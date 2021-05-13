/*Include Header File*/
#include "Adapt_Dio.h"
#include "DrvDio.h"
/*Define*/

/*Static Function Prototype*/

/*Variables*/


/*Get*/


/*Functions*/
/*Set*/
void Adapt_Set_nuDioP13_0(uint8_t param_nuDioP13_0)
{
    Drv_Set_nuDioP13_0(param_nuDioP13_0);
}

void Adapt_Set_nuDioP13_1(uint8_t param_nuDioP13_1)
{
    Drv_Set_nuDioP13_1(param_nuDioP13_1);
}

void Adapt_Set_nuDioP13_2(uint8_t param_nuDioP13_2)
{
    Drv_Set_nuDioP13_2(param_nuDioP13_2);
}

void Adapt_Set_nuDioP13_3(uint8_t param_nuDioP13_3)
{
    Drv_Set_nuDioP13_3(param_nuDioP13_3);
}


/*Get*/
uint8_t Adapt_Get_nuDioP22_0(void)
{
    uint8_t u8nuDioP22_0 = 0u;
    u8nuDioP22_0 = Drv_Get_nuDioP22_0();
    return u8nuDioP22_0;
}

uint8_t Adapt_Get_nuDioP22_1(void)
{
    uint8_t u8nuDioP22_1 = 0u;
    u8nuDioP22_1 = Drv_Get_nuDioP22_1();
    return u8nuDioP22_1;
}
