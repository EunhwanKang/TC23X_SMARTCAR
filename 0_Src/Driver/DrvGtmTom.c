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
#define ISR_PRIORITY_TIMER_10MS      79  /**< \brief Define the 1ms timer interrupt priority.  */
#define ISR_PROVIDER_TIMER_10MS      IfxSrc_Tos_cpu0 /**< \brief Define the 1ms timer interrupt provider.  */
#define INTERRUPT_TIMER_10MS         ISR_ASSIGN(ISR_PRIORITY_TIMER_10MS, ISR_PROVIDER_TIMER_10MS)           /**< \brief Define the 1ms timer interrupt priority.  */


#define ISR_PRIORITY_TIMER          83/**< \brief Define the 1ms timer interrupt priority.  */
#define ISR_PROVIDER_TIMER          IfxSrc_Tos_cpu0 /**< \brief Define the 1ms timer interrupt provider.  */
#define INTERRUPT_TIMER             ISR_ASSIGN(ISR_PRIORITY_TIMER, ISR_PROVIDER_TIMER)                   /**< \brief Define the 1ms timer interrupt priority.  */

#define PWM_FREQ	(1000000.0f/256.0f) /*100Hz*/

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


/*----------------------------------------------------------------*/
/*						Static Function Prototype				  */
/*----------------------------------------------------------------*/
static void GtmTomTimer_initTimer(void);
static void GtmTomTestPwm_init(void);

/*----------------------------------------------------------------*/
/*						Variables				  				  */
/*----------------------------------------------------------------*/
App_GtmTomTimer g_GtmTomTimer; /**< \brief Demo information */

uint32_t u32nuMyTestPwmDuty = 500u; /*Unit: 0.1%, 500 -> 50.0% duty*/
float32_t fMyTestPwmDuty = 0.5f;
/*----------------------------------------------------------------*/
/*						Functions				  				  */
/*----------------------------------------------------------------*/

/*---------------------Interrupt Define--------------------------*/
IFX_INTERRUPT(ISR_Timer_10ms, 0, ISR_PRIORITY_TIMER_10MS);


/*Interrupt Isr*/
void ISR_Timer_10ms(void)
{
    IfxCpu_enableInterrupts();

    IfxGtm_Tom_Timer_acknowledgeTimerIrq(&g_GtmTomTimer.drivers.timerOneMs);
    g_GtmTomTimer.isrCounter.slotOneMs++;
}

/*---------------------Test Code--------------------------*/
void GtmTomMyPwmTest(void)
{
    Ifx_TimerValue triggerPoint= (uint32_t)(fMyTestPwmDuty*PWM_FREQ);

	/*Disable Update*/
    IfxGtm_Tom_Timer_disableUpdate(&g_GtmTomTimer.drivers.timerOneMs);

    /*Set PWM duty*/
    IfxGtm_Tom_Timer_setTrigger(&g_GtmTomTimer.drivers.timerOneMs, triggerPoint);

	/*Apply Update*/
    IfxGtm_Tom_Timer_applyUpdate(&g_GtmTomTimer.drivers.timerOneMs);
}

/*---------------------Init Function--------------------------*/
void DrvGtmTomInit(void)
{
	GtmTomTestPwm_init();
}

static void GtmTomTimer_initTimer(void)
{
    {   /*Create Gtm Timer Output Module (TOM) configuration for timer*/
        IfxGtm_Tom_Timer_Config timerConfig;

        /*Init TOM timer configuration*/
        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);

        /*Setting timer configuration*/
        timerConfig.base.frequency       = 100;     /*Set PWM period : 100Hz*/
        timerConfig.base.isrPriority     = ISR_PRIORITY(INTERRUPT_TIMER_10MS);
        timerConfig.base.isrProvider     = ISR_PROVIDER(INTERRUPT_TIMER_10MS);
        timerConfig.base.minResolution   = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled = FALSE;
        timerConfig.tom                  = IfxGtm_Tom_1;    /*Set TOM1*/
        timerConfig.timerChannel         = IfxGtm_Tom_Ch_7; /*Set Channel 7*/
        timerConfig.clock                = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2; /*100MHz/256*/

        // Set output port, p33.10
        timerConfig.triggerOut                      = &IfxGtm_TOM1_7_TOUT32_P33_10_OUT;
        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 500000/256; /*5msec source: Fxclk2 100MHz/256*/
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE; /*Rising edge에서 interrupt*/

        /*Apply GTM Tom Reisgter*/
        IfxGtm_Tom_Timer_init(&g_GtmTomTimer.drivers.timerOneMs, &timerConfig);

        /*Start timer*/
        IfxGtm_Tom_Timer_run(&g_GtmTomTimer.drivers.timerOneMs);
    }
}

static void GtmTomTestPwm_init(void)
{
    /*disable interrupts*/
    boolean  interruptState = IfxCpu_disableInterrupts();

    /*obtain GTM clock frequency*/
    Ifx_GTM *gtm = &MODULE_GTM;
    g_GtmTomTimer.info.gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);

	/*Enable GTM*/
    IfxGtm_enable(gtm);
	
    /*setting the global clock to 100MHz*/
    IfxGtm_Cmu_setGclkFrequency(&MODULE_GTM, g_GtmTomTimer.info.gtmFreq);
    /*get Global clock frequency*/
    g_GtmTomTimer.info.gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);

    /*setting CMU0 frequency*/
    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, g_GtmTomTimer.info.gtmFreq);
	
    /*Gtm timer initialization*/
    GtmTomTimer_initTimer();

    /*enable interrupts again*/
    IfxCpu_restoreInterrupts(interruptState);

	/*enable Cmu clock*/
    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
}
