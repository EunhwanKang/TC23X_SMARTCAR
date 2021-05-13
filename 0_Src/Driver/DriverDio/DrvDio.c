/*----------------------------------------------------------------*/
/*						Include Header File						  */
/*----------------------------------------------------------------*/
#include "DrvDio.h"
#include "IfxPort.h"
#include "IfxPort_PinMap.h"
#include "Configuration.h"

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


/*----------------------------------------------------------------*/
/*						Functions				  				  */
/*----------------------------------------------------------------*/

/*---------------------Driver API--------------------------*/
/*Set*/
void Drv_Set_nuDioP13_0(uint8_t param_nuDioP13_0)
{
	if(param_nuDioP13_0 == 0u)
	{
		IfxPort_setPinLow(IfxPort_P13_0.port, IfxPort_P13_0.pinIndex);
	}
	else
	{
		IfxPort_setPinHigh(IfxPort_P13_0.port, IfxPort_P13_0.pinIndex);
	}
}

void Drv_Set_nuDioP13_1(uint8_t param_nuDioP13_1)
{
	if(param_nuDioP13_1 == 0u)
	{
		IfxPort_setPinLow(IfxPort_P13_1.port, IfxPort_P13_1.pinIndex);
	}
	else
	{
		IfxPort_setPinHigh(IfxPort_P13_1.port, IfxPort_P13_1.pinIndex);
	}
}

void Drv_Set_nuDioP13_2(uint8_t param_nuDioP13_2)
{
	if(param_nuDioP13_2 == 0u)
	{
		IfxPort_setPinLow(IfxPort_P13_2.port, IfxPort_P13_2.pinIndex);
	}
	else
	{
		IfxPort_setPinHigh(IfxPort_P13_2.port, IfxPort_P13_2.pinIndex);
	}
}

void Drv_Set_nuDioP13_3(uint8_t param_nuDioP13_3)
{
	if(param_nuDioP13_3 == 0u)
	{
		IfxPort_setPinLow(IfxPort_P13_3.port, IfxPort_P13_3.pinIndex);
	}
	else
	{
		IfxPort_setPinHigh(IfxPort_P13_3.port, IfxPort_P13_3.pinIndex);
	}
}

/*Get*/
uint8_t Drv_Get_nuDioP22_0(void)
{
    return (uint8_t)IfxPort_getPinState(IfxPort_P22_0.port, IfxPort_P22_0.pinIndex);
}

uint8_t Drv_Get_nuDioP22_1(void)
{
    return (uint8_t)IfxPort_getPinState(IfxPort_P22_1.port, IfxPort_P22_1.pinIndex);
}

/*---------------------Init Function--------------------------*/
void DrvDioInit(void)
{
	/*P13_0	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P13_0.port, IfxPort_P13_0.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general); //Set Pin13_0 as Output
	IfxPort_setPinLow(IfxPort_P13_0.port, IfxPort_P13_0.pinIndex);

	/*P13_1	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P13_1.port, IfxPort_P13_1.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general); //Set Pin13_0 as Output
	IfxPort_setPinLow(IfxPort_P13_1.port, IfxPort_P13_1.pinIndex);

  	/*P13_2	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P13_2.port, IfxPort_P13_2.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general); //Set Pin13_0 as Output
	IfxPort_setPinLow(IfxPort_P13_2.port, IfxPort_P13_2.pinIndex);

	/*P13_3	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P13_3.port, IfxPort_P13_3.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general); //Set Pin13_0 as Output
	IfxPort_setPinLow(IfxPort_P13_3.port, IfxPort_P13_3.pinIndex);

    /*CS to touch*/
    IfxPort_setPinModeInput(TOUCH_USE_CHIPSELECT.pin.port, TOUCH_USE_CHIPSELECT.pin.pinIndex, IfxPort_Mode_inputPullUp);
    /*CS to tft*/
    IfxPort_setPinModeInput(TFT_USE_CHIPSELECT.pin.port, TFT_USE_CHIPSELECT.pin.pinIndex, IfxPort_Mode_inputPullUp);
    /*INT from touch*/
    IfxPort_setPinModeInput(TOUCH_USE_INT.port, TOUCH_USE_INT.pinIndex, IfxPort_Mode_inputPullUp);
    /*We enable the background light Application Kit*/
    IfxPort_setPinModeOutput(BACKGROUND_LIGHT.pin.port, BACKGROUND_LIGHT.pin.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_alt1);
}

