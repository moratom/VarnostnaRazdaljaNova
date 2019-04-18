/*
 * Funkcije.cpp
 *
 *  Created on: Apr 11, 2019
 *      Author: matevz
 */
#include"Varnostna.h"
#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


float temperatura(void){
  int tempReading = analogRead(pinTemp);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;
  return tempC ;
}


float razdalja(void){
  int duration;
  float distance;
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  duration = pulseIn(pinEcho, HIGH,20000); //zadnja paramater je maksimalni čas, v us ki naj ga funkcija počaka.
  Serial.println(duration);
  distance = float(duration) * 0.034 / 2;
  return distance;

}





