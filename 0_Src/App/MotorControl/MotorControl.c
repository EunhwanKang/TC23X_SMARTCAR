/*----------------------------------------------------------------*/
/*						Include Header File						  */
/*----------------------------------------------------------------*/
#include "MotorControl.h"
#include "MidDio.h"


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
void Unit_MotorFrontDirectionCtl(MOTOR_CMD_TYPE param_DirectionType)
{
    switch(param_DirectionType)
    {
        case MOTOR_STOP: /*Stop*/
        {
        	MidDio_SetFrontIn1(0u);
        	MidDio_SetFrontIn2(0u);
        	MidDio_SetFrontIn3(0u);
        	MidDio_SetFrontIn4(0u);	
            break;
        }
        case MOTOR_FWD: /*Forward*/
        {
        	MidDio_SetFrontIn1(1u);
        	MidDio_SetFrontIn2(0u);
        	MidDio_SetFrontIn3(1u);
        	MidDio_SetFrontIn4(0u);			
            break;           
        }
        case MOTOR_TURN_RIGHT: /*TurnRight*/
        {
        	MidDio_SetFrontIn1(1u);
        	MidDio_SetFrontIn2(0u);
        	MidDio_SetFrontIn3(0u);
        	MidDio_SetFrontIn4(1u);	
            break;            
        }
        case MOTOR_TURN_LEFT: /*TurnLeft*/
        {
        	MidDio_SetFrontIn1(0u);
        	MidDio_SetFrontIn2(1u);
        	MidDio_SetFrontIn3(1u);
        	MidDio_SetFrontIn4(0u);	        
            break;            
        }
        case MOTOR_REVERSE: /*Reverse*/
        {
        	MidDio_SetFrontIn1(0u);
        	MidDio_SetFrontIn2(1u);
        	MidDio_SetFrontIn3(0u);
        	MidDio_SetFrontIn4(1u);	        
            break;            
        }
        default:
        break;
    }
}


void Unit_MotorRearDirectionCtl(MOTOR_CMD_TYPE param_DirectionType)
{
    switch(param_DirectionType)
    {
        case MOTOR_STOP: /*Stop*/
        {
        	MidDio_SetRearIn1(0u);
        	MidDio_SetRearIn2(0u);
        	MidDio_SetRearIn3(0u);
        	MidDio_SetRearIn4(0u);	
            break;
        }
        case MOTOR_FWD: /*Forward*/
        {
        	MidDio_SetRearIn1(1u);
        	MidDio_SetRearIn2(0u);
        	MidDio_SetRearIn3(1u);
        	MidDio_SetRearIn4(0u);	
            break;
        }        
        case MOTOR_TURN_RIGHT: /*TurnRight*/
        {
        	MidDio_SetRearIn1(1u);
        	MidDio_SetRearIn2(0u);
        	MidDio_SetRearIn3(0u);
        	MidDio_SetRearIn4(1u);	
            break;
        }
        case MOTOR_TURN_LEFT: /*TurnLeft*/
        {
        	MidDio_SetRearIn1(0u);
        	MidDio_SetRearIn2(1u);
        	MidDio_SetRearIn3(1u);
        	MidDio_SetRearIn4(0u);	 
            break;
        }
        case MOTOR_REVERSE: /*Reverse*/
        {
        	MidDio_SetRearIn1(0u);
        	MidDio_SetRearIn2(1u);
        	MidDio_SetRearIn3(0u);
        	MidDio_SetRearIn4(1u);	
            break;
        }
        default:
        break;
    }
}

#if 0
void Unit_MotorPwmCtl(void)
{
    static uint8_t u8nuMotorPwmStartFlag = 0u;
    static float32_t f32nuPwm0A0Duty = 70.0f;
    static float32_t f32nuPwm0B0Duty = 70.0f;
    static float32_t f32nuPwm0A2Duty = 70.0f;
    static float32_t f32nuPwm0B2Duty = 70.0f;

    if(u8nuMotorPwmStartFlag == 0u)
    {
        Hal_Set_nuPwm0Run(5u);
    }

    #if 1
    Hal_Set_nuPwm0A0Duty(f32nuPwm0A0Duty);
    Hal_Set_nuPwm0B0Duty(f32nuPwm0B0Duty);
    Hal_Set_nuPwm0A2Duty(f32nuPwm0A2Duty);
    Hal_Set_nuPwm0B2Duty(f32nuPwm0B2Duty);

    Hal_Set_nuPwm0LoadOk(5u);
    #endif
}
#endif
