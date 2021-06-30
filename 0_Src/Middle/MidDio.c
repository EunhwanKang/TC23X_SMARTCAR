/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "MidDio.h"
#include "DrvDio.h"

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
void MidDio_SetFrontIn1(uint8_t param_SetIn1)
{
    if(param_SetIn1 == 0u)
    {
        DrvDio_SetPinLow(IfxPort_P33_5);
    }
    else
    {
        DrvDio_SetPinHigh(IfxPort_P33_5);
    }
}

void MidDio_SetFrontIn2(uint8_t param_SetIn2)
{
    if(param_SetIn2 == 0u)
    {
        DrvDio_SetPinLow(IfxPort_P33_3);
    }
    else
    {
        DrvDio_SetPinHigh(IfxPort_P33_3);
    }
}

void MidDio_SetFrontIn3(uint8_t param_SetIn3)
{
    if(param_SetIn3 == 0u)
    {
        DrvDio_SetPinLow(IfxPort_P33_1);
    }
    else
    {
        DrvDio_SetPinHigh(IfxPort_P33_1);
    }
}

void MidDio_SetFrontIn4(uint8_t param_SetIn4)
{
    if(param_SetIn4 == 0u)
    {
        DrvDio_SetPinLow(IfxPort_P33_4);
    }
    else
    {
        DrvDio_SetPinHigh(IfxPort_P33_4);
    }
}

void MidDio_SetRearIn1(uint8_t param_SetIn1)
{
    if(param_SetIn1 == 0u)
    {
        DrvDio_SetPinLow(IfxPort_P02_0);
    }
    else
    {
        DrvDio_SetPinHigh(IfxPort_P02_0);
    }
}

void MidDio_SetRearIn2(uint8_t param_SetIn2)
{
    if(param_SetIn2 == 0u)
    {
        DrvDio_SetPinLow(IfxPort_P02_2);
    }
    else
    {
        DrvDio_SetPinHigh(IfxPort_P02_2);
    }
}

void MidDio_SetRearIn3(uint8_t param_SetIn3)
{
    if(param_SetIn3 == 0u)
    {
        DrvDio_SetPinLow(IfxPort_P02_4);
    }
    else
    {
        DrvDio_SetPinHigh(IfxPort_P02_4);
    }
}

void MidDio_SetRearIn4(uint8_t param_SetIn4)
{
    if(param_SetIn4 == 0u)
    {
        DrvDio_SetPinLow(IfxPort_P02_3);
    }
    else
    {
        DrvDio_SetPinHigh(IfxPort_P02_3);
    }
}

