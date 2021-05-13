#ifndef _COMP_HALINTERFACE_H_
#define _COMP_HALINTERFACE_H_

/*Include Header File*/
#include "Ifx_Types.h"
//#include "Adapt_Dio.h"
/*Define*/


/*Dio*/
#define Hal_Set_nuBoardLed1(x)		Adapt_Set_nuDioP13_0(x)
#define Hal_Set_nuBoardLed2(x)		Adapt_Set_nuDioP13_1(x)
#define Hal_Set_nuBoardLed3(x)		Adapt_Set_nuDioP13_2(x)
#define Hal_Set_nuBoardLed4(x)		Adapt_Set_nuDioP13_3(x)

#endif


