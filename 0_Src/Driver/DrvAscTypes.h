#ifndef DRVASCTYPES_H
#define DRVASCTYPES_H

/*----------------------------------------------------------------*/
/*						Include Header File						  */
/*----------------------------------------------------------------*/
#include "Ifx_Types.h"
#include <Asclin/Asc/IfxAsclin_Asc.h>
#include "SysSe/Time/Ifx_DateTime.h"
#include "IfxLldVersion.h"
#include "_Impl/IfxGlobal_cfg.h"
#include "SysSe/Bsp/Bsp.h"
#include "SysSe/Comm/Ifx_Console.h"
#include "SysSe/Comm/Ifx_Shell.h"
#include "Assert.h"

/*----------------------------------------------------------------*/
/*						Define						  			  */
/*----------------------------------------------------------------*/
#define ASC_TX_BUFFER_SIZE 64
#define ASC_RX_BUFFER_SIZE 64

#define ISR_PRIORITY_ASC_0_RX 4
#define ISR_PRIORITY_ASC_0_TX 5
#define ISR_PRIORITY_ASC_0_EX 6

#define SW_REVISION_DATE    (0x20140630)            // Software date 0xyyyymmdd, with yyyy the year and mm the month and dd the day
#define SW_REVISION         (0x00000103)            // Software version and revision 0x0000vvrr, with vv the version number and rr the revision number

#define CFG_ASC_BAUDRATE       (115200.0)                   /**< \brief Define the Baudrate */
#define CFG_ASC_RX_BUFFER_SIZE (512)                        /**< \brief Define the Rx buffer size in byte. */
#define CFG_ASC_TX_BUFFER_SIZE (6 * 1024)                   /**< \brief Define the Tx buffer size in byte. */

#define ISR_ASSIGN(no, cpu)  ((no << 8) + cpu)
#define ISR_PRIORITY(no_cpu) (no_cpu >> 8)
#define ISR_PROVIDER(no_cpu) (no_cpu % 8)

#define ISR_PROVIDER_ASC_0    IfxSrc_Tos_cpu0         /**< \brief Define the ASC0 interrupt provider.  */

#define INTERRUPT_ASC_0_RX    ISR_ASSIGN(ISR_PRIORITY_ASC_0_RX, ISR_PROVIDER_ASC_0)                 /**< \brief Define the ASC0 receive interrupt priority.  */
#define INTERRUPT_ASC_0_TX    ISR_ASSIGN(ISR_PRIORITY_ASC_0_TX, ISR_PROVIDER_ASC_0)                 /**< \brief Define the ASC0 transmit interrupt priority.  */
#define INTERRUPT_ASC_0_EX    ISR_ASSIGN(ISR_PRIORITY_ASC_0_EX, ISR_PROVIDER_ASC_0)                 /**< \brief Define the ASC0 error interrupt priority.  */


/*----------------------------------------------------------------*/
/*						Typedefs						  		  */
/*----------------------------------------------------------------*/
typedef struct
{
    uint8 tx[CFG_ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
    uint8 rx[CFG_ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
} AppAscBuffer;

typedef struct
{
    AppAscBuffer ascBuffer;                     /**< \brief ASC interface buffer */
    struct
    {
        IfxAsclin_Asc asc0;                     /**< \brief ASC interface */
    }         drivers;

    uint8     txData[5];
    uint8     rxData[5];
    Ifx_SizeT count;
} App_AsclinAsc;

typedef struct
{
    struct
    {
        sint32 srcRev;                  /**< \brief Project source code revision number */
        sint32 srcRevDate;              /**< \brief Project source code revision Date */
        sint32 compilerVer;             /**< \brief Compiler version */
    }            info;
    AppAscBuffer ascBuffer;             /**< \brief ASC interface buffer */
    struct
    {
        IfxAsclin_Asc asc;              /**< \brief ASC interface */
    }         drivers;
    Ifx_Shell shell;                    /**< \brief Shell object */
    struct
    {
        IfxStdIf_DPipe asc;
    }stdIf;
} App_AsclinShellInterface;

#endif


