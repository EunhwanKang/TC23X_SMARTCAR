/*----------------------------------------------------------------*/
/*						Include Header File						  */
/*----------------------------------------------------------------*/
#include "DrvGtmTom.h"
#include "SysSe/Bsp/Bsp.h"
#include "Gtm/Tom/Timer/IfxGtm_Tom_Timer.h"
#include "Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.h"

/*----------------------------------------------------------------*/
/*						Define						  			  */
/*----------------------------------------------------------------*/
#define ISR_ASSIGN(no, cpu)  ((no << 8) + cpu)
#define ISR_PRIORITY(no_cpu) (no_cpu >> 8)
#define ISR_PROVIDER(no_cpu) (no_cpu % 8)
#define ISR_PRIORITY_TIMER_10MS      1  /**< \brief Define the 1ms timer interrupt priority.  */
#define ISR_PROVIDER_TIMER_10MS      IfxSrc_Tos_cpu0 /**< \brief Define the 1ms timer interrupt provider.  */
#define INTERRUPT_TIMER_10MS         ISR_ASSIGN(ISR_PRIORITY_TIMER_10MS, ISR_PROVIDER_TIMER_10MS)           /**< \brief Define the 1ms timer interrupt priority.  */


#define ISR_PRIORITY_TIMER          2/**< \brief Define the 1ms timer interrupt priority.  */
#define ISR_PROVIDER_TIMER          IfxSrc_Tos_cpu0 /**< \brief Define the 1ms timer interrupt provider.  */
#define INTERRUPT_TIMER             ISR_ASSIGN(ISR_PRIORITY_TIMER, ISR_PROVIDER_TIMER)                   /**< \brief Define the 1ms timer interrupt priority.  */


/*----------------------------------------------------------------*/
/*						Typedefs						  		  */
/*----------------------------------------------------------------*/
typedef struct
{
    struct
    {
        float32 gtmFreq;
        float32 gtmGclkFreq;
    }info;
    struct
    {
        IfxGtm_Tom_Timer timerOneMs;        /**< \brief Timer driver */
    }drivers;
    struct
    {
        uint32 slotOneMs;
    }isrCounter;
} App_GtmTomTimer;

/*PWMHl*/
typedef enum
{
    GtmTomPwmHl_State_uninit = 0,
    GtmTomPwmHl_State_off,
    GtmTomPwmHl_State_normal,
    GtmTomPwmHl_State_count
}GtmTomPwmHl_State;



typedef struct
{
    struct
    {
        float32           gtmFreq;
        float32           gtmGclkFreq;
        float32           gtmCmuClk0Freq; /**< \brief CMU CLK 0 frequency*/
        Ifx_TimerValue    timerValue;
        GtmTomPwmHl_State state;
    }info;
    Ifx_TimerValue    tOn[2];  /**< \brief PwmHl 0,2 onTime value */
    struct
    {
        IfxGtm_Tom_Timer timer;        /**< \brief Timer driver */
        IfxGtm_Tom_PwmHl pwm;
    }drivers;
    struct
    {
        uint32 counter;
    }isrCounter;
}App_GtmTomPwmHl;


/*----------------------------------------------------------------*/
/*						Static Function Prototype				  */
/*----------------------------------------------------------------*/
#if 0
static void GtmTomTimer_initTimer(void);
static void GtmTomTestPwm_init(void);
static void GtmTomPwmHl_initTimer(void);
static void GtmTomPwmHl_init(void);
#endif
/*----------------------------------------------------------------*/
/*						Variables				  				  */
/*----------------------------------------------------------------*/
App_GtmTomTimer g_GtmTomTimer; /**< \brief Demo information */
App_GtmTomPwmHl g_GtmTomPwmHl; /**< \brief Demo information */

uint32_t u32nuMyTestPwmDuty = 500u; /*Unit: 0.1%, 500 -> 50.0% duty*/

/*----------------------------------------------------------------*/
/*						Functions				  				  */
/*----------------------------------------------------------------*/

/*---------------------Interrupt Define--------------------------*/
IFX_INTERRUPT(ISR_Timer_10ms, 0, ISR_PRIORITY_TIMER_10MS);
IFX_INTERRUPT(ISR_Timer, 0, ISR_PRIORITY_TIMER);


/*Interrupt Isr*/
void ISR_Timer_10ms(void)
{
    IfxCpu_enableInterrupts();

    IfxGtm_Tom_Timer_acknowledgeTimerIrq(&g_GtmTomTimer.drivers.timerOneMs);
    g_GtmTomTimer.isrCounter.slotOneMs++;
}

void ISR_Timer(void)
{
    IfxCpu_enableInterrupts();

    IfxGtm_Tom_Timer_acknowledgeTimerIrq(&g_GtmTomPwmHl.drivers.timer);
    g_GtmTomPwmHl.isrCounter.counter++;

}

/*---------------------Test Code--------------------------*/
void GtmTomMyPwmTest(void)
{
    Ifx_TimerValue triggerPoint= (u32nuMyTestPwmDuty * 1000u) /256u;

    IfxGtm_Tom_Timer_disableUpdate(&g_GtmTomTimer.drivers.timerOneMs);

    // Set PWM duty
    IfxGtm_Tom_Timer_setTrigger(&g_GtmTomTimer.drivers.timerOneMs, triggerPoint);
    IfxGtm_Tom_Timer_applyUpdate(&g_GtmTomTimer.drivers.timerOneMs);
}

void GtmTomPwmHl_run(void)
{
    IfxGtm_Tom_PwmHl *pwmHl = &g_GtmTomPwmHl.drivers.pwm;
    IfxGtm_Tom_Timer *timer = &g_GtmTomPwmHl.drivers.timer;

    /* Set PWM duty */
	switch (g_GtmTomPwmHl.info.state)
	{

	case GtmTomPwmHl_State_uninit:
		/* GtmTomPwmHl is NOT initialized */

		break;

	case GtmTomPwmHl_State_normal:
		/* Set 0% duty cycle, center aligned */
		IfxGtm_Tom_PwmHl_setMode(pwmHl, Ifx_Pwm_Mode_centerAligned);
		IfxGtm_Tom_Timer_disableUpdate(timer);
		IfxGtm_Tom_PwmHl_setOnTime(pwmHl, g_GtmTomPwmHl.tOn);
		IfxGtm_Tom_Timer_applyUpdate(timer);
		break;

	case GtmTomPwmHl_State_off:
	default:
		/* Set PWM to off */
		IfxGtm_Tom_PwmHl_setMode(pwmHl, Ifx_Pwm_Mode_off);
		IfxGtm_Tom_Timer_disableUpdate(timer);
		IfxGtm_Tom_PwmHl_setOnTime(pwmHl, NULL_PTR);
		IfxGtm_Tom_Timer_applyUpdate(timer);
		break;
	}

}

/*---------------------Init Function--------------------------*/
void DrvGtmTomInit(void)
{
    IfxGtm_enable(&MODULE_GTM);
    // we set the global clock to 100MHz
    IfxGtm_Cmu_setGclkFrequency(&MODULE_GTM, 100000000.0f);
    // set CMU0 frequency
    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, 100000000.0f);
    // enable CMU0 clock
    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);
    // enable FX clock
    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_FXCLK);

	#if 0
    /* disable interrupts */
	float32_t f32gtmfrequency = 0.0f;
    boolean  interruptState = IfxCpu_disableInterrupts();

    /** - GTM clocks */
    Ifx_GTM *gtm = &MODULE_GTM;
    f32gtmfrequency = IfxGtm_Cmu_getModuleFrequency(gtm);
    IfxGtm_enable(gtm);

    /* Set the global clock frequencies */
    IfxGtm_Cmu_setGclkFrequency(gtm, f32gtmfrequency);

	GtmTomPwmHl_init();
	GtmTomTestPwm_init();
	#endif
}
#if 0
static void GtmTomTimer_initTimer(void)
{
    {   // Create Gtm Timer Output Module (TOM) configuration for timer
        IfxGtm_Tom_Timer_Config timerConfig;

        // TOM timer configuration 초기화
        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);

        // timer configuration에 대한 세부 설정 셋팅
        timerConfig.base.frequency       = 100;     // Set PWM period
        timerConfig.base.isrPriority     = ISR_PRIORITY(INTERRUPT_TIMER_10MS);
        timerConfig.base.isrProvider     = ISR_PROVIDER(INTERRUPT_TIMER_10MS);
        timerConfig.base.minResolution   = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled = FALSE;
        timerConfig.tom                  = IfxGtm_Tom_1;    // Set TOM1 for TOM object
        timerConfig.timerChannel         = IfxGtm_Tom_Ch_7; // Set Channel 7
        timerConfig.clock                = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2;

        // Set output port, p33.10
        timerConfig.triggerOut                      = &IfxGtm_TOM1_7_TOUT32_P33_10_OUT;
        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 500000/256; /* 5msec source: Fxclk2 100MHz/256 */
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE; // Rising edge에서 interrupt 발생

        // 변경된 설정을 적용하기 위해 다시 초기화
        IfxGtm_Tom_Timer_init(&g_GtmTomTimer.drivers.timerOneMs, &timerConfig);

        // Start timer
        IfxGtm_Tom_Timer_run(&g_GtmTomTimer.drivers.timerOneMs);
    }
}


static void GtmTomTestPwm_init(void)
{
    /* disable interrupts */
    boolean  interruptState = IfxCpu_disableInterrupts();

    // GTM clock frequency 설정
    Ifx_GTM *gtm = &MODULE_GTM;
    g_GtmTomTimer.info.gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);
    IfxGtm_enable(gtm);

    // Get Global clock frequency
    g_GtmTomTimer.info.gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);

    // Gtm timer initialization
    GtmTomTimer_initTimer();

    //printf("Gtm Tom Timer is initialised\n");

    /* enable interrupts again */
    IfxCpu_restoreInterrupts(interruptState);

    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
}



static void GtmTomPwmHl_initTimer(void)
{
    {   /* GTM TOM configuration */
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_PwmHl_Config pwmHlConfig;

        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        timerConfig.base.frequency                  = 10000;
        timerConfig.base.isrPriority                = ISR_PRIORITY(INTERRUPT_TIMER);
        timerConfig.base.isrProvider                = ISR_PROVIDER(INTERRUPT_TIMER);
        timerConfig.base.minResolution              = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled            = FALSE;
        timerConfig.tom                             = IfxGtm_Tom_0;
        timerConfig.timerChannel                    = IfxGtm_Tom_Ch_0;
        timerConfig.clock                           = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk0;

        timerConfig.triggerOut                      = &IfxGtm_TOM0_0_TOUT18_P00_9_OUT;
        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 500;
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE;

        IfxGtm_Tom_Timer_init(&g_GtmTomPwmHl.drivers.timer, &timerConfig);

        IfxGtm_Tom_PwmHl_initConfig(&pwmHlConfig);

        IfxGtm_Tom_ToutMapP ccx[2], coutx[2];
        ccx[0]   = &IfxGtm_TOM0_4_TOUT10_P00_1_OUT;
        coutx[0] = &IfxGtm_TOM0_5_TOUT11_P00_2_OUT;
        ccx[1]   = &IfxGtm_TOM0_6_TOUT14_P00_5_OUT;
        coutx[1] = &IfxGtm_TOM0_7_TOUT15_P00_6_OUT;
        pwmHlConfig.timer                 = &g_GtmTomPwmHl.drivers.timer;
        pwmHlConfig.tom                   = timerConfig.tom;
        pwmHlConfig.base.deadtime         = 2e-6;
        pwmHlConfig.base.minPulse         = 1e-6;
        pwmHlConfig.base.channelCount     = 2;
        pwmHlConfig.base.emergencyEnabled = FALSE;
        pwmHlConfig.base.outputMode       = IfxPort_OutputMode_pushPull;
        pwmHlConfig.base.outputDriver     = IfxPort_PadDriver_cmosAutomotiveSpeed1;
        pwmHlConfig.base.ccxActiveState   = Ifx_ActiveState_high;
        pwmHlConfig.base.coutxActiveState = Ifx_ActiveState_high;
        pwmHlConfig.ccx                   = ccx;
        pwmHlConfig.coutx                 = coutx;

        IfxGtm_Tom_PwmHl_init(&g_GtmTomPwmHl.drivers.pwm, &pwmHlConfig);

        IfxGtm_Tom_Timer_run(&g_GtmTomPwmHl.drivers.timer);
    }
}


/** \brief Demo init API
 *
 * This function is called from main during initialization phase
 */
static void GtmTomPwmHl_init(void)
{
    /* disable interrupts */
    boolean  interruptState = IfxCpu_disableInterrupts();

    /** - GTM clocks */
    Ifx_GTM *gtm = &MODULE_GTM;
    g_GtmTomPwmHl.info.gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);
    IfxGtm_enable(gtm);

    /* Get the global clock frequencies */
    g_GtmTomPwmHl.info.gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);

    IfxGtm_Cmu_setClkFrequency(gtm, IfxGtm_Cmu_Clk_0, g_GtmTomPwmHl.info.gtmGclkFreq);
    g_GtmTomPwmHl.info.gtmCmuClk0Freq = IfxGtm_Cmu_getClkFrequency(gtm, IfxGtm_Cmu_Clk_0, TRUE);
    g_GtmTomPwmHl.info.state          = GtmTomPwmHl_State_normal;

    /** - Initialise the GTM part */
    GtmTomPwmHl_initTimer();

    g_GtmTomPwmHl.info.timerValue =  IfxGtm_Tom_Timer_getPeriod(&g_GtmTomPwmHl.drivers.timer);
    g_GtmTomPwmHl.tOn[0] = 3000;
    g_GtmTomPwmHl.tOn[1] = 5000;

    /* enable interrupts again */
    IfxCpu_restoreInterrupts(interruptState);

    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
}
#endif
