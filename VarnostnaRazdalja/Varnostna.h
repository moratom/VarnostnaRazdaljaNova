/*
 * Varnostna.h
 *
 *  Created on: Apr 11, 2019
 *      Author: root
 */

#ifndef VARNOSTNA_H_
#define VARNOSTNA_H_

#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define pinEcho 2
#define pinTrig 3
#define pinTemp A1
#define velikostGlavniMeni 7
#define velikostNastavitveSenzorja 6

float temperatura(void);
float razdalja(void);




#endif /* VARNOSTNA_H_ */
