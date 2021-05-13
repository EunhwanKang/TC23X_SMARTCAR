/*Include Header File*/
#include "Comp_ComplexInterface.h"
#include <string.h>

/*Define*/

#if 0
/*Variable*/
static TASKFLAG gstnuTaskFlag = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

/*Functions*/
void ComIf_Write_nuTaskFlag(TASKFLAG param_nuTaskFlag)
{
	gstnuTaskFlag = param_nuTaskFlag;
}

TASKFLAG ComIf_Read_nuTaskFlag(void)
{
	return gstnuTaskFlag;
}
#endif