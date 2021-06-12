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
void DrvDio_SetPinLow(IfxPort_Pin param_PortPin)
{
	IfxPort_setPinLow(param_PortPin.port, param_PortPin.pinIndex);
}

void DrvDio_SetPinHigh(IfxPort_Pin param_PortPin)
{
	IfxPort_setPinHigh(param_PortPin.port, param_PortPin.pinIndex);
}

/*---------------------Init Function--------------------------*/
void DrvDioInit(void)
{
	/*P33_6	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P13_0.port, IfxPort_P13_0.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
	IfxPort_setPinLow(IfxPort_P13_0.port, IfxPort_P13_0.pinIndex);

    /*CS to touch*/
    IfxPort_setPinModeInput(TOUCH_USE_CHIPSELECT.pin.port, TOUCH_USE_CHIPSELECT.pin.pinIndex, IfxPort_Mode_inputPullUp);
    /*CS to tft*/
    IfxPort_setPinModeInput(TFT_USE_CHIPSELECT.pin.port, TFT_USE_CHIPSELECT.pin.pinIndex, IfxPort_Mode_inputPullUp);
    /*INT from touch*/
    IfxPort_setPinModeInput(TOUCH_USE_INT.port, TOUCH_USE_INT.pinIndex, IfxPort_Mode_inputPullUp);

    /* we enable the background light Application Kit */
    IfxPort_setPinModeOutput(BACKGROUND_LIGHT.pin.port, BACKGROUND_LIGHT.pin.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_alt1);

	/*P02_0	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P02_0.port, IfxPort_P02_0.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
	IfxPort_setPinLow(IfxPort_P02_0.port, IfxPort_P02_0.pinIndex);

	/*P02_2	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P02_2.port, IfxPort_P02_2.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
	IfxPort_setPinLow(IfxPort_P02_2.port, IfxPort_P02_2.pinIndex);

	/*P02_4	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P02_4.port, IfxPort_P02_4.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
	IfxPort_setPinLow(IfxPort_P02_4.port, IfxPort_P02_4.pinIndex);

	/*P02_6	Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P02_6.port, IfxPort_P02_6.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
	IfxPort_setPinLow(IfxPort_P02_6.port, IfxPort_P02_6.pinIndex);


}


#if 0
/*Get*/
uint8_t Drv_Get_nuDioP22_0(void)
{
    return (uint8_t)IfxPort_getPinState(IfxPort_P22_0.port, IfxPort_P22_0.pinIndex);
}
#endif


#if 0
/*P13_1 Digital Output*/
IfxPort_setPinModeOutput(IfxPort_P13_1.port, IfxPort_P13_1.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general); //Set Pin13_0 as Output
IfxPort_setPinLow(IfxPort_P13_1.port, IfxPort_P13_1.pinIndex);

/*P13_2 Digital Output*/
IfxPort_setPinModeOutput(IfxPort_P13_2.port, IfxPort_P13_2.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general); //Set Pin13_0 as Output
IfxPort_setPinLow(IfxPort_P13_2.port, IfxPort_P13_2.pinIndex);

/*P13_3 Digital Output*/
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
#endif
