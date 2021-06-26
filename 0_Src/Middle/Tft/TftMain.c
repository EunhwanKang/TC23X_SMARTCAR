/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "TftMain.h"
#include <background_light.h>
#include "Configuration.h"
#include <Tft/conio_tft.h>
#include "tft_app.h"
#include "Perf_Meas.h"
#include "display_io.h"
#include "IfxScuCcu.h"
#include "IfxStm.h"
#include "Main.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Init Function--------------------------*/
void Tft_Init(void)
{
    /* Initialise the application state */
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

    /*Init TFT-display*/
    tft_appl_init(1);

    /*Init the backroundlight*/
    background_light_init();
    graph_drawInfineonLogo();

    /*Init the performance measurement*/
    perf_meas_init();
    display_io_init();

}


