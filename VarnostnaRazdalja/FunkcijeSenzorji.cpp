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
  distance = float(duration) * 0.034 / 2;
  return distance;
}

int Hitrost(void){
	int napetost = analogRead(pinHitrost);
	int hitrost = razdeli(napetost, 0 , 1024, 0 , 220);
	return hitrost;
}

int idealnaVarnostna(int hitrost, int msIdealneVarnostne){
	return ((float)hitrost / 3.6) * (float)msIdealneVarnostne / 1000;
}

int koefVarnostneRazdalje(int hitrost, float razdalja, int msIdealneVarnostne){ //vrne koeficiet med 0 - 300, kjer je 100 idealana razdalja, 300 pa 3x itd
	int idealVarnostna = idealnaVarnostna(hitrost, msIdealneVarnostne);
	int koef = (int)(100* razdalja) / idealVarnostna;
	if(hitrost < 15) return 0;
	else if(koef > 200) koef = 200;
	return koef;
}

long razdeli(long x, long in_min, long in_max, long out_min, long out_max) {
	if(x > in_max) x = in_max;
	if(x < in_min) x = in_min;
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}





