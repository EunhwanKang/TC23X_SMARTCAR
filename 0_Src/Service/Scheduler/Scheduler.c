/*----------------------------------------------------------------*/
/*						Include Header File						  */
/*----------------------------------------------------------------*/
#include "Scheduler.h"
#include "MidStm.h"
#include "Common.h"
#include "Comp_HalInterface.h"

#include "tft_app.h"
#include "Configuration.h"
#include "Perf_Meas.h"
/*----------------------------------------------------------------*/
/*						Define						  			  */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*						Typedefs						  		  */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*						Static Function Prototype				  */
/*----------------------------------------------------------------*/
static void AppNoTimeTask(void);
static void AppTask1ms(void);
static void AppTask5ms(void);
static void AppTask10ms(void);
static void AppTask50ms(void);
static void AppTask100ms(void);
static void AppTask200ms(void);
static void AppTask500ms(void);
static void AppTask1s(void);

static void TaskSchedulerCallbackFnc(void);

/*----------------------------------------------------------------*/
/*						Variables				  				  */
/*----------------------------------------------------------------*/
uint32_t ulScheduler1msCounter = 0u;
uint8_t	ucScheduler1msFlag = 0u;


/*----------------------------------------------------------------*/
/*						Functions				  				  */
/*----------------------------------------------------------------*/

/*---------------------Application Task Function--------------------------*/
/*NoTime Taksing*/
static void AppNoTimeTask(void)
{
//	perf_meas_idle();
}

/*AppTask 1ms*/
static void AppTask1ms(void)
{

}


/*AppTask 5ms*/
static void AppTask5ms(void)
{

}


/*AppTask 10ms*/
static void AppTask10ms(void)
{

}

/*AppTask 50ms*/
static void AppTask50ms(void)
{

}

/*AppTask 100ms*/
static void AppTask100ms(void)
{
	//controlmenu.cpuseconds += controlmenu.cpusecondsdelta;
}

/*AppTask 200ms*/
static void AppTask200ms(void)
{
//	IfxSrc_setRequest(&TFT_UPDATE_IRQ);    /*trigger the tft lib*/
}

/*AppTask 500ms*/
static void AppTask500ms(void)
{

}

/*AppTask 1s*/
static void AppTask1s(void)
{
	static uint32_t ulAppTask1sCounter = 0u;
	//static uint8_t u8nuLedStateFlag = 0u;

	ulAppTask1sCounter++;

	#if 0 
	if(u8nuLedStateFlag == 0u)
	{
		Hal_Set_nuBoardLed1(1);
		u8nuLedStateFlag = 1u;
	}
	else
	{
		Hal_Set_nuBoardLed1(0);
		u8nuLedStateFlag = 0u;
	}
	#endif
}


/*---------------------CallbackFunc--------------------------*/
static void TaskSchedulerCallbackFnc(void)
{
	ulScheduler1msCounter++;
	ucScheduler1msFlag = ON;
}

/*---------------------Register CallbackFunc--------------------------*/
void Scheduler_Init(void)
{
	MidRegTimerCallbackFnc(TaskSchedulerCallbackFnc);
}

/*---------------------Scheduler--------------------------*/
void Scheduler(void)
{
	AppNoTimeTask();

	if(ucScheduler1msFlag == ON)
	{
		ucScheduler1msFlag = OFF;
		AppTask1ms();

		 if((ulScheduler1msCounter % 5u) == 0u)
		 {
			AppTask5ms();
		 }

		 if((ulScheduler1msCounter % 10u) == 0u)
		 {
			AppTask10ms();
		 }

		 if((ulScheduler1msCounter % 50u) == 0u)
		 {
			AppTask50ms();
		 }

		 if((ulScheduler1msCounter % 100u) == 0u)
		 {
			AppTask100ms();
		 }

		 if((ulScheduler1msCounter % 200u) == 0u)
		 {
			AppTask200ms();
		 }

		 if((ulScheduler1msCounter % 500u) == 0u)
		 {
			AppTask500ms();
		 }

		 if((ulScheduler1msCounter % 1000u) == 0u)
		 {
			AppTask1s();
			ulScheduler1msCounter = 0u;
		 }
	}
}
