#include <string.h>
#include "driver_beken_includes.h"
#include "app_beken_includes.h"
#if(BEKEN_OTA_1ST_HALF_ONLY==1)
#include "app_ota.h"
#include "bootloader.h"

extern BOOT_CODE u_int16 get_software_mark(u_int16 mark);
extern BOOT_CODE u_int16 get_software_version(void);

enum 
{
	FLASH_ERASE_4K       = 1,
	FLASH_ERASE_32K      = 2,
	FLASH_ERASE_64K      = 3,
} FLASH_ERASE_SIZE;

BOOT_CODE uint32 Boot_flash_read_mID(void) 
{
    unsigned int temp0;
    uint32 flash_id;

    while(reg_FLASH_OPERATE_SW & 0x80000000);
    temp0 = reg_FLASH_OPERATE_SW;
    reg_FLASH_OPERATE_SW = (  (temp0             &  SET_ADDRESS_SW)
                            | (FLASH_OPCODE_RDID << BIT_OP_TYPE_SW)
                            | (0x1               << BIT_OP_SW)
                            | (temp0             &  SET_WP_VALUE));
    while(reg_FLASH_OPERATE_SW & 0x80000000);

    flash_id = reg_FLASH_RDID_DATA_FLASH;
    return (flash_id & 0xFFFFFF);
}

BOOT_CODE void Boot_flash_set_line_mode(uint8 mode) 
{
    if(mode == FLASH_LINE_2) 
    {       
        reg_FLASH_CONF &= (~(7<<BIT_MODE_SEL));
        reg_FLASH_CONF |= (1<<BIT_MODE_SEL);  
    }
}

BOOT_CODE void Boot_flash_set_protect(uint8 all) 
{
    unsigned int temp0;
	uint8 bit_QE = 0;
	uint32 flash_id;
    while(reg_FLASH_OPERATE_SW & 0x80000000){}

    temp0 = reg_FLASH_CONF; //ÅäÖÃWRSR Status data
    temp0 &= 0xfffe0fff;    // set [BP4:BP0] = 0
    flash_id = Boot_flash_read_mID();

	if(((flash_id & 0x00ff0000) == 0x00BA0000) || flash_id == 0xC22014 ) // ZETTA
    {// ZETTA 
        if(all == 1)
        {
            reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
            					| (0x1003c << BIT_WRSR_DATA));// protect all sectors for ZETTA
        }
        else
        {
            reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
            					| (0x10028 << BIT_WRSR_DATA));//protect 0 -251 sectors
        }
        	//Start WRSR
    	temp0 = reg_FLASH_OPERATE_SW;
    	reg_FLASH_OPERATE_SW = (  (temp0   &  SET_ADDRESS_SW)
    								| (FLASH_OPCODE_WRSR << BIT_OP_TYPE_SW)
                            		| (0x1               << BIT_OP_SW)
                            		| (0x1               << BIT_WP_VALUE)); // make WP equal 1 not protect SRP
        while(reg_FLASH_OPERATE_SW & 0x80000000);
    }
    else if(flash_id == 0xC22314) 
    {//MXIC 
    	/* Attention: TB(top/bottom) bit of MXIC flash is OTP !!! */
        if(READ_CHIPID == 0x326283)  //chipid = '3262S'
        {
            reg_FLASH_SR_DATA_CRC_CNT = (0xa5 << 22);            
            if(all == 1)
            {
                reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
                                                 |(bit_QE  << 16)// QE(Quad Enable)
            					       | (0x1003c << BIT_WRSR_DATA));//protect 0 -251 sectors
            }
            else
            {
                reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
                                                 |(bit_QE  << 16)// QE(Quad Enable)
            					       | (0x10000 << BIT_WRSR_DATA)); // only protect 0th-7th blocks for MXIC,so 8th-15th blks may be written;0x10850 QE = enable
            }
        }    
        else
        {
            if(all == 1)
            {
                reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
            					    | (0x1003c << BIT_WRSR_DATA));////protect all
            }
            else
            {
                reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
            					    | (0x10000 << BIT_WRSR_DATA));//protect none 
            } 
        }
       //Start WRSR
    	temp0 = reg_FLASH_OPERATE_SW;
    	reg_FLASH_OPERATE_SW = (  (temp0    &  SET_ADDRESS_SW)
    								| (FLASH_OPCODE_WRSR << BIT_OP_TYPE_SW)
                            		| (0x1               << BIT_OP_SW)
                            		| (0x1               << BIT_WP_VALUE)); // make WP equal 1 not protect SRP
        while(reg_FLASH_OPERATE_SW & 0x80000000);
    }
	else if(flash_id == 0x5e4014) //xtx 8M flash
    {
        if(all == 1)
            reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
                                   |(0x1001c << BIT_WRSR_DATA)); 
    	else
        	reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
                               |(0x10000 << BIT_WRSR_DATA));

        //Start WRSR
        temp0 = reg_FLASH_OPERATE_SW;
        reg_FLASH_OPERATE_SW = (  (temp0 &  SET_ADDRESS_SW)
                                         | (FLASH_OPCODE_WRSR << BIT_OP_TYPE_SW)
                                         | (0x1                << BIT_OP_SW)
                                         | (0x1                << BIT_WP_VALUE)); // make WP equal 1 not protect SRP
        while(reg_FLASH_OPERATE_SW & 0x80000000);    
    }
	else if((flash_id == 0x0b4015) ||(flash_id == 0xc84015))//xtx 16M flash  CMP:0   GD 25Q16B 
    {
        if(all == 1)
        {
            reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
            					| (0x10011 << BIT_WRSR_DATA));
        }
    	 else
        {
            reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
            					| (0x10000 << BIT_WRSR_DATA));
        }
        //Start WRSR
        temp0 = reg_FLASH_OPERATE_SW;
        reg_FLASH_OPERATE_SW = (  (temp0 &  SET_ADDRESS_SW)
                                         | (FLASH_OPCODE_WRSR << BIT_OP_TYPE_SW)
                                         | (0x1                << BIT_OP_SW)
                                         | (0x1                << BIT_WP_VALUE)); // make WP equal 1 not protect SRP
        while(reg_FLASH_OPERATE_SW & 0x80000000);    
    }
    else if(flash_id == 0x514014) //MD25D80 8M flash
    {
    	//os_printf("MD25D80\r\n");
        if(all == 1)
            reg_FLASH_CONF = ((temp0 &  SET_FLASH_CLK_CONF)
                               |(0x1001c << BIT_WRSR_DATA)); 
    	else
        	reg_FLASH_CONF = ((temp0 &  SET_FLASH_CLK_CONF)
                                | (0x10000 << BIT_WRSR_DATA));

        //Start WRSR
        temp0 = reg_FLASH_OPERATE_SW;
        reg_FLASH_OPERATE_SW = (  (temp0 &  SET_ADDRESS_SW)
                                         | (FLASH_OPCODE_WRSR << BIT_OP_TYPE_SW)
                                         | (0x1                << BIT_OP_SW)
                                         | (0x1                << BIT_WP_VALUE)); // make WP equal 1 not protect SRP
        while(reg_FLASH_OPERATE_SW & 0x80000000);    
    }
	else if(flash_id == 0x856014)//P25Q80 8M flash
    {
    	//if (flash_mid == 0x856013)
    	//	os_printf("P25Q40\r\n");
		//else
		//	os_printf("P25Q80\r\n");
        if(all == 1)
        {
            reg_FLASH_CONF = ((temp0&SET_FLASH_CLK_CONF)
        						|(0x14000 << BIT_WRSR_DATA));//protect all
        }
        else
        {
            reg_FLASH_CONF = ((temp0&SET_FLASH_CLK_CONF)
        						| (0x14048 << BIT_WRSR_DATA));//protect Lower 504KB    1016K
        }
        //Start WRSR
        temp0 = reg_FLASH_OPERATE_SW;
        reg_FLASH_OPERATE_SW = (  (temp0 &	SET_ADDRESS_SW)
        					 | (FLASH_OPCODE_WRSR2 << BIT_OP_TYPE_SW)
        					 | (0x1 			   << BIT_OP_SW)
        					 | (0x1 			   << BIT_WP_VALUE)); // make WP equal 1 not protect SRP
        while(reg_FLASH_OPERATE_SW & 0x80000000);
    }		
    else
    {//other flash, such as BOYA, Paragon, BG etc.
    	if(all == 1)
        	reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
        					   |(bit_QE  << 19)// QE(Quad Enable)
                               |(0x14000 << BIT_WRSR_DATA)); //protect all sectors &
    	else
        	reg_FLASH_CONF = (  (temp0 &  SET_FLASH_CLK_CONF)
        					   |(bit_QE  << 19)// QE(Quad Enable)
                                    	  	 | (0x10000 << BIT_WRSR_DATA));//protect address:0x00000-0xfbfff


        //Start WRSR
        temp0 = reg_FLASH_OPERATE_SW;
        reg_FLASH_OPERATE_SW = (  (temp0 &  SET_ADDRESS_SW)
                                         | (FLASH_OPCODE_WRSR2 << BIT_OP_TYPE_SW)
                                         | (0x1                << BIT_OP_SW)
                                         | (0x1                << BIT_WP_VALUE)); // make WP equal 1 not protect SRP
        while(reg_FLASH_OPERATE_SW & 0x80000000);
    }
    while(reg_FLASH_OPERATE_SW & 0x80000000);   
}

BOOT_CODE void Boot_set_flash_clk(unsigned char clk_conf) 
{
    unsigned int temp0;
    temp0 = reg_FLASH_CONF;
    reg_FLASH_CONF = (  (clk_conf << BIT_FLASH_CLK_CONF)
                      | (temp0    &  SET_MODE_SEL)
                      | (temp0    &  SET_FWREN_FLASH_CPU)
                      | (temp0    &  SET_WRSR_DATA)
                      | (temp0    &  SET_CRC_EN));

	/* Flash read data operation after setting clock */
	while(reg_FLASH_OPERATE_SW & 0x80000000);
    temp0 = reg_FLASH_OPERATE_SW;
    reg_FLASH_OPERATE_SW = (  (0              << BIT_ADDRESS_SW)
                            | (FLASH_OPCODE_READ << BIT_OP_TYPE_SW)
                            | (0x1               << BIT_OP_SW)
                            | (temp0          &  SET_WP_VALUE));
    while(reg_FLASH_OPERATE_SW & 0x80000000);
    temp0 = reg_FLASH_DATA_SW_FLASH;
    temp0 = reg_FLASH_DATA_SW_FLASH;
    temp0 = reg_FLASH_DATA_SW_FLASH;
    temp0 = reg_FLASH_DATA_SW_FLASH;
   	temp0 = reg_FLASH_DATA_SW_FLASH;
    temp0 = reg_FLASH_DATA_SW_FLASH;
    temp0 = reg_FLASH_DATA_SW_FLASH;
    temp0 = reg_FLASH_DATA_SW_FLASH;
}

BOOT_CODE void Boot_flash_erase_sector(uint32 address, uint8 erase_size) 
{
    unsigned int temp0;
    uint32 flash_opcode;

    if(erase_size == FLASH_ERASE_32K)
        flash_opcode = FLASH_OPCODE_BE1;
    else if(erase_size == FLASH_ERASE_64K)
        flash_opcode = FLASH_OPCODE_BE2;
    else
        flash_opcode = FLASH_OPCODE_SE;

    while(reg_FLASH_OPERATE_SW & 0x80000000);
    temp0 = reg_FLASH_OPERATE_SW;
    reg_FLASH_OPERATE_SW = (  (address      << BIT_ADDRESS_SW)
                            | (flash_opcode << BIT_OP_TYPE_SW)
                            | (0x1          << BIT_OP_SW)
                            | (temp0        &  SET_WP_VALUE));
    while(reg_FLASH_OPERATE_SW & 0x80000000);
}

BOOT_CODE void Boot_flash_read_data(uint8 *buffer, uint32 address, uint32 len) 
{
    uint32 i, reg_value;
    uint32 addr = address&(~0x1F);
    uint32 buf[8];
    uint8 *pb = (uint8 *)&buf[0];

    while(reg_FLASH_OPERATE_SW & 0x80000000);
    while(len) 
    {
        reg_value = reg_FLASH_OPERATE_SW;
        reg_FLASH_OPERATE_SW = (  (addr              << BIT_ADDRESS_SW)
                                | (FLASH_OPCODE_READ << BIT_OP_TYPE_SW)
                                | (0x1               << BIT_OP_SW)
                                | (reg_value         &  SET_WP_VALUE));
        while(reg_FLASH_OPERATE_SW & 0x80000000);
        
        addr += 32;

        for(i = 0; i < 8; i++)
            buf[i] = reg_FLASH_DATA_FLASH_SW;

        for(i = (address & 0x1F); i < 32; i++) 
        {
            *buffer++ = pb[i];
            address++;
            len--;
            if(len == 0)
                break;
        }
    }
}

BOOT_CODE void Boot_flash_write_data(uint8 *buffer, uint32 address, uint32 len) 
{
    uint32 i, reg_value;
    uint32 addr = address&(~0x1F);
    uint32 buf[8];
    uint8 *pb = (uint8 *)&buf[0];
 
    if(address & 0x1F)
        Boot_flash_read_data(pb, addr, 32);

    while(reg_FLASH_OPERATE_SW & 0x80000000);
    while(len) 
    {
        for(i = (address & 0x1F); i < 32; i++)
        {
            if(len)
            {
                pb[i] = *buffer++;
                address++;
                len--;
            }
            else
                pb[i] = 0xFF;
        }

        for(i = 0; i < 8; i++)
            reg_FLASH_DATA_SW_FLASH = buf[i];

        reg_value = reg_FLASH_OPERATE_SW;
        reg_FLASH_OPERATE_SW = (  (addr            << BIT_ADDRESS_SW)
                                | (FLASH_OPCODE_PP << BIT_OP_TYPE_SW)
                                | (0x1             << BIT_OP_SW)
                                | (reg_value       &  SET_WP_VALUE));
        while(reg_FLASH_OPERATE_SW & 0x80000000);
        addr += 32;
    }
}

BOOT_CODE void Boot_erase_code(uint32 start_addr, uint32 end_addr)
{
    while(start_addr < end_addr)
    {
        if(((start_addr % 0x10000) == 0) && ((start_addr + 0x10000) < end_addr))
        {
            Boot_flash_erase_sector(start_addr, FLASH_ERASE_64K);
            start_addr += 0x10000;
        }
        else if(((start_addr % 0x8000) == 0) && ((start_addr+ 0x8000) < end_addr))
        {
            Boot_flash_erase_sector(start_addr, FLASH_ERASE_32K);
            start_addr += 0x8000;
        }
        else
        {
            Boot_flash_erase_sector(start_addr, FLASH_ERASE_4K);
            start_addr += 0x1000;
        }
    }
}

BOOT_CODE uint16 Boot_calc_crc(uint32 start_addr, uint32 end_addr)
{
    uint8 data[1000];
    uint16 crc = 0xFFFF;
    uint16 len = 0;
    uint32 i = 0;
    
    while(start_addr < end_addr)
    {
        i = 0;
        len = ((start_addr + sizeof(data)) <= end_addr) ? sizeof(data) : (end_addr - start_addr);
        Boot_flash_read_data(data, start_addr, len);
        while(i < len) 
        {        
             crc = ((crc >> 8) | (crc << 8)) & 0xFFFF;   
             crc ^= (data[i++] & 0xFF);   
             crc ^= ((crc & 0xFF) >> 4);      
             crc ^= (crc << 12) & 0xFFFF;   
             crc ^= ((crc & 0xFF) << 5) & 0xFFFF;   
        } 
        start_addr += len; 
    }
    
    return crc;
}

BOOT_CODE void app_ota_copy_flash(uint32 read_start, uint32 read_end, uint32 write_start, uint32 write_end)
{
	uint8 data[1000];
    uint16 len = 0;

    while(read_start < read_end)
    {
        if((read_start + sizeof(data)/sizeof(data[0])) <= read_end)
            len = sizeof(data)/sizeof(data[0]);
        else
            len = read_end - read_start;
        
        Boot_flash_read_data(data, read_start, len);
        Boot_flash_write_data(data, write_start, len);
        read_start += len; 
		write_start += len;
    }
}

#if 0
#define PRINT_BUF_PREPARE(rc, buf, fmt)             \
    int rc;                                         \
    va_list args;                                   \
    va_start(args, fmt);                            \
    rc = vsnprintf(buf, sizeof(buf), fmt, args);    \
    va_end(args);                                   \
    buf[sizeof(buf) - 1] = '\0';
#define PRINT_BUF_SIZE 0X100

BOOT_CODE void Boot_uart_init(u_int32 baud_rate) 
{
    u_int32 baud_divisor;

    baud_divisor           = UART_CLOCK_FREQ_26M/baud_rate;
    baud_divisor           = baud_divisor-1;

    REG_APB3_UART_CFG      = (   (DEF_STOP_BIT    << sft_UART_CONF_STOP_LEN)
                                 | (DEF_PARITY_MODE << sft_UART_CONF_PAR_MODE)
                                 | (DEF_PARITY_EN   << sft_UART_CONF_PAR_EN)
                                 | (DEF_DATA_LEN    << sft_UART_CONF_UART_LEN)
                                 | (baud_divisor    << sft_UART_CONF_CLK_DIVID)
                                 | (DEF_IRDA_MODE   << sft_UART_CONF_IRDA)
                                 | (DEF_RX_EN       << sft_UART_CONF_RX_ENABLE)
                                 | (DEF_TX_EN       << sft_UART_CONF_TX_ENABLE));

    REG_APB3_UART_FIFO_THRESHOLD = ((RX_FIFO_THRD << sft_UART_FIFO_CONF_RX_FIFO)
                                    | (TX_FIFO_THRD << sft_UART_FIFO_CONF_TX_FIFO));
    REG_APB3_UART_INT_ENABLE=0;             /* Disable UART Interrupts */
    REG_APB3_UART_INT_ENABLE = bit_UART_INT_RX_NEED_READ | bit_UART_INT_RX_STOP_END; //enable Rx interrupt
    BK3000_GPIO_0_CONFIG = 0x70;
    BK3000_GPIO_1_CONFIG = 0x7C;
}

BOOT_CODE void Boot_uart_send (unsigned char *buff, unsigned int len)
{
    while (len--) 
	{
        while(!UART_TX_WRITE_READY);
            UART_WRITE_BYTE(*buff++);
    }
}

BOOT_CODE int32 Boot_printf(const char *fmt, ...) 
{
    char buf[PRINT_BUF_SIZE];

    PRINT_BUF_PREPARE(rc, buf, fmt);
    Boot_uart_send((unsigned char *)&buf[0], rc);
    return rc;
}
#endif

BOOT_CODE void Boot_wdt_reset(void )
{
    BK3000_WDT_CONFIG = 0x5A0001;
    BK3000_WDT_CONFIG = 0xA50001;
}

BOOT_CODE void Boot_loader(void)
{
	ota_info_s ota_info_read;
	uint16 section_A = OTA_A_MARK;
    uint16 section_B = 0x0000;
	
	/****1.Stop watchdog****/
	BK3000_WDT_CONFIG = 0x5A0000;
    BK3000_WDT_CONFIG = 0xA50000;

	//BK3000_GPIO_6_CONFIG = 00;//gpio2=0
	//BK3000_GPIO_8_CONFIG = 00;//gpio4=0
	//BK3000_GPIO_8_CONFIG ^= 0x02;//gpio4=1

	/****2.set flash para****/
	Boot_flash_set_protect(0);
	Boot_set_flash_clk(FLASH_CLK_26mHz);
    Boot_flash_set_line_mode(FLASH_LINE_2);

	/****3.erase 1st half flash****/
	Boot_erase_code(OTA_A_ADDR, OTA_B_ADDR);
	
	/****4.read ota info****/
	Boot_flash_read_data((uint8*)&ota_info_read, OTA_END_ADDR-0x1000-0x10, sizeof(ota_info_s)); 

	/****5.copy flash code and check crc****/
	if(ota_info_read.flag == 0x5555)//specific len and crc
	{
		app_ota_copy_flash(OTA_B_ADDR, OTA_B_ADDR+ota_info_read.len, OTA_A_ADDR, OTA_A_ADDR+ota_info_read.len);
		if(Boot_calc_crc(OTA_A_ADDR, OTA_A_ADDR+ota_info_read.len)!=ota_info_read.crc)
		{
			Boot_wdt_reset();
			while(1);	
		}
	}
	else//full len coyp and crc
	{
		app_ota_copy_flash(OTA_B_ADDR, OTA_END_ADDR-0x1000, OTA_A_ADDR, OTA_B_ADDR);
		if(Boot_calc_crc(OTA_A_ADDR, OTA_B_ADDR)!=Boot_calc_crc(OTA_B_ADDR, OTA_END_ADDR - 0x1000))
		{
			Boot_wdt_reset();
			while(1);
		}
	}
	/****6.erase 2st half flash****/
	//Boot_erase_code(OTA_B_ADDR, OTA_END_ADDR-0x1000);

	/****7.write new mark****/
	Boot_flash_write_data((uint8*)&section_A, OTA_A_ADDR + OTA_MARK_OFFSET, sizeof(section_A));     
    Boot_flash_write_data((uint8*)&section_B, OTA_B_ADDR + OTA_MARK_OFFSET, sizeof(section_B));
	
	/****8.set flash protect****/
	Boot_flash_set_protect(1); 
}

void app_erase_flash(uint32 start_addr,uint32 end_addr)
{
	uint32 addr = 0;
	
	if(end_addr > start_addr)
    {
        for(addr = start_addr; addr < end_addr; )
        {
            if(((addr % 0x10000) == 0) && ((addr + 0x10000) < end_addr))
            {
                flash_erase_block_64K(addr);
                addr += 0x10000;
            }
            else if(((addr % 0x8000) == 0) && ((addr + 0x8000) < end_addr))
            {
                flash_erase_block_32K(addr);
                addr += 0x8000;
            }
            else
            {
                flash_erase_sector(addr);
                addr += 0x1000;
            }
            CLEAR_WDT;
        }
    }
}

void app_erase_2st_half_flash(void)
{
	uint32 start_addr = 0;
    uint32 end_addr = 0;

	os_printf("| Device version: 0x%x |\r\n", get_software_version());
	if(0xFF00==get_software_mark(OTA_B_MARK)||0x0000==get_software_mark(OTA_B_MARK))
    {
        start_addr = OTA_B_ADDR;
        end_addr   = OTA_END_ADDR - 0x1000;  /*4K calibration data*/
    }
	if(end_addr > start_addr)
    {
		os_printf("---OTA erase flash addr:0x%x, Please Waiting...\r\n\r\n", start_addr); 
		app_erase_flash(start_addr,end_addr);
	}
}

void app_erase_picture(void)
{
	uint32 start_addr = 0;
    uint32 end_addr = 0;

	//if(OTA_B_PICTURE_MARK==get_software_mark(OTA_B_MARK))
	if(0xFFFF!=get_software_mark(OTA_B_MARK))
    {
        start_addr = OTA_B_ADDR;
        end_addr   = OTA_END_ADDR - 0x1000;/*4K calibration data*/
    }
	if(end_addr > start_addr)
    {
		os_printf("---OTA erase picture addr:0x%x, Please Waiting...\r\n\r\n", start_addr); 
		app_erase_flash(start_addr,end_addr);
	}
}
#endif

