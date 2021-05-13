/*----------------------------------------------------------------*/
/*						Include Header File						  */
/*----------------------------------------------------------------*/
#include "Main.h"
#include "DrvSys.h"
#include "Scheduler.h"
#include "DrvAsc.h"

/*----------------------------------------------------------------*/
/*						Define						  			  */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*						Typedefs						  		  */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*						Static Function Prototype				  */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*						Variables				  				  */
/*----------------------------------------------------------------*/
App_Cpu g_AppCpu0;
uint32_t u32nuMemberNo = 4u;
uint32_t u32nuEunhwanAge = 34u;
uint32_t u32nuEunhwanHeight = 168u;
uint32_t u32nuEunhwanWeight = 64u;


/*----------------------------------------------------------------*/
/*						Functions				  				  */
/*----------------------------------------------------------------*/

/*---------------------Main Function--------------------------*/
int main(void)
{
	/*System Initialization*/
	DrvSys();

	/*Register Callback Function*/
	Scheduler_Init();

    /*Enable the global interrupts of this CPU*/
    IfxCpu_enableInterrupts();

	#if 0 
	/*Tlf Initialization*/
	DrvTlfInit();
	#endif
	
	/*For Asc Test*/
	AscPrintf("Hello! GreenFrog!\r\n");
	AscPrintf("GreenFrog has %d Members!\r\n", u32nuMemberNo);
	AscPrintf("Eunhwan Age : %d, Height: %d Weight: %d \r\n", u32nuEunhwanAge, u32nuEunhwanHeight, u32nuEunhwanWeight);

    while(1u)
    {
    	Scheduler();
    }

    return 0;
}
