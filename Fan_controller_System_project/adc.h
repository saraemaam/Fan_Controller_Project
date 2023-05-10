/******************************************************************
 * Module      : ADC
 * File name   : adc.h
 * Description : header file for the ATmega32 ADC driver
 * Author      : Sarah
 ****************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/******************************************************************
 *                           Types declaration
 ******************************************************************/
typedef enum{
	ADC_AREF,ADC_AVCC,ADC_INTERNAL_2_56V=3
}ADC_ReferenceVolatge;

typedef enum {
	ADC_FCPU_2,ADC_FCPU_2_OPTION,ADC_FCPU_4,ADC_FCPU_8,ADC_FCPU_16
	,ADC_FCPU_32 ,ADC_FCPU_64,ADC_FCPU_128
}ADC_Prescaler;


typedef struct{
 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_MAXIMUM_VALUE    1023 /*depends on the ADC resolution if 10 bit 1023*/
#define ADC_REF_VOLT_VALUE   2.56


/* ADC Channels */

#define ADC_u8CH_0      0
#define ADC_u8CH_1      1
#define ADC_u8CH_2      2
#define ADC_u8CH_3      3
#define ADC_u8CH_4      4
#define ADC_u8CH_5      5
#define ADC_u8CH_6      6
#define ADC_u8CH_7      7


/* Left and Right adjustment of ADLAR*/
#define ADC_uint8LEFT_ADJUST    0
#define ADC_uint8RIGHT_ADJUST	 1

/* ADC Trigger Source*/
#define ADC_uint8TRIGGER_SOURCE_DISABLED           1
#define ADC_uint8TRIGGER_SOURCE_FREE_RUN           2
#define ADC_uint8TRIGGER_SOURCE_ANALOG_COMP        3
#define ADC_uint8TRIGGER_SOURCE_EXT_INT_REQ0       4
#define ADC_uint8TRIGGER_SOURCE_TIMER_COMP_MATCH   5
#define ADC_uint8TRIGGER_SOURCE_TIMER_0_OVF        6
#define ADC_uint8TRIGGER_SOURCE_TIMER_COMP_MATCH_B 7
#define ADC_uint8TRIGGER_SOURCE_TIMER_1_OVF        8
#define ADC_uint8TRIGGER_SOURCE_TIMER_1_CAPT       9

/* ADC based on Interrupt or polling technique*/
#define ADC_uint8INTERRUPT_BASED     1
#define ADC_uint8POOLLING_BASED      2


#define ADC_uint8RESULT_ADJUST         ADC_uint8RIGHT_ADJUST

#define ADC_uint8AUTO_TRIGGER          ADC_uint8TRIGGER_SOURCE_DISABLED

#define ADC_uint8IMPLEMENTATION_BASED	ADC_uint8POOLLING_BASED


/****************************************************************
 *                    ADC Registers new type
 ***************************************************************/

typedef union {

	uint8 Byte;
	struct {

		/* Bit by Bit or for making it easier every group of bits related to one functionality*/
		/*uint8 MUX0:1;
		  uint8 MUX1:1;
		  uint8 MUX2:1;
		  uint8 MUX3:1;
		  uint8 MUX4:1;
		 */
		uint8 MUX:5;
		uint8 ADLAR:1;
		/*uint8 REFS0:1;
		  uint8 REFS1:1;*/
		uint8 REFS:2;
	}Bits;

}Adc_ADMUX_Type;

typedef union{
	struct{

		/*uint8 ADPS0:1;
		uint8 ADPS1:1;
		uint8 ADPS2:1;*/
		uint8 ADPS: 3;
		uint8 ADIE: 1;
		uint8 ADIF: 1;
		uint8 ADATE:1;
		uint8 ADSC: 1;
		uint8 ADEN: 1;
	}Bits;
	uint8 Byte;
}Adc_ADCSRA_Type;


typedef union{
	struct{

		uint8 PSR10:1;
		uint8 PSR2:1;
		uint8 PUD:1;
		uint8 ACME: 1;
		uint8 RESERVED:1;
		//uint8 ADTS0:1;
		//uint8 ADTS1: 1;
		uint8 ADTS: 3;
	}Bits;
	uint8 Byte;
}Adc_SFIOR_Type;



typedef union{
	struct{

		uint8 ADC0 :1;
		uint8 ADC1 :1;
		uint8 ADC2 :1;
		uint8 ADC3: 1;
		uint8 ADC4: 1;
		uint8 ADC5 :1;
		uint8 ADC6: 1;
		uint8 ADC7: 1;
	}Bits;
	uint8 Byte;
}Adc_ADCL_Type;

typedef union{
	struct{

		uint8 ADC0 :1;
		uint8 ADC1 :1;
		uint8 ADC2 :1;
		uint8 ADC3: 1;
		uint8 ADC4: 1;
		uint8 ADC5 :1;
		uint8 ADC6: 1;
		uint8 ADC7: 1;
	}Bits;
	uint8 Byte;
}Adc_ADCH_Type;

#define ADMUX    (*((volatile Adc_ADMUX_Type*)0x27))
#define ADCSRA   (*((volatile Adc_ADCSRA_Type*)0x26))
#define ADCH     (*((volatile Adc_ADCH_Type*)0x25))
#define ADCL     (*((volatile Adc_ADCL_Type*)0x24))
#define SFIOR    (*((volatile Adc_SFIOR_Type*)0x50))



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType* Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
#if ADC_u8RESULT_ADJUST == ADC_u8RIGHT_ADJUST
uint16 ADC_readChannel(uint8 Chnl_Id);

#elif ADC_u8RESULT_ADJUST == ADC_u8LEFT_ADJUST
uint8 ADC_readChannel(uint8 Chnl_Id);

#endif



#endif /* ADC_H_ */
