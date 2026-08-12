/*
 * EEPROM_register.h
 *
 * Created: 12/6/2025 7:38:30 PM
 *  Author: mahmo
 */ 


#ifndef EEPROM_REGISTER_H_
#define EEPROM_REGISTER_H_


#define EEARLH_REG   *((volatile u16*)0x3E) //eeprom address register
#define EEARH1  9
#define EEARH0  8
#define EEARL7  7
#define EEARL6  6
#define EEARL5  5
#define EEARL4  4
#define EEARL3  3
#define EEARL2  2
#define EEARL1  1
#define EEARL0  0


#define EEDR_REG   *((volatile u8*)0x3D) // eeprom data register
#define EEDR7  7
#define EEDR6  6
#define EEDR5  5
#define EEDR4  4
#define EEDR3  3
#define EEDR2  2
#define EEDR1  1
#define EEDR0  0

#define EECR_REG   *((volatile u8*)0x3C) // eeprom control register
#define EERIE   3
#define EEMWE   2
#define EEWE    1
#define EERE    0

#endif /* EEPROM_REGISTER_H_ */