#ifndef MAIN_H
#define MAIN_H

/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "Configuration.h"
#include "Cpu/Std/Ifx_Types.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/
typedef struct
{
    float32 sysFreq;                /**< \brief Actual SPB frequency */
    float32 cpuFreq;                /**< \brief Actual CPU frequency */
    float32 pllFreq;                /**< \brief Actual PLL frequency */
    float32 stmFreq;                /**< \brief Actual STM frequency */
} AppInfo;

/** \brief Application information */
typedef struct
{
    AppInfo info;                               /**< \brief Info object */
    uint32 TickCount_1ms;                       /**< \brief TickCount 1ms */
} App_Cpu;

/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/
IFX_EXTERN App_Cpu g_AppCpu0;


/*----------------------------------------------------------------*/
/*                        Global Function Prototype                  */
/*----------------------------------------------------------------*/


#endif
