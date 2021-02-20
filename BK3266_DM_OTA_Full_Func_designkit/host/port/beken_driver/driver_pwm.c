
/***************************************************************************************
20150515  xugaojing 
file:driver_pwm.h
detail:
	PWM0��PWM1����

  
****************************************************************************************
*/
#include "driver_beken_includes.h"
#include "driver_pwm.h"

#ifdef ENABLE_PWM
pwmData pwmdata;


/***************************************************************************************
function:
	GPIO6(10),GPIO7(11),GPIO11(18),GPIO12(19),GPIO13(20),GPIO14(21)��ΪPWM���
param:
	@PWMindex:0 ��GPIO6(10)��ΪPWM0 ���.
			    1 ��GPIO7(11)��ΪPWM1���.
			    2 ��GPIO11(18)��ΪPWM2���.
			    3 ��GPIO12(19)��ΪPWM3���.
			    4 ��GPIO13(20)��ΪPWM4���.
			    5 ��GPIO14(21)��ΪPWM5���.

return void 
*/
void PWMxOrGpio(uint8 IsPWM,uint8  PWMindex,uint8 gpioDir)
{
    if(IsPWM)
    {   
        if(0 == PWMindex)
        {
            gpio_enable_second_function(GPIO_FUNCTION_PWM0);
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x20*4)) |= (1<<10); //gpio_pconf1
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x1f*4)) = 0; //gpio_pconf4
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x26*4)) = 0; //gpio_pconf3
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x3b*4)) = 0; //gpio_pconf2
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x2b*4)) = 0; //gpio_dconf
            BK3000_PWM2_PWM_CTRL |= PWM0_EN;
        }
        else if(1 == PWMindex)
        {
            gpio_enable_second_function(GPIO_FUNCTION_PWM1);
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x20*4)) |= (1<<11); //gpio_pconf1
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x1f*4)) = 0; //gpio_pconf4
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x26*4)) = 0; //gpio_pconf3
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x3b*4)) = 0; //gpio_pconf2
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x2b*4)) = 0; //gpio_dconf
            BK3000_PWM2_PWM_CTRL |= PWM1_EN;
        }
        else if(2 == PWMindex)
        {
            gpio_enable_second_function(GPIO_FUNCTION_PWM2);
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x20*4)) |= (1<<18); //gpio_pconf1
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x1f*4)) = 0; //gpio_pconf4
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x26*4)) = 0; //gpio_pconf3
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x3b*4)) = 0; //gpio_pconf2
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x2b*4)) = 0; //gpio_dconf
            BK3000_PWM2_PWM_CTRL |= PWM2_EN;
        }
        else if(3 == PWMindex)
        {
            gpio_enable_second_function(GPIO_FUNCTION_PWM3);
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x20*4)) |= (1<<19); //gpio_pconf1
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x1f*4)) = 0; //gpio_pconf4
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x26*4)) = 0; //gpio_pconf3
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x3b*4)) = 0; //gpio_pconf2
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x2b*4)) = 0; //gpio_dconf
            BK3000_PWM2_PWM_CTRL |= PWM3_EN;
        }
        else if(4 == PWMindex)
        {
            gpio_enable_second_function(GPIO_FUNCTION_PWM4);
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x20*4)) |= (1<<20); //gpio_pconf1
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x1f*4)) = 0; //gpio_pconf4
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x26*4)) = 0; //gpio_pconf3
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x3b*4)) = 0; //gpio_pconf2
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x2b*4)) = 0; //gpio_dconf
            BK3000_PWM2_PWM_CTRL |= PWM4_EN;
        }
        else if(5 == PWMindex)
        {
            gpio_enable_second_function(GPIO_FUNCTION_PWM5);
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x20*4)) |= (1<<21); //gpio_pconf1
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x1f*4)) = 0; //gpio_pconf4
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x26*4)) = 0; //gpio_pconf3
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x3b*4)) = 0; //gpio_pconf2
            (*(volatile unsigned long *)(BK3000_GPIO_BASE_ADDR+0x2b*4)) = 0; //gpio_dconf
            BK3000_PWM2_PWM_CTRL |= PWM5_EN;
        }
        PWMxEnableWork(PWMindex,1);
    }
    else
    {
        PWMxEnableWork(PWMindex,0);
        if(0 == PWMindex)
        {
            gpio_config( 10, gpioDir );
        }	
        else if(1 == PWMindex)
        {
            gpio_config( 11, gpioDir );
        }
        else if(2 == PWMindex)
        {
            gpio_config( 18, gpioDir );
        }
        else if(3 == PWMindex)
        {
            gpio_config( 19, gpioDir );
        }
        else if(4 == PWMindex)
        {
            gpio_config( 20, gpioDir );
        }
        else if(5 == PWMindex)
        {
            gpio_config( 21, gpioDir );
        }
    }
}
/***************************************************************************************
function:
	change PWM0,PWM1,PWM2,PWM3,PWM4,PWM5 to enable or disable
param:
	@PWMindex:0 ��PWM0,1 ��PWM1,2 ��PWM2,3 ��PWM3,4 ��PWM4,5 ��PWM5
	@enableWork:0 PWM disable ,1 PWM enable
return void
*/
void PWMxEnableWork(uint8 PWMindex,uint8 enableWork)
{
    if(enableWork)
    {	
    //pwm0 enable
        if(0 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL |= PWM0_EN ;
        }
        //pwm1 enable
        else if(1 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL |= PWM1_EN ;
        }
        //pwm2 enable
        else if(2 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL |= PWM2_EN ;
        }
        //pwm3 enable
        else if(3 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL |= PWM3_EN ;
        }
        //pwm4 enable
        else if(4 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL |= PWM4_EN ;
        }
        //pwm5 enable
        else if(5 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL |= PWM5_EN ;
        }
    }
    else
    {   
        //pwm0 disable
        if(0 == PWMindex)
        {
        BK3000_PWM2_PWM_CTRL &= (~PWM0_EN) ;
        }
        //pwm1 disable
        else if(1 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL &= (~PWM1_EN) ;
        }
        //pwm2 disable
        else if(2 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL &= (~PWM2_EN) ;
        }
        //pwm3 disable
        else if(3 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL &= (~PWM3_EN) ;
        }
        //pwm4 disable
        else if(4 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL &= (~PWM4_EN) ;
        }
        //pwm5 disable
        else if(5 == PWMindex)
        {
            BK3000_PWM2_PWM_CTRL &= (~PWM5_EN) ;
        }
    }

}
/***************************************************************************************************
function:
	PWM0,PWM1ռ�ձ�����
param:
	@PWMindex:0��PWM0,1��PWM1.
	@dutyCycle:PWM�ߵ�ƽ����ʱ��,��ҪС��PWMperiod:
			    PWM Ƶ����26M/div�� 1��dutyCycle�൱��1000*1000us/(26M/div) =   xus.
		           PWMx Ƶ����32K��1��dutyCycle�൱��1000*1000us/32K = 31.25us.
return: void.
*/
RAM_CODE void PWMxdutyCycleSet(uint8 PWMindex,uint16 dutyCycle)
{
    if(0 == PWMindex)
    {
        BK3000_PWM2_PWM0_CONF = (BK3000_PWM2_PWM0_CONF&(~0xffff))|dutyCycle;
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<6)))|(0x1<<6);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(1 == PWMindex)
    {
        BK3000_PWM2_PWM1_CONF = (BK3000_PWM2_PWM1_CONF&(~0xffff))|(dutyCycle);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<10)))|(0x1<<10);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(2 == PWMindex)
    {
        BK3000_PWM2_PWM2_CONF = (BK3000_PWM2_PWM2_CONF&(~0xffff))|(dutyCycle);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<14)))|(0x1<<14);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(3 == PWMindex)
    {
        BK3000_PWM2_PWM3_CONF = (BK3000_PWM2_PWM3_CONF&(~0xffff))|(dutyCycle);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<18)))|(0x1<<18);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(4 == PWMindex)
    {
        BK3000_PWM2_PWM4_CONF = (BK3000_PWM2_PWM4_CONF&(~0xffff))|(dutyCycle);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<22)))|(0x1<<22);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(5 == PWMindex)
    {
        BK3000_PWM2_PWM5_CONF = (BK3000_PWM2_PWM5_CONF&(~0xffff))|(dutyCycle);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<26)))|(0x1<<26);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
}
/***************************************************************************************************
function:
	PWM0,PWM1��������
param:
	@PWMindex:PWMͨ��ѡ��:0��PWM0,1��PWM1.
	@PWMperiod:PWM��������,��Ҫ����dutyCycle.
			    PWM0 Ƶ����1M�� 1��PWMperiod�൱��1000*1000us/1M =   1us.
		           PWM1 Ƶ����32K��1��PWMperiod�൱��1000*1000us/32K = 31.25us.
return: void.
*/
RAM_CODE void PWMxPeriodSet(uint8 PWMindex,uint16 PWMperiod)
{
    if(0 == PWMindex)
    {
        BK3000_PWM2_PWM0_CONF = (BK3000_PWM2_PWM0_CONF&(~(0xffff<<16)))|(uint32)(PWMperiod<<16);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<6)))|(0x1<<6);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(1 == PWMindex)
    {
        BK3000_PWM2_PWM1_CONF = (BK3000_PWM2_PWM1_CONF&(~(0xffff<<16)))|(uint32)(PWMperiod<<16);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<10)))|(0x1<<10);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(2 == PWMindex)
    {
        BK3000_PWM2_PWM2_CONF = (BK3000_PWM2_PWM2_CONF&(~(0xffff<<16)))|(uint32)(PWMperiod<<16);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<14)))|(0x1<<14);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(3 == PWMindex)
    {
        BK3000_PWM2_PWM3_CONF = (BK3000_PWM2_PWM3_CONF&(~(0xffff<<16)))|(uint32)(PWMperiod<<16);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<18)))|(0x1<<18);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(4 == PWMindex)
    {
        BK3000_PWM2_PWM4_CONF = (BK3000_PWM2_PWM4_CONF&(~(0xffff<<16)))|(uint32)(PWMperiod<<16);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<22)))|(0x1<<22);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
    else if(5 == PWMindex)
    {
        BK3000_PWM2_PWM5_CONF = (BK3000_PWM2_PWM5_CONF&(~(0xffff<<16)))|(uint32)(PWMperiod<<16);
        //BK3000_PWM2_PWM_CTRL = (BK3000_PWM2_PWM_CTRL&(~(0xf<<26)))|(0x1<<26);	//ʱ�ӷ�Ƶ��Ӱ��PWM��ʱ��
    }
}

/*
	PWM��ʼ��
*/
void PWMxinit(uint8 PWMindex, uint8 enableWork,uint16 PWMperiod,uint16 dutyCycle)
{
    pwmdata.pwmDirect = PWM_INC;
    pwmdata.pwmCount = 0;
    pwmdata.pwmHoldTime = 0;
    PWMxOrGpio(enableWork,PWMindex,1);
    PWMxdutyCycleSet(PWMindex,dutyCycle);
    PWMxPeriodSet(PWMindex,PWMperiod);
    BK3000_PMU_PERI_PWDS  &= ~bit_PMU_PCM2_PWD;
    //BK3000_PMU_PERI_PWDS |= (bit_PWM2_CLK_SEL_XTAL);  // 0:32K  1:26M/DIV
}

/*
RAM_CODE void PWMGradualChange(uint8 pwmDirect) //���ģ�����
{
    //pwmdata.pwmDirect = pwmdirect;
    switch(pwmdata.pwmDirect)
    {
        case PWM_INC: //����
            if(pwmdata.pwmCount<(PWM_PERIOD/3))
                pwmdata.pwmCount++;
            else if(pwmdata.pwmCount<(PWM_PERIOD*2/3))
                pwmdata.pwmCount += 2;
            else
                pwmdata.pwmCount += 3;
            if(pwmdata.pwmCount >=PWM_PERIOD)
            {
                pwmdata.pwmCount=PWM_PERIOD;
                pwmdata.pwmDirect = PWM_MAX;
            }
            break;
            
        case PWM_DEC://����
            if(pwmdata.pwmCount<(PWM_PERIOD/3))
                pwmdata.pwmCount--;
            else if(pwmdata.pwmCount<(PWM_PERIOD*2/3))
                pwmdata.pwmCount -= 2;
            else
                pwmdata.pwmCount -= 3;
            if(pwmdata.pwmCount <= 0)
            {
                pwmdata.pwmCount = 0;
                pwmdata.pwmDirect = PWM_MIN;
            }
            break;
            
        case PWM_MAX:// ��������һС��ʱ��
            pwmdata.pwmCount=PWM_PERIOD;
            pwmdata.pwmHoldTime++;
            if(pwmdata.pwmHoldTime>=PWM_MAX_HOLD)
            {
                pwmdata.pwmHoldTime = 0;
                pwmdata.pwmDirect = PWM_DEC;
            }
            break;
            
        case PWM_MIN://�����һС��ʱ��
            pwmdata.pwmCount=0;
            pwmdata.pwmHoldTime++;
            if(pwmdata.pwmHoldTime>=PWM_MIN_HOLD)
            {
                pwmdata.pwmHoldTime = 0;
                pwmdata.pwmDirect = PWM_INC;
            }
            break;
            
        default:
            break;
    }

    PWMxdutyCycleSet(2,pwmdata.pwmCount);
    PWMxdutyCycleSet(3,pwmdata.pwmCount);
    PWMxdutyCycleSet(4,pwmdata.pwmCount);

}
*/
#endif 

