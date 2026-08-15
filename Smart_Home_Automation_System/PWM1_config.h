/*
 * PWM1_config.h
 *
 * Created: 11/16/2025 9:42:37 PM
 *  Author: hussain zaid
 */ 


#ifndef PWM1_CONFIG_H_
#define PWM1_CONFIG_H_

/*Options For Fast PWM1  Operation Mode
1- PWM1_FAST_MODE_14
2- PWM1_FAST_MODE_15
*/
#define PWM1_MODE		PWM1_FAST_MODE_14

/*Options For Fast PWM1  Compare Mode
1- PWM1_NON_INVERTING_MODE
2- PWM1_INVERTING_MODE
*/
#define PWM1_COMPARE_MODE  PWM1_NON_INVERTING_MODE

#define TMR1_PRESCALER     64

#endif /* PWM1_CONFIG_H_ */