# Fan_Controller_Project
 
Build-Driver for Fan controlling using peripherals DIO, ADC and PWM. Implement the following Fan Controller system with the specifications listed below:

The aim of this project is to design a temperature-controlled fan using ATmega32 microcontroller, in which the fan is automatically turned ON or OFF according to the temperature. Use ATmega16 Microcontroller with frequency 1Mhz.
In this project, the LM35 temperature sensor will give continuous analog output corresponding to the temperature sensed by it. This analog signal is given to the ADC, which converts the analog values to digital values.
The digital output of the ADC is equivalent to sensed analog voltage.
In order to get the temperature from the sensed analog voltage, we need to perform some calculations in the programming for the microcontroller.
Once the calculations are done by the microcontroller according to the logic, the temperature is displayed on the LCD.
The microcontroller will continuously monitor the temperature and based on the temperature value, the microcontroller will drive the fan like that: a. If the temperature is less than 30C turn off the fan. b. If the temperature is greater than or equal 30C turn on the fan with 25% of its maximum speed. c. If the temperature is greater than or equal 60C turn on the fan with 50% of its maximum speed. d. If the temperature is greater than or equal 90C turn on the fan with 75% of its maximum speed.e. If the temperature is greater than or equal 120C turn on the fan with 100% of its maximum speed.
The main principle of the circuit is to switch on/off the fan connected to DC motor based on temperature value. The DC-Motor rotates in clock-wise direction or stopped based on the fan state.
The LCD should display the temperature value and the fan state continuously.
Control the DC-Motor speed using PWM signal generated from Timer0.

![image](https://github.com/saraemaam/Fan_Controller_Project/assets/44003494/f42e995b-d665-4828-8ab4-7f87145d87b4)
