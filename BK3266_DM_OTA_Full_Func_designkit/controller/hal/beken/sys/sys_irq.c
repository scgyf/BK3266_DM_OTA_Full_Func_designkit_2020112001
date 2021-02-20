/***********************************************************************
 *
 * MODULE NAME:    sys_irq.c
 * PROJECT CODE:   Bluetooth
 * DESCRIPTION:    Hardware Interrupt Interface
 * MAINTAINER:     Tom Kerwick
 * CREATION DATE:  10 Jan 2011
 *
 * LICENSE:
 *     This source code is copyright (c) 2011 Ceva Inc.
 *     All rights reserved.
 *
 ***********************************************************************/
#include "sys_config.h"
#include "config.h"
#include "sys_types.h"
#include "sys_irq.h"
#include "sys_irq_impl.h"
#include "bautil.h"
#include "lslc_irq.h"
#include "hw_leds.h"
#include "beken_external.h"
#include "bk3000_mcu.h"
#include "driver_flash.h"
#ifdef BEKEN_OTA
#include "app_ota.h"
#if(BEKEN_OTA_1ST_HALF_ONLY==1)
#include "bootloader.h"
#endif
#endif

static u_int32 int_disable_count = 0;
static u_int32 int_restore_count = 0;

extern void uart_handler(void);

extern void timer_pwm1_pt2_isr(void);
extern void gpio_isr(void);

#if defined(CONFIG_TWS)
extern void pwm1_pt1_isr(void);
#endif
#ifdef BT_DUALMODE
extern RAM_CODE void aud_isr(int mode_sel );
#else
extern DRAM_CODE void aud_isr(int mode_sel );
#endif
#ifdef CONFIG_APP_AEC
extern void fft_isr( void );
#endif
extern void saradc_isr(void);
extern void gpio_isr(void);
#ifdef CONFIG_IRDA
extern DRAM_CODE void IrDA_isr(void);
#endif
extern void usb_isr(void);
#ifdef CONFIG_DRIVER_SPI
extern void spi2_isr(void);
#endif
#ifdef CONFIG_DRIVER_I2S
extern void i2s_isr(void);
#endif

#if 1
#define HALF_1ST_CODE_ADDR            0x1E20
#define HALF_2ND_CODE_ADDR            0xF1E20       
typedef void (*jump_func)(void);
BOOT_CODE void flash_read_mark (uint8 *buffer, uint32 address, uint32 len) 
{
    uint32 i, reg_value;
    uint32 addr = address&(~0x1f);
    uint32 buf[8];
    uint8 *pb = (uint8 *)&buf[0];

    if (len == 0)
        return;

    while(reg_FLASH_OPERATE_SW & 0x80000000);
    while (len) {
        reg_value = reg_FLASH_OPERATE_SW;
        reg_FLASH_OPERATE_SW = (  (addr              << BIT_ADDRESS_SW)
                                | (FLASH_OPCODE_READ << BIT_OP_TYPE_SW)
                                | (0x1               << BIT_OP_SW)
                                | (reg_value         &  SET_WP_VALUE));
        while(reg_FLASH_OPERATE_SW & 0x80000000);
        addr+=32;

        for (i=0; i<8; i++)
            buf[i] = reg_FLASH_DATA_FLASH_SW;

        for (i=(address&0x1f); i<32; i++) {
            *buffer++ = pb[i];
            address++;
            len--;
            if (len == 0)
                break;
        }
    }
}

#ifdef BEKEN_OTA
BOOT_CODE u_int16 get_software_mark(u_int16 mark)
{
    volatile u_int16 p_half;
    if(OTA_B_MARK == mark)
    {
        flash_read_mark((uint8*)&p_half, OTA_B_ADDR + OTA_MARK_OFFSET, 2);   
    }
    else if(OTA_A_MARK == mark)
    {
        flash_read_mark((uint8*)&p_half, OTA_A_ADDR + OTA_MARK_OFFSET, 2);   
    }
    return p_half;
}

BOOT_CODE u_int16 get_software_version(void)
{
    u_int16 version;
    if(OTA_B_MARK == get_software_mark(OTA_B_MARK))
    {
        flash_read_mark((uint8*)&version, OTA_B_ADDR + OTA_VER_OFFSET, 2);
    }
    else
    {
        flash_read_mark((uint8*)&version, OTA_A_ADDR + OTA_VER_OFFSET, 2);
    }
    
    return version;  
}
#endif

BOOT_CODE void _check_update_finished(void)
{
    jump_func func;
	
#ifdef BEKEN_OTA
    if(OTA_B_MARK == get_software_mark(OTA_B_MARK))
    {
    	#if(BEKEN_OTA_1ST_HALF_ONLY==1)//OTA SUCCESS
		Boot_loader();
		func =(jump_func)(volatile uint32 *)(HALF_1ST_CODE_ADDR + 16 + 32);
		#else
    	func =(jump_func)(volatile uint32 *)(HALF_2ND_CODE_ADDR + 16 + 32);
		#endif
    }
    else
#endif
    {
    	func =(jump_func)(volatile uint32 *)(HALF_1ST_CODE_ADDR + 16 + 32);
    }
    func();
    return;
}

BOOT_CODE void watchdog_reset(void)
{
    BK3000_WDT_CONFIG = 0x5A0001|0x3fff;
    BK3000_WDT_CONFIG = 0xA50001|0x3fff;
}
#endif

/******************************************************************************
 *
 * FUNCTION:  SYSirq_Disable_Interrupts_Save_Flags
 * PURPOSE:   Disables ARM IRQ and FIQ Interrupts, saves previous
 *            PSR
 *
 ******************************************************************************/
DRAM_CODE void SYSirq_Disable_Interrupts_Save_Flags(u_int32 *flags, u_int32 *mask) {
    *flags = get_spr(SPR_SR);
    cpu_set_interrupts_enabled(0);
    *mask = get_spr(SPR_VICMR(0));
    set_spr(SPR_VICMR(0), 0x00);

    int_disable_count++;
}
void SYSirq_Disable_Interrupts_Except(u_int32 *oldflags, u_int32 flags)
{
    cpu_set_interrupts_enabled(0);
    *oldflags = get_spr(SPR_VICMR(0));
    set_spr(SPR_VICMR(0), flags);
    cpu_set_interrupts_enabled(1);
}
void SYSirq_Enable_All_Interrupts(u_int32 flags)
{
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), flags);
    cpu_set_interrupts_enabled(1);
 
}
void SYSirq_Unmask_Interrupt(u_int32 *oldflags,u_int32 flags)
{
    cpu_set_interrupts_enabled(0);
    *oldflags = get_spr(SPR_VICMR(0));
    set_spr(SPR_VICMR(0), (*oldflags) & (~flags));
    cpu_set_interrupts_enabled(1);
}

void SYSirq_interrupt_enable(int index)
{
    unsigned long oldmask = get_spr(SPR_VICMR(0));    // read old spr_vicmr
    set_spr(SPR_VICMR(0), oldmask | (1<<index));      // set  new spr_vicmr
}

void SYSirq_interrupt_disable(int index)
{
    unsigned long oldmask = get_spr(SPR_VICMR(0));    // read old spr_vicmr
    set_spr(SPR_VICMR(0), oldmask & (~(1<<index)));   // set  new spr_vicmr
}


/******************************************************************************
 *
 * FUNCTION:  SYSirq_Interrupts_Restore_Flags
 * PURPOSE:   Restores previously saved previous PSR
 *
 ******************************************************************************/
DRAM_CODE void SYSirq_Interrupts_Clear_Trig_Flags(void)
{
    uint32 trg_flags = get_spr(SPR_VICTR(0));
    if(trg_flags)
    {
        set_spr(SPR_VICTR(0),0);    
    }
}
DRAM_CODE void SYSirq_Interrupts_Restore_Flags(u_int32 flags, u_int32 mask) {

    int_restore_count++;

    if (int_disable_count > int_restore_count)
    {
        return;
    }
	else
	{
	    int_disable_count = 0;
		int_restore_count = 0;
	}
	
    if(mask != 0)
    {
        uint32 trg_flags = get_spr(SPR_VICTR(0));
        set_spr(SPR_VICTR(0), trg_flags &(~(1<<VIC_CEVA_ISR_INDEX)));
        set_spr(SPR_VICMR(0), mask);
    }

    set_spr(SPR_SR,flags);

}

/******************************************************************************
 *
 * FUNCTION:  SYSirq_Initialise
 * PURPOSE:   Initialise Interrupt Requests
 *
 ******************************************************************************/
void SYSirq_Initialise(void) {
    unsigned int sr;

    // clear all interrupts
    set_spr( SPR_VICTR(0), 0x00000000 );

    // enable interrupts
    set_spr( SPR_VICMR(0), (  (1<<VIC_AUD_ISR_INDEX)
                            | (1<<VIC_PWM5_ISR_INDEX)
                            | (1<<VIC_UART_ISR_INDEX)
                            | (1<<VIC_SADC_ISR_INDEX)
                        #ifdef CONFIG_APP_AEC
                            | (1<<VIC_FFT_ISR_INDEX)
                        #endif
                        #ifdef CONFIG_TWS
				            | (1<<VIC_PWM4_ISR_INDEX)
                        #endif
                            | (1<<VIC_CEVA_ISR_INDEX)));

    // set interrupt handler
    set_vic_handler( SPR_VICVA(VIC_SDIO_ISR_INDEX), _sdio_isr );
    set_vic_handler( SPR_VICVA(VIC_SADC_ISR_INDEX), _sadc_isr );
    set_vic_handler( SPR_VICVA(VIC_AUD_ISR_INDEX ), _aud_isr  );
    set_vic_handler( SPR_VICVA(VIC_PWM0_ISR_INDEX), _pwm0_isr );
    set_vic_handler( SPR_VICVA(VIC_PWM1_ISR_INDEX), _pwm1_isr );
    set_vic_handler( SPR_VICVA(VIC_PWM2_ISR_INDEX), _pwm2_isr );
    set_vic_handler( SPR_VICVA(VIC_PWM3_ISR_INDEX), _pwm3_isr );
    set_vic_handler( SPR_VICVA(VIC_PWM4_ISR_INDEX), _pwm4_isr );
    set_vic_handler( SPR_VICVA(VIC_PWM5_ISR_INDEX), _pwm5_isr );
    set_vic_handler( SPR_VICVA(VIC_GPIO_ISR_INDEX), _gpio_isr );
    set_vic_handler( SPR_VICVA(VIC_SPI_ISR_INDEX ), _spi_isr  );
    set_vic_handler( SPR_VICVA(VIC_SPI2_ISR_INDEX ), _spi2_isr  );
    set_vic_handler( SPR_VICVA(VIC_I2S_ISR_INDEX), _i2s_isr );
    set_vic_handler( SPR_VICVA(VIC_I2C2_ISR_INDEX), _i2c2_isr );
    set_vic_handler( SPR_VICVA(VIC_UART_ISR_INDEX), _uart_isr );
    set_vic_handler( SPR_VICVA(VIC_FFT_ISR_INDEX ), _fft_isr  );
    set_vic_handler( SPR_VICVA(VIC_DMA_ISR_INDEX ), _dma_isr  );
    set_vic_handler( SPR_VICVA(VIC_CEVA_ISR_INDEX), _ceva_isr );
    set_vic_handler( SPR_VICVA(VIC_USB_ISR_INDEX ), _usb_isr  );
    set_vic_handler( SPR_VICVA(VIC_IRDA_ISR_INDEX), _irda_isr );

    // set priority
    set_spr( SPR_VICPR(VIC_SDIO_ISR_INDEX), 1 );
    set_spr( SPR_VICPR(VIC_SADC_ISR_INDEX), 2 );
    set_spr( SPR_VICPR(VIC_AUD_ISR_INDEX ), 7 );
    set_spr( SPR_VICPR(VIC_PWM0_ISR_INDEX), 5 );
    set_spr( SPR_VICPR(VIC_PWM1_ISR_INDEX), 5 );
    set_spr( SPR_VICPR(VIC_PWM2_ISR_INDEX), 2 );
    set_spr( SPR_VICPR(VIC_PWM3_ISR_INDEX), 3 );
    set_spr( SPR_VICPR(VIC_PWM4_ISR_INDEX), 5 );
    set_spr( SPR_VICPR(VIC_PWM5_ISR_INDEX), 5 );
    set_spr( SPR_VICPR(VIC_GPIO_ISR_INDEX), 2 );
    set_spr( SPR_VICPR(VIC_SPI_ISR_INDEX),  3 );
    set_spr( SPR_VICPR(VIC_SPI2_ISR_INDEX), 3 );
    set_spr( SPR_VICPR(VIC_I2S_ISR_INDEX),  1 );
    set_spr( SPR_VICPR(VIC_I2C2_ISR_INDEX), 1 );
    set_spr( SPR_VICPR(VIC_UART_ISR_INDEX), 2 );
    set_spr( SPR_VICPR(VIC_FFT_ISR_INDEX ), 2 );
    set_spr( SPR_VICPR(VIC_DMA_ISR_INDEX ), 3 );
    set_spr( SPR_VICPR(VIC_CEVA_ISR_INDEX), 6 );
    set_spr( SPR_VICPR(VIC_USB_ISR_INDEX ), 1 );
    set_spr( SPR_VICPR(VIC_IRDA_ISR_INDEX), 3 );

    set_spr(SPR_PM_EVENT_CTRL, 0x01);//enable pic  envent
    // set global interrupt enable
    sr = get_spr(SPR_SR);
    sr = sr | SPR_SR_IEE;
    set_spr(SPR_SR, sr);
}

void UART_InterruptHandler(void) {
    unsigned int oldmask = get_spr(SPR_VICMR(0));
    /* unsigned int sr ; */
    set_spr(SPR_VICMR(0), oldmask & (1 << VIC_CEVA_ISR_INDEX));

    /* //disable dcache */
    /* sr = get_spr(SPR_SR); */
    /* sr = sr & (~SPR_SR_DCE); */
    /* set_spr(SPR_SR, sr); */

    uart_handler();

    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);

    /* //enable dcache */
    /* sr = get_spr(SPR_SR); */
    /* sr = sr | SPR_SR_DCE; */
    /* set_spr(SPR_SR, sr); */
}

DRAM_CODE void CEVA_InterruptHandler (void) {
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
    set_spr(SPR_VICMR(0), oldmask&(1<<VIC_AUD_ISR_INDEX));                     //mask all priority interrupt.
    if(oldmask&(1<<VIC_AUD_ISR_INDEX))
        cpu_set_interrupts_enabled(1);
    //set_spr(SPR_VICMR(0), 0x00);					   //mask all priority interrupt.

    LSLCirq_IRQ_Handler();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);                  //recover the old spr_vicmr.

}

void PWM5_InterruptHandler (void) 
{
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
#ifdef CONFIG_IRDA
    set_spr( SPR_VICMR(0), oldmask & ((1 << VIC_CEVA_ISR_INDEX)|(1 << VIC_IRDA_ISR_INDEX)));
#else
    set_spr( SPR_VICMR(0), oldmask & (1 << VIC_CEVA_ISR_INDEX));
#endif
    cpu_set_interrupts_enabled(1);

    //set_spr(SPR_VICMR(0), 0x00);                     //mask all/low priority interrupt.
    timer_pwm1_pt2_isr();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);                  //recover the old spr_vicmr.
}

#ifdef BT_DUALMODE
RAM_CODE void AUD_InterruptHandler (void) 
#else
DRAM_CODE void AUD_InterruptHandler (void) 
#endif
{
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
    set_spr(SPR_VICMR(0), 0x00);                     //mask all/low priority interrupt.
    aud_isr(0);
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);                  //recover the old spr_vicmr.
}

#ifdef CONFIG_APP_AEC
#ifdef BT_DUALMODE
RAM_CODE void FFT_InterruptHandler (void)
#else
DRAM_CODE void FFT_InterruptHandler (void)
#endif
{
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
#ifdef CONFIG_IRDA
    set_spr(SPR_VICMR(0), oldmask & (1 << VIC_IRDA_ISR_INDEX));                     //mask all/low priority interrupt.
#else
    set_spr(SPR_VICMR(0), 0x00);                     //mask all/low priority interrupt.
#endif
    fft_isr();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);                  //recover the old spr_vicmr.
}
#else
void FFT_InterruptHandler  (void) {os_printf("FFT_InterruptHandler\r\n");}
#endif
#ifdef CONFIG_APP_USB
void USB_InterruptHandler (void)
{
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
#ifdef CONFIG_IRDA
    set_spr(SPR_VICMR(0), oldmask & (1 << VIC_IRDA_ISR_INDEX));                        //mask all/low priority interrupt.
#else
    set_spr(SPR_VICMR(0), 0x00);                        //mask all/low priority interrupt.
#endif
    usb_isr();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask); 
}
#else
void USB_InterruptHandler  (void) {os_printf("USB_InterruptHandler\r\n");}
#endif
void SADC_InterruptHandler (void)
{
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
#ifdef CONFIG_IRDA
    set_spr( SPR_VICMR(0), oldmask & ((1 << VIC_CEVA_ISR_INDEX)|(1 << VIC_IRDA_ISR_INDEX)));                     //mask all/low priority interrupt.
#else
    set_spr( SPR_VICMR(0), oldmask & (1 << VIC_CEVA_ISR_INDEX));                     //mask all/low priority interrupt.
#endif
    saradc_isr();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);                  //recover the old spr_vicmr.
}

void INT0_InterruptHandler (void) {os_printf("INT0_InterruptHandler\r\n");}
void INT1_InterruptHandler (void) {os_printf("INT1_InterruptHandler\r\n");}
void TIME_InterruptHandler (void) {os_printf("TIME_InterruptHandler\r\n");}
void PWM0_InterruptHandler (void) {os_printf("PWM0_InterruptHandler\r\n");}
void PWM1_InterruptHandler (void) {os_printf("PWM1_InterruptHandler\r\n");}
void PWM2_InterruptHandler (void) {os_printf("PWM2_InterruptHandler\r\n");}
void PWM3_InterruptHandler (void) {os_printf("PWM3_InterruptHandler\r\n");}

void PWM4_InterruptHandler (void) {
#if defined(CONFIG_TWS)
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
    set_spr(SPR_VICMR(0), 0x00);                     //mask all/low priority interrupt.
    pwm1_pt1_isr();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);                  //recover the old spr_vicmr.
#else
	os_printf("PWM4_InterruptHandler\r\n");
#endif
}

void GPIO_InterruptHandler (void) //{os_printf("GPIO_InterruptHandler\r\n");}
{
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
    set_spr(SPR_VICMR(0), oldmask & (1 << VIC_IRDA_ISR_INDEX));                     //mask all/low priority interrupt.
    gpio_isr();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);                  //recover the old spr_vicmr.
}
#ifdef CONFIG_IRDA
DRAM_CODE void IRDA_InterruptHandler (void) 
{
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
    set_spr(SPR_VICMR(0), 0x00);                         //mask all/low priority interrupt.
    IrDA_isr();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);   
}
#else
void IRDA_InterruptHandler (void)  {os_printf("IRDA_InterruptHandler\r\n");}
#endif

void I2S_InterruptHandler (void) 
{
#ifdef CONFIG_DRIVER_I2S
    unsigned int oldmask = get_spr(SPR_VICMR(0));    //read old spr_vicmr
    set_spr(SPR_VICMR(0), oldmask&(1<<VIC_CEVA_ISR_INDEX));                     //mask all priority interrupt.
    cpu_set_interrupts_enabled(1);
    i2s_isr();
    cpu_set_interrupts_enabled(0);
    set_spr(SPR_VICMR(0), oldmask);                  //recover the old spr_vicmr.
#else
    os_printf("I2S_InterruptHandler\r\n");
#endif
}

void SPI_InterruptHandler  (void) {os_printf("SPI_InterruptHandler\r\n");}
void SPI2_InterruptHandler (void) {os_printf("SPI2_InterruptHandler\r\n");}
void I2C2_InterruptHandler (void) {os_printf("I2C2_InterruptHandler\r\n");}
void DMA_InterruptHandler  (void) {os_printf("DMA_InterruptHandler\r\n");}
void SDIO_InterruptHandler (void) {/*os_printf("SDIO_InteruptHandler\r\n");*/}
//void IRDA_InterruptHandler (void) {os_printf("IRDA_InteruptHandler\r\n");}
