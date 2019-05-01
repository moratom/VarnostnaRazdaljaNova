/*
 * Varnostna.h
 *
 *  Created on: Apr 11, 2019
 *      Author: matevz
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
#define pinHitrost A2
#define NAZAJ '*'


//FUNKCIJE ZA MENI
int prikazujMeni(char **meniPointer, int velikostMenija); //vrne kje v meniju je uporabnik izbral opcijo
void prikaziMeni(int zacetekPrikaza, int velikostMenija, char **meni);
void prikazOsnovni(void);
void prikazRazdalje(void);
void prikazHitrost(void);
void prikazSpremenjen(char tekst[]);
void izbrisiToFunkcijo(void);
void prikazGraficni1(void);
void spremeniIdealnoVarnostno(void);


//SENZORJI
float temperatura(void);
float razdalja(void);
int Hitrost(void);
int idealnaVarnostna(int hitrost, int msIdealneVarnostne);
int koefVarnostneRazdalje(int hitrost, float razdalja, int msIdealneVarnostne);
long razdeli(long x, long in_min, long in_max, long out_min, long out_max);




#endif /* VARNOSTNA_H_ */
