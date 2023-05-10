/****************************************************************
 *
 * Module: Motor
 *
 * File Name: motor_module.h
 *
 * Description: Header File for AVR GPIO driver
 *
 * Author: Sarah
 ******************************************************************/
#ifndef MOTOR_MODULE_H_
#define MOTOR_MODULE_H_


#include"std_types.h"

/*************************************************************
 *             Definition
 *************************************************************/

#define MOTOR_PIN1_PIN2_PORT  PORTB_ID

#define MOTOR_PIN1            PIN0_ID
#define MOTOR_PIN2            PIN1_ID


#define MOTOR_IS_OFF          LOGIC_LOW
#define MOTOR_IS_ON           LOGIC_HIGH


/**************************************************************
 *                         Type declaration
 *************************************************************/
typedef enum {
	CW_DIRECTION,ACW_DIRECTION,STOP_MOTOR
}DC_Motor_state;

typedef struct {
	DC_Motor_state DC_State;
}DC_Motor_Config;

/************************************************************
 *                         Function prototypes
 ************************************************************/

/* Module initialization make pins output*/
void DcMotor_init(void);
/* Set Motor Speed, direction CW or ACW or stop Motor*/
void DcMotor_Rotate(const DC_Motor_Config *state,uint8 speed);

#endif /* MOTOR_MODULE_H_ */
