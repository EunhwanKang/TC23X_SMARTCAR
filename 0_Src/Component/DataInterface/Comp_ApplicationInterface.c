/*Include Header File*/
#include "Comp_ApplicationInterface.h"

/*Define*/


/*Variable*/
static uint8_t gu8nuTemp = 0u;

/*Functions*/
void AppIf_Write_nuTemp(uint8_t param_nuTemp)
{
	gu8nuTemp = param_nuTemp;
}

uint8_t AppIf_Read_nuTemp(void)
{
	return gu8nuTemp;
}
