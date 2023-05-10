/******************************************************************
 * Module      : ADC
 * File name   : adc.c
 * Description : Analog to digital converter configurable driver
 * Author      : Sarah
 ****************************************************************/

#include"adc.h"
#include"common_macros.h"

#include <avr/interrupt.h> /* For ADC ISR */

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	g_adcResult = ADC;

}


/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType* Config_Ptr)
{

	/* Set the required reference voltage*/
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<6);

#if ADC_u8RESULT_ADJUST==ADC_u8RIGHT_ADJUST
	/* Select Right adjustment */
	CLEAR_BIT(ADMUX,5);
	/*ADMUX.Bits.ADLAR=0;*/

#elif ADC_u8RESULT_ADJUST == ADC_u8LEFT_ADJUST
	/* Select Left adjustment */
	SET_BIT(ADMUX,5);
	/*ADMUX.Bits.ADLAR=1;*/

#endif

#if ADC_u8AUTO_TRIGGER == ADC_u8TRIGGER_SOURCE_DISABLED
	/* Disable AUTO Trigger */

	CLEAR_BIT(ADCSRA,ADATE);
	/*ADCSRA.Bits.ADATE=0;*/

#elif ADC_u8AUTO_TRIGGER== ADC_u8TRIGGER_SOURCE_FREE_RUN

	/* Enable AUTO Trigger */
	SET_BIT(ADCSRA , 5);

	/*ADCSRA.Bits.ADATE=1;*/

	/* Select Free Run as AUTO Trigger */
	CLEAR_BIT(SFIOR , 7);
	CLEAR_BIT(SFIOR , 6);
	CLEAR_BIT(SFIOR , 5);

	/*ADCSRA.Bits.ADTS=0;*/

#elif ADC_u8AUTO_TRIGGER== ADC_u8TRIGGER_SOURCE_ANALOG_COMP
	/* Enable AUTO Trigger */

	SET_BIT(ADCSRA , 5);
	/*ADCSRA.Bits.ADATE=1;*/

	/* Select Free Run as ANALOG_COMPARATOR Trigger */
	CLEAR_BIT(SFIOR , 7);
	CLEAR_BIT(SFIOR , 6);
	SET_BIT(SFIOR , 5);

	/*ADCSRA.Bits.ADTS=1;*/

#elif ADC_u8AUTO_TRIGGER==ADC_u8TRIGGER_SOURCE_EXT_INT_REQ0
	/* Enable AUTO Trigger */

	SET_BIT(ADCSRA , 5);

	/*ADCSRA.Bits.ADATE=1;*/

	/* Select Free Run as EXTERNAL INTERPUT Trigger */
	CLEAR_BIT(SFIOR , 7);
	SET_BIT(SFIOR , 6);
	CLEAR_BIT(SFIOR , 5);

	/*ADCSRA.Bits.ADTS=2;*/


#elif ADC_u8AUTO_TRIGGER==ADC_u8TRIGGER_SOURCE_TIMER_COMP_MATCH
	/* Enable AUTO Trigger */

	SET_BIT(ADCSRA , 6);
	/*ADCSRA.Bits.ADATE=1;*/

	/* Select Free Run as COMPARE_MATCH Trigger */
	CLEAR_BIT(SFIOR , 7);
	SET_BIT(SFIOR , 6);
	SET_BIT(SFIOR , 5);

	/*ADCSRA.Bits.ADTS=3;*/

#elif ADC_u8AUTO_TRIGGER== ADC_u8TRIGGER_SOURCE_TIMER_0_OVF
	/* Enable AUTO Trigger */
	SET_BIT(ADCSRA , 5);

	/*ADCSRA.Bits.ADATE=1;*/

	/* Select Free Run as TIMER0_OVERFLOW Trigger */

	SET_BIT(SFIOR , 7);
	CLEAR_BIT(SFIOR , 6);
	CLEAR_BIT(SFIOR , 5);

	/*ADCSRA.Bits.ADTS=4;*/

#elif ADC_u8AUTO_TRIGGER== ADC_u8TRIGGER_SOURCE_TIMER_COMP_MATCH_B
	/* Enable AUTO Trigger */
	SET_BIT(ADCSRA , 7);
	/*ADCSRA.Bits.ADATE=1;*/

	/* Select Free Run as TIMER0_OVERFLOW Trigger */
	SET_BIT(SFIOR , 7);
	CLEAR_BIT(SFIOR , 6);
	SET_BIT(SFIOR , 5);
	/*ADCSRA.Bits.ADTS=5;*/

#elif ADC_u8AUTO_TRIGGER== ADC_u8TRIGGER_SOURCE_TIMER_1_OVF
	/* Enable AUTO Trigger */
	SET_BIT(ADCSRA , 7);

	/*ADCSRA.Bits.ADATE=1;*/

	/* Select Free Run as TIMER1_OVERFLOW Trigger */


#elif ADC_u8AUTO_TRIGGER== ADC_u8TRIGGER_SOURCE_TIMER_1_CAPT
	/* Enable AUTO Trigger */
	SET_BIT(ADCSRA , 5);
	/*ADCSRA.Bits.ADATE=1;*/

	/* Select Free Run as TIMER1_CAPTURE_EVENT Trigger */
	SET_BIT(SFIOR , 7);
	SET_BIT(SFIOR , 6);
	SET_BIT(SFIOR , 5);

	/*ADCSRA.Bits.ADTS=6;*/
#endif

	/* Enable ADC module */
	SET_BIT(ADCSRA,ADEN);

	/* Disable start conversion it will be enabled in adc_read Fun*/
	CLEAR_BIT(ADCSRA,ADSC);

	/* Clear ADIF Flag */
	SET_BIT(ADCSRA,ADIF);


#if (ADC_uint8IMPLEMENTATION_BASED == ADC_uint8INTERRUPT_BASED)
	/* Enable interrupt*/
	SET_BIT(ADCSRA,ADIE);
	/* ACSRA.Bits.ADIE = 1
	 */
#elif (ADC_u8IMPLEMENTATION_BASED == ADC_u8POOLLING_BASED)
	/* Disable interrupt*/
	CLEAR_BIT(ADCSRA,ADIE);


#endif

	/* Set the required Prescaler */
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler) ;

}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
#if ADC_u8RESULT_ADJUST == ADC_u8RIGHT_ADJUST

uint16 ADC_readChannel(uint8 Chnl_Id)

#elif ADC_u8RESULT_ADJUST == ADC_u8LEFT_ADJUST

uint8 ADC_readChannel(uint8 Chnl_Id)

#endif
{
	/* Input channel number must be from 0 --> 7 */
	Chnl_Id &= 0x07;

	/* Clear first 5 bits in the ADMUX (channel number  :0 bits) before set the required channel */
	ADMUX &= 0xE0;
	/*
	 * ADMUX.Bits.MUX = 0;
	 */
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = ADMUX | Chnl_Id;

	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA,ADSC);
	/*ADCSRA.Bits.ADSC = 1;*/

	/* Read the digital value from the data register */

#if ADC_u8RESULT_ADJUST == ADC_u8RIGHT_ADJUST
	uint16 Result=0;
	Result=ADCL;
	Result|=((ADCH)<<8);

#elif ADC_u8RESULT_ADJUST == ADC_u8LEFT_ADJUST
	Result = ADCH ;
#endif

	return Result;

}
