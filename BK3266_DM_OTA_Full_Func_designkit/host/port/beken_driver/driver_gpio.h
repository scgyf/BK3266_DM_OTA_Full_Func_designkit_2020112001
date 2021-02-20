#ifndef _DRIVER_GPIO_H_
#define _DRIVER_GPIO_H_


#define GPIO_CON_UART2                   ( 0 << 0 )
#define GPIO_CON_I2C2                    ( 1 << 0 )
#define GPIO_CON_I2S                     ( 0 << 1 )
#define GPIO_CON_UART1_MONITOR_FLOWCTL   ( 1 << 1 )
#define GPIO_CON_JTAG                    ( 0 << 2)
#define GPIO_CON_NOJTAG                  ( 1 << 2 )
#define GPIO_CON_I2C_FM                  ( 1 << 3 )  
#define GPIO_CON_SDIO                    ( 1 << 3 )
#define GPIO_CON_INT_FM_ON               ( 1 << 4 )
#define GPIO_CON_INT_FM_OFF              ( 0 << 4 )

#define GPIO_NUM                         (22)
#define DEFAULT_WAKEUP_PIN                         (22)

enum GPIO_INDEX
{
    GPIO0 = 0,
    GPIO1 =1,
    GPIO2=6,
    GPIO3=7,
    GPIO4=8,
    GPIO5=9,
    GPIO6=10,
    GPIO7=11,
    GPIO8=12,
    GPIO9=13,
    GPIO10=14,
    ADKEY0=17,
    GPIO11=18,
    GPIO12=19,
    GPIO13=20,
    GPIO14=21,
    GPIO15=22,
    ADKEY1=23,
    ADKEY2=24,
    ADKEY3=25,
    ADKEY4=26,
    ADKEY5=27,
    ADKEY6=28,
    ADKEY7=29,
    ADKEY8=30,
    ADKEY9=31,
};

enum
{
    GPIO_FUNCTION_UART2 = 0,
    GPIO_FUNCTION_I2C2,
    GPIO_FUNCTION_PCM2,
    GPIO_FUNCTION_UART1_FLOW_CTL,
    GPIO_FUNCTION_UART1_MONITOR,
    GPIO_FUNCTION_SPI,
    GPIO_FUNCTION_PWM0,
    GPIO_FUNCTION_PWM1,
    GPIO_FUNCTION_PWM2,
    GPIO_FUNCTION_PWM3,
    GPIO_FUNCTION_PWM4,
    GPIO_FUNCTION_PWM5,
    GPIO_FUNCTION_SDIO,
    GPIO_FUNCTION_I2C_FM,
    GPIO_FUNCTION_JTAG
};

enum
{
    GPIO_INT_LEVEL_LOW = 0,
    GPIO_INT_LEVEL_HIGH = 1
};

void gpio_config( int index, int dir );
void gpio_output( int index, uint32 val );
uint32 gpio_input( int index );
void gpio_output_reverse( int index );
void  gpio_enable_second_function( int gpio_function );
void gpio_button_wakeup_enable(void);
void gpio_int_enable( int index, int level );
void gpio_isr( void );

#define ENTER_DEEP_SLEEP    do{BK3000_GPIO_WKUPEN |= 0x10000000; BK3000_GPIO_DPSLP = 0x3261;} while(0)/* do{ BK3000_GPIO_DPSLP = 0x3251; }while(0) */
#define GPIO_CHARGER_FLAG   (BK3000_GPIO_DRB & 0x02) /* (BK3000_GPIO_OTDET & 0x02) */

/// GPIO_A0
typedef union {
    struct {
        volatile unsigned int SSEnSystemVUSBLDO       : 1; /**< VUSB System LDO Soft Start Enbale */
        volatile unsigned int SSEnAna18LDO            : 1; /**< Analog 1.8V LDO Soft Start Enable */
        volatile unsigned int SSEnDigCoreLDO          : 1; /**< DigLDO Soft start Enable */
        volatile unsigned int SystemLDOVUSBtrimming10 : 2; /**< VUSB Vsystem LDO Output Trimming, */
        volatile unsigned int AnaBuckv0p75vtrimming10 : 2; /**< ģ��BUCK burstģʽ���ripple��ѹ���ڿ���λ */
        volatile unsigned int DigBuckv0p6vtrimming10  : 2; /**< ����BUCK burstģʽ���ripple��ѹ���ڿ���λ */
        volatile unsigned int SSEnSystemVBATLDO       : 1; /**< VBAT SYSTEM LDO Softstart Enable */
        volatile unsigned int calvbacharger           : 5; /**< Charger BG Trimming bits */
        volatile unsigned int spipwdanabuck           : 1; /**< Analog BUCK power down control */
        volatile unsigned int CHGIICctl10             : 2; /**< Charger: larger charge current trimming in Internal charger mode; 00=120mA; 01=200mA
; 10=280mA; 11=360mA */
        volatile unsigned int CHGLC2CVdlyEn           : 1; /**< Charger: CI to CV Delay Enable; 1=Enable */
        volatile unsigned int CHGLC2CVdly20           : 3; /**< Charger: delay trimming from Constant larger current charger mode to CV mode; 000=0.
16ms; 001=0.32mS; 010=0.64mS; 111=20.48mS */
        volatile unsigned int CHGCVEN                 : 1; /**< Charger: Charger CV Mode Enable; 1=enable */
        volatile unsigned int CHGExtEn                : 1; /**< Charger: External Charger Enable: 1=enable */
        volatile unsigned int CHGEN                   : 1; /**< Charger: Charger function Enable; 1=enable */
        volatile unsigned int CHGCALEN                : 1; /**< Charger: Calibration Enable; 1=enable */
        volatile unsigned int buckexckdiv50           : 6; /**< When buck clock source select xtal26M, its divider setting; buck frequency is 52M/N
, N=1~64 */
    };
    volatile unsigned int value;
} GPIO_A0_TypeDef;

/// GPIO_A1
typedef union {
    struct {
        volatile unsigned int ocpena0        : 1; /**< ģ��BUCK��������ʹ�� */
        volatile unsigned int ocpsela20      : 3; /**< ģ��BUCK������������λ */
        volatile unsigned int pfmsela30      : 4; /**< ģ��BUCK PFM��PWMģʽ�л��ĵ���������ֵ */
        volatile unsigned int clkcala30      : 4; /**< ģ��BUCK PWMģʽ��ʱ��΢��У׼ */
        volatile unsigned int clksela20      : 3; /**< ģ��BUCK PWMģʽ��ʱ��ѡ��0.5M��1M��2M��2.5M,3M,3.5M,4M,5MHz */
        volatile unsigned int vnrsela10      : 2; /**< ģ��BUCK�ڲ�NMOS�ֲ���ѹѡ��2.7V��2.8V��2.9V��3.0V */
        volatile unsigned int voutsela30     : 4; /**< ģ��BUCK�ڲ�NMOS�ֲ���ѹѡ��2.7V��2.8V��2.9V��3.0V */
        volatile unsigned int ealimaen       : 1; /**< ģ��BUCK ��������������ѡ�� */
        volatile unsigned int extCKaen       : 1; /**< ģ��BUCK �ⲿʱ��ѡ�� */
        volatile unsigned int ringclraen     : 1; /**< ģ��BUCK ����SW��ring��ʹ�� */
        volatile unsigned int pfmmodaen      : 1; /**< ģ��BUCK PFM ģʽʹ�� */
        volatile unsigned int spiburstmodaen : 1; /**< ģ��BUCK burst ģʽʹ��,���ܺ�PFMģʽʹ��ͬʱΪ�� */
        volatile unsigned int spipwdSysLDO   : 1; /**< System LDO Control, default 0 */
        volatile unsigned int spipwdDigBUCK  : 1; /**< Power down control of Digital BUCK, defualt off */
        volatile unsigned int spipwdBUCKEXCK : 1; /**< Power down control of BUCK external clock buffer */
        volatile unsigned int bustconspiEn   : 1; /**< BUCK burst mode Enable spi control Enable */
        volatile unsigned int spipwdAnaLDO18 : 1; /**< spi control of power down of Analog LDO, default off */
        volatile unsigned int spipwdDigLDO12 : 1; /**< spi control of power down of DigLDO, default on */
    };
    volatile unsigned int value;
} GPIO_A1_TypeDef;

/// GPIO_A2
typedef union {
    struct {
        volatile unsigned int ocpend0        : 1; /**< ����BUCK��������ʹ�� */
        volatile unsigned int ocpseld20      : 3; /**< ����BUCK������������λ */
        volatile unsigned int pfmseld30      : 4; /**< ����BUCK PFM��PWMģʽ�л��ĵ���������ֵ */
        volatile unsigned int clkcald30      : 4; /**< ����BUCK PWMģʽ��ʱ��΢��У׼ */
        volatile unsigned int clkseld20      : 3; /**< ����BUCK PWMģʽ��ʱ��ѡ��0.5M��1M��2M��2.5M,3M,3.5M,4M,5MHz */
        volatile unsigned int vnrseld10      : 2; /**< ����BUCK�ڲ�NMOS�ֲ���ѹѡ��2.7V��2.8V��2.9V��3.0V */
        volatile unsigned int voutseld30     : 4; /**< ����BUCK�ڲ�NMOS�ֲ���ѹѡ��2.7V��2.8V��2.9V��3.0V */
        volatile unsigned int ealimden       : 1; /**< ����BUCK ��������������ѡ�� */
        volatile unsigned int extCKden       : 1; /**< ����BUCK �ⲿʱ��ѡ�� */
        volatile unsigned int ringclrden     : 1; /**< ����BUCK ����SW��ring��ʹ�� */
        volatile unsigned int pfmmodden      : 1; /**< ����BUCK PFM ģʽʹ�� */
        volatile unsigned int spiburstmodden : 1; /**< ����BUCK burst ģʽʹ��,���ܺ�PFMģʽʹ��ͬʱΪ�� */
        volatile unsigned int Enbborvbat2p7v : 1; /**< When 0, VBAT BOR at 2.7V; Otherwise not bor. */
        volatile unsigned int calvbgbat40    : 5; /**< VBG on VBAT Output Trimming */
    };
    volatile unsigned int value;
} GPIO_A2_TypeDef;

/// GPIO_A3
typedef union {
    struct {
        volatile unsigned int AudiopwdMICR        : 1; /**< Power down of Right channel MIC */
        volatile unsigned int AudiopwdMICL        : 1; /**< Power down of Left channel MIC */
        volatile unsigned int AudiopwdAudCB       : 1; /**< Power down of Audio CB */
        volatile unsigned int AudiopwdAudDigLDO   : 1; /**< Power down of audio 1.2V ldo */
        volatile unsigned int AudiopwdDigMIC      : 1; /**< Power down of DigMIC Fucntion */
        volatile unsigned int AudiopwdAudDAC      : 1; /**< Power down of Audio DAC */
        volatile unsigned int AudiopwdAudPA       : 1; /**< Power down of Audio PA */
        volatile unsigned int AudiopwdMICBIAS     : 1; /**< Power down of Audio MIC Bias Generator */
        volatile unsigned int AudiopwdAGC         : 1; /**< Power down of Audio DAC AGC */
        volatile unsigned int spipwdLED1          : 1; /**< Power down control of LED1 Driver */
        volatile unsigned int spipwdLED2          : 1; /**< Power down control of LED2 Driver */
        volatile unsigned int spipwdLED           : 1; /**< Power down control of LED Driver */
        volatile unsigned int spipwdSARADCLDO     : 1; /**< Power down control of SARADC LDO */
        volatile unsigned int spipwdSarADCBuffer  : 1; /**< Power down control of SARADC Input buffer */
        volatile unsigned int spipwdSarADCA       : 1; /**< Power down control of SARADC at analog part */
        volatile unsigned int AudiopulllowEn      : 1; /**< Audio PA Output pull low Enable, 1=enable */
        volatile unsigned int V12IOSel            : 1; /**< V12 IO votalge auto selectrion, 0=vddSPI; 1=VDIG */
        volatile unsigned int V12IOSelSPIEN       : 1; /**< V12 IO voltage Selectrion control, 1=spi; 0=auto */
        volatile unsigned int NC                  : 1; /**< NC */
        volatile unsigned int CKRSC78MENB         : 1; /**< RSCPLL 78MHz Clock Enabe, 0=enable */
        volatile unsigned int DeepSleepEnVDDIOLDO : 1; /**< Note Used */
        volatile unsigned int pwdCB1              : 1; /**< Power down of Central Bias */
        volatile unsigned int AudCKSel            : 1; /**< Audio synchronous 26MHz clock inversion enable */
        volatile unsigned int NC_                 : 1; /**< NC */
        volatile unsigned int spixtalFilEn        : 1; /**< Crystal power supply filter Enable */
        volatile unsigned int spipwdbtspiLDO      : 1; /**< Power down control of BT spi LDO */
        volatile unsigned int LDOEN               : 1; /**< BT LDO_EN */
        volatile unsigned int spipwdVDDIOFlaLDO   : 1; /**< Power down control of VDDIO FLASH LDO */
        volatile unsigned int spipwdrsc100K       : 1; /**< Power down control of RSC100K */
        volatile unsigned int spipwdxtalbufd      : 1; /**< Power down cotrol of crystal digital buffer */
        volatile unsigned int spipwdxtalbufa      : 1; /**< Power down cotrol of crystal analog buffer */
        volatile unsigned int spipwdxtal          : 1; /**< Power down cotrol of crystal core */
    };
    volatile unsigned int value;
} GPIO_A3_TypeDef;

/// GPIO_A4
typedef union {
    struct {
        volatile unsigned int pwdtempSensor    : 1; /**< Power down control of Temp Sensor */
        volatile unsigned int vselVDDIOFLALDO  : 1; /**< VDDIO_FLA LDO Output Trimming, 0=2.8V; 1=3.0V; */
        volatile unsigned int spidpllldo       : 1; /**< CPU Digpll LDO Power down control */
        volatile unsigned int spipwdPLL        : 1; /**< RSC DigPLL power down control */
        volatile unsigned int spidpllldo10     : 2; /**< CPU Digpll LDO Output Trimming */
        volatile unsigned int spixtalxamp20    : 3; /**< Crystal amp control, 111=largest; 000=smallest */
        volatile unsigned int ckreqbt          : 1; /**<  */
        volatile unsigned int ckreqEn          : 1; /**<  */
        volatile unsigned int vselSARADCLDO10  : 2; /**< SARADC LDO Output Trimming */
        volatile unsigned int pwdUSBOTG        : 1; /**< Power Down Control of USBOTG */
        volatile unsigned int dacpopConspiEn   : 1; /**< When 1, dacpop control is set by spi */
        volatile unsigned int V12IOSEL0        : 1; /**< When A3<1>=1, sel0=0, V12IO=VDIG; */
        volatile unsigned int V12IOSEL1        : 1; /**< When A3<1>=1, sel1=0, V12IO=vdddig; */
        volatile unsigned int spiUSBSPIEn      : 1; /**< when 1, USB Mode is controlled by spi, <20:18> */
        volatile unsigned int spiUSBState20    : 3; /**< 001= USB Host Mode; 110=USB Slave Mode; */
        volatile unsigned int SARADCDCCalEn    : 1; /**< SARADC DC Calibaration Enable */
        volatile unsigned int LEDCURSEL        : 1; /**< LED Drvier ability trimming */
        volatile unsigned int spiDigMICCKINVEN : 1; /**< DigMIC Clock Inversion Enable */
        volatile unsigned int spipwdRampDAC    : 1; /**< Power Down Control of RampDAC */
        volatile unsigned int spiRampUpstart   : 1; /**< RampDAC rampUp Start Enable */
        volatile unsigned int spiRampDownstart : 1; /**< RampDAC rampDown start Enable */
        volatile unsigned int vbgEn            : 1; /**< ref from VBG Enable, 1=enable */
        volatile unsigned int rampDACEn        : 1; /**< ref from RampDAC Enbale, 1=enable */
        volatile unsigned int ratime20         : 3; /**< <2>=1, ref=1.2V; <1>=1, ref=0.9; <0>=1, refEn */
    };
    volatile unsigned int value;
} GPIO_A4_TypeDef;

/// GPIO_A5
typedef union {
    struct {
        volatile unsigned int lockspi          : 1; /**< DPLL lock spi */
        volatile unsigned int openloopdigpllen : 1; /**< DPLL OpenLoop Enable */
        volatile unsigned int pwdpllspi        : 1; /**< DPLL Power down Control */
        volatile unsigned int pwdpll           : 1; /**< DPLL Power down Control */
        volatile unsigned int pwddigpllcp      : 1; /**< DPLL CP Power down control */
        volatile unsigned int pwddigpllpfd     : 1; /**< DPLL PFD Power down control */
        volatile unsigned int pwddigpllvco     : 1; /**< DPLL VCO Power down control */
        volatile unsigned int CK48MENB         : 1; /**< USB48MHz Clock Enable, Low Enable */
        volatile unsigned int NC               : 4; /**< No description */
        volatile unsigned int spiselDigLDO30   : 4; /**< In sleep mode, digital ldo output trimming */
        volatile unsigned int CP10             : 2; /**< DPLL CP Control */
        volatile unsigned int dpllR1pr20       : 3; /**< DPLL LP Trimming */
        volatile unsigned int dpllictrlCP30    : 4; /**< DPLL CP Current Triming */
        volatile unsigned int spirst           : 1; /**< DPLL Reset Signal, high Reset, 0-1-0 */
        volatile unsigned int tstEn            : 1; /**< TEST Buffer Test Enable */
        volatile unsigned int atsel10          : 2; /**< TEST Selection, 00=RSCDPLL, RSCDPLL/4; 01=0; 10=DPLL, 6MHz; 11=RSC100k */
        volatile unsigned int tstRSC100KEn     : 1; /**< RSC100K Test Enable */
        volatile unsigned int tstRSCDPLL78MEn  : 1; /**< RSCDPLL 78M Test Enable, test output RSCDPLL/4; */
        volatile unsigned int tstDPLL48MEn     : 1; /**< DPLL 48MHz Test Enable, test output 48M/8=6MHz */
    };
    volatile unsigned int value;
} GPIO_A5_TypeDef;

/// GPIO_A6
typedef union {
    struct {
        volatile unsigned int amsel      : 1; /**< 0Ϊ�Զ����ƣ�1Ϊ�ֶ����� */
        volatile unsigned int msw70      : 8; /**< �ֶ�Ƶ�ʿ��� */
        volatile unsigned int ictrl20    : 3; /**< �����������ƣ�Ĭ��ֵΪ0 */
        volatile unsigned int divctrl10  : 2; /**< ���������ƣ�Ĭ��ֵΪ0��00=156M/2��01=156M/3��10=156/4, 11=156M/6 */
        volatile unsigned int osctrig    : 1; /**< ��������trig�ź� */
        volatile unsigned int osccaltrig : 1; /**< �Զ�У׼trig�ź� */
        volatile unsigned int cnti80     : 9; /**< ����ring osc Ƶ�ʣ�Ĭ��ֵΪC0 */
        volatile unsigned int spirst     : 1; /**< DPLL Calibration Block Reset. Low Trige Reset */
        volatile unsigned int NC         : 5; /**< NC */
        volatile unsigned int spipwdbtldo: 1;
    };
    volatile unsigned int value;
} GPIO_A6_TypeDef;

/// GPIO_A7
typedef union {
    struct {
        volatile unsigned int Audiocssw       : 1; /**< ��Ƶ���ֵ��ܵĵ���trimming��0��Default��1����С1/3. */
        volatile unsigned int LineEn          : 1; /**< LINEʹ�� */
        volatile unsigned int daccssw1V       : 1; /**< audioDAC����trimming��if 0�� ��С1/2�� */
        volatile unsigned int RampEn          : 1; /**< DAC Output Ramp Enable */
        volatile unsigned int adccssel        : 1; /**< audioADC�ĵ���trimming��if 0����С1/2�� */
        volatile unsigned int LineGain10      : 2; /**< Line����������ƣ�0~-9db��with -3dB/step */
        volatile unsigned int vselmicldo10    : 2; /**< MicReference Generator��LDO���������ѹ�Ŀ��� */
        volatile unsigned int pwdRpap         : 1; /**< AudioDAC�����������P��Driver��ģʽ���ƣ�1ΪpowerDown��0ΪON */
        volatile unsigned int pwdRpan         : 1; /**< AudioDAC�����������N��Driver��ģʽ���ƣ�1ΪpowerDown��0ΪON */
        volatile unsigned int pwdLpap         : 1; /**< AudioDAC�����������P��Driver��ģʽ���ƣ�1ΪpowerDown��OΪON */
        volatile unsigned int pwdLpan         : 1; /**< AudioDAC�����������N��Driver��ģʽ���ƣ�1ΪpowerDown��0ΪON */
        volatile unsigned int BTAudStbEn      : 1; /**< AudioDAC StandBy Enable,if 1, AudioDAC standBy */
        volatile unsigned int RampDACCLKSEL   : 1; /**< AduioDAC RampDAC Clock Selectiion */
        volatile unsigned int audDACckinven   : 1; /**< AudioDACǰ�˲�����ʱ����ѡ��Default�������ز������½��ط����� */
        volatile unsigned int audADCReftrm    : 1; /**< AudioADC��reference��ѹ���ƣ�1��Vref=1.2V��VFS=4.9dbm��0��Vref=1.8V��VFS=8.4dbm */
        volatile unsigned int audDACg30       : 4; /**< AudioDAC��������ƣ�0dB~-30dB��stepΪ-2dB�� */
        volatile unsigned int vselAudDigLDO10 : 2; /**< Audio�ڲ��õ�1.5V��ѹLDO�����ֵ���ƣ�00-1.18��01-1.18��10-1.29��11-1.38V; */
        volatile unsigned int adcckinven      : 1; /**< AudioADCǰ�˲�����ʱ����ѡ��Default�������ز������½��ط����� */
        volatile unsigned int CurMicREn       : 1; /**< Current Mode MIC Enable, Right channel */
        volatile unsigned int CurMicLEn       : 1; /**< Current Mode MIC Enable, left channel */
        volatile unsigned int limtlvcon10     : 2; /**< Limiter�ķ��ȿ��ƣ����ڴ��adcref��00--2dbFS��01--4dbFS��10--6dbFS��11--9dbFS������С��ref��
10--2dbFS��11--6dbFS */
        volatile unsigned int limtbpen        : 1; /**< MicrophonePath��Limiter��Bypass��ʹ�ܿ��� */
        volatile unsigned int MicTrim10       : 2; /**< Microphoneƫ�õ�ѹ�������00-2.6��01-2.4��10-2.1V��11-1.8V */
        volatile unsigned int SingleEn        : 1; /**< MicphoneAGC�Ĺ�ģ��ѹѡ��0����ģΪvbg��1��VDD/2. */
    };
    volatile unsigned int value;
} GPIO_A7_TypeDef;
/// GPIO_Ax
struct GPIO_Ax_TypeDef {
    volatile GPIO_A0_TypeDef  *a0;
    volatile GPIO_A1_TypeDef  *a1;
    volatile GPIO_A2_TypeDef  *a2;
    volatile GPIO_A3_TypeDef  *a3;
    volatile GPIO_A4_TypeDef  *a4;
    volatile GPIO_A5_TypeDef  *a5;
    volatile GPIO_A6_TypeDef  *a6;
    volatile GPIO_A7_TypeDef  *a7;
};

extern const struct GPIO_Ax_TypeDef GPIO_Ax;

#endif
