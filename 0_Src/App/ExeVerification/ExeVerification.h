#ifndef EXEVERIFICATION_H
#define EXEVERIFICATION_H

/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "Ifx_Types.h"
#include "IfxStm.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/
#define STM_CLOCK_HZ    100000.0f /*100MHz*/ 

#define CYCLE_CHECK(x)   CycleVerfication(x)

/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/
typedef enum
{
    TASK_1MS = 0u,
    TASK_5MS,
    TASK_10MS,
    TASK_50MS,    
    TASK_100MS,
    TASK_200MS,
    TASK_500MS,
    TASK_1S,
    TASK_NUMBER    
}E_TASK;
    
typedef struct
{
    uint8_t ucCycleFlag[TASK_NUMBER];
    uint32_t ulCycleStartCnt[TASK_NUMBER];
    uint32_t ulCycleEndCnt[TASK_NUMBER]; 
    float32_t fCycleTaskMs[TASK_NUMBER];
}CycleInfo;

/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/
extern CycleInfo stCycleInfo;

/*----------------------------------------------------------------*/
/*                        Global Function Prototype                  */
/*----------------------------------------------------------------*/
IFX_INLINE void CycleVerfication(E_TASK param_Task)
{
    uint32_t ulTemp = 0u;

    if(stCycleInfo.ucCycleFlag[param_Task] == 0u)
    {
        /*Change Cycle Flag*/
        stCycleInfo.ucCycleFlag[param_Task] = 1u;
        
        /*Obtain STM Start Clock*/
        stCycleInfo.ulCycleStartCnt[param_Task]    = MODULE_STM0.TIM0.U;
    }
    else
    {
        /*Change Cycle Flag*/
        stCycleInfo.ucCycleFlag[param_Task] = 0u;    
        
        /*Obtain STM End Clock*/
        stCycleInfo.ulCycleEndCnt[param_Task]    = MODULE_STM0.TIM0.U;

        /*Calculation of Task Execution*/
        ulTemp = stCycleInfo.ulCycleEndCnt[param_Task] - stCycleInfo.ulCycleStartCnt[param_Task];
        stCycleInfo.fCycleTaskMs[param_Task] = (float32_t)ulTemp/STM_CLOCK_HZ;
    }
}
#endif
