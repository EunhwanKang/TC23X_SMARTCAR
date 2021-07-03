/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "DrvGtm.h"
#include "SysSe/Bsp/Bsp.h"
#include "Gtm/Tom/Timer/IfxGtm_Tom_Timer.h"
#include "Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/

#define TOM_BASE_FREQ    (100000000.0f/256.0f)
//#define TOM_BASE_FREQ    (100000000.0f)
#define PWM_HZ           (100.0f)
#define PWM_PERIOD_CNT   TOM_BASE_FREQ/PWM_HZ


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
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
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/
static void GtmTom1Init(void);
static void GtmTim0Init(void);


/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/
App_GtmTomTimer g_GtmTomTimer; /**< \brief Demo information */

uint32_t u32nuMyTestPwmDuty = 500u; /*Unit: 0.1%, 500 -> 50.0% duty*/
float32_t fMyTestPwmDuty = 0.5f;
uint32_t ulPulseCnt = 0u;


/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Interrupt Define--------------------------*/
IFX_INTERRUPT(TIM0_IntHandler, 0, 200);

/*---------------------Interrupt Service Routine--------------------------*/
void TIM0_IntHandler(void)
{
    IfxCpu_enableInterrupts();
    ulPulseCnt++;
}

/*---------------------Test Code--------------------------*/
void DrvGtmPwmTest(float32_t param_Ch4Duty, float32_t param_Ch5Duty, float32_t param_Ch6Duty, float32_t param_Ch7Duty)
{
    float32_t fPeriodCnt = PWM_PERIOD_CNT;
    uint32_t ulPeriodCnt = (uint32_t)fPeriodCnt;
    
    GTM_TOM1_TGC0_GLB_CTRL.U = 0xAA000000u; 
    
    GTM_TOM1_CH4_SR0.B.SR0 = ulPeriodCnt;
    GTM_TOM1_CH4_SR1.B.SR1 = (uint32_t)(fPeriodCnt*param_Ch4Duty);

    GTM_TOM1_CH5_SR0.B.SR0 = ulPeriodCnt;
    GTM_TOM1_CH5_SR1.B.SR1 = (uint32_t)(fPeriodCnt*param_Ch5Duty);

    GTM_TOM1_CH6_SR0.B.SR0 = ulPeriodCnt;
    GTM_TOM1_CH6_SR1.B.SR1 = (uint32_t)(fPeriodCnt*param_Ch6Duty);

    GTM_TOM1_CH7_SR0.B.SR0 = ulPeriodCnt;
    GTM_TOM1_CH7_SR1.B.SR1 = (uint32_t)(fPeriodCnt*param_Ch7Duty);
    
    GTM_TOM1_TGC0_GLB_CTRL.U = 0xAA000000u;
}

/*---------------------Init Function--------------------------*/
void DrvGtmInit(void)
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
    
    GtmTom1Init();
    GtmTim0Init();

    /*enable interrupts again*/
    IfxCpu_restoreInterrupts(interruptState);

    /*enable Cmu clock*/
    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
}

static void GtmTom1Init(void)
{
    IfxGtm_PinMap_setTomTout(&IfxGtm_TOM1_4_TOUT30_P33_8_OUT, IfxPort_OutputMode_pushPull, IfxPort_PadDriver_cmosAutomotiveSpeed4); /*Rear Left*/
    IfxGtm_PinMap_setTomTout(&IfxGtm_TOM1_5_TOUT28_P33_6_OUT, IfxPort_OutputMode_pushPull, IfxPort_PadDriver_cmosAutomotiveSpeed4); /*Rear Right*/
    IfxGtm_PinMap_setTomTout(&IfxGtm_TOM1_6_TOUT5_P02_5_OUT, IfxPort_OutputMode_pushPull, IfxPort_PadDriver_cmosAutomotiveSpeed4);  /*Front Left*/
    IfxGtm_PinMap_setTomTout(&IfxGtm_TOM1_7_TOUT6_P02_6_OUT, IfxPort_OutputMode_pushPull, IfxPort_PadDriver_cmosAutomotiveSpeed4);  /*Front Right*/

    GTM_TOM1_CH4_CTRL.B.RST_CCU0 = 0u;
    GTM_TOM1_CH4_CTRL.B.TRIGOUT = 1u;
    GTM_TOM1_CH4_CTRL.B.SL = 1u;

    GTM_TOM1_CH5_CTRL.B.RST_CCU0 = 1u;
    GTM_TOM1_CH5_CTRL.B.TRIGOUT = 0u;
    GTM_TOM1_CH5_CTRL.B.SL = 1u;

    GTM_TOM1_CH6_CTRL.B.RST_CCU0 = 1u;
    GTM_TOM1_CH6_CTRL.B.TRIGOUT = 0u;
    GTM_TOM1_CH6_CTRL.B.SL = 1u;

    GTM_TOM1_CH7_CTRL.B.RST_CCU0 = 1u;
    GTM_TOM1_CH7_CTRL.B.TRIGOUT = 0u;
    GTM_TOM1_CH7_CTRL.B.SL = 1u;

    GTM_TOM1_TGC0_GLB_CTRL.U = 0xAA000000u; 
    GTM_TOM1_TGC0_ENDIS_CTRL.U = 0xAA00u;    
    GTM_TOM1_TGC0_OUTEN_CTRL.U = 0xAA00u;  

    GTM_TOM1_CH4_CTRL.B.CLK_SRC_SR = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2;
    GTM_TOM1_CH5_CTRL.B.CLK_SRC_SR = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2;    
    GTM_TOM1_CH6_CTRL.B.CLK_SRC_SR = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2;
    GTM_TOM1_CH7_CTRL.B.CLK_SRC_SR = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2;

    GTM_TOM1_TGC0_GLB_CTRL.B.HOST_TRIG = 1u;  
}

static void GtmTim0Init(void)
{
    float32_t temp = 0.0f;
    
    IfxGtm_PinMap_setTimTin(&IfxGtm_TIM0_0_TIN32_P33_10_IN, IfxPort_InputMode_pullDown);

    GTM_TIM0_CH0_CTRL.B.TIM_MODE = 2u; 
    GTM_TIM0_CH0_CTRL.B.ISL = 0u;
    GTM_TIM0_CH0_CTRL.B.DSL = 1u;

    GTM_TIM0_CH0_CTRL.B.FLT_EN = 0;
    //temp = 2.0f * TOM_BASE_FREQ;

    //GTM_TIM0_CH0_FLT_RE.B.FLT_RE = (uint32_t)temp;
    //GTM_TIM0_CH0_CTRL.B.FLT_MODE_RE = (uint8_t)IfxGtm_Tim_FilterMode_immediateEdgePropagation;

    SRC_GTMTIM00.B.SRE = 1;
    SRC_GTMTIM00.B.SRPN = 200u;
    GTM_TIM0_CH0_CNT.U = 0;
    GTM_TIM0_CH0_IRQ_EN.U = 0x1;
    GTM_TIM0_CH0_CTRL.B.TIM_EN = 1;
    GTM_IRQ_MODE.B.IRQ_MODE = 2;
    GTM_TIM0_CH0_IRQ_MODE.B.IRQ_MODE = 2;    
}
