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
#include <EEPROM.h>


#define pinEcho 2
#define pinTrig 3
#define pinTemp A1
#define pinHitrost A2
#define NAZAJ '*'
#define pinZvok 10

typedef struct podatki{
	/*
	 * Podatki za vsakega uporabnika
	 */
	int msVarnostneRazdalje, refreshRate, koefTemp, temp, zvok, lucke;
	void (*prikazPointer)(struct podatki*);
} podatki;

typedef struct {
	int x,y;
	char slikica;
}slikica;

extern LiquidCrystal_I2C lcd;
extern Keypad tipkovnica;

//FUNKCIJE ZA MENI
int prikazujMeni(char **meniPointer, int velikostMenija); //vrne kje v meniju je uporabnik izbral opcijo
void prikaziMeni(int zacetekPrikaza, int velikostMenija, char **meni);
void prikazOsnovni(podatki* pointerPodatki);
void prikazRazdalje(podatki* pointerPodatki);
void prikazHitrost(podatki* pointerPodatki);
void prikazSpremenjen(char tekst[]);
void izbrisiToFunkcijo(void);
void prikazGraficni1(podatki* pointerPodatki);
void spremeniPodatek(char tekst[10],char enota[4],int *podatek, int maks, int min, byte stUporabnika, podatki* pointerPodatki);
void uporabnikSpremenjen(int stUporabnika);
void prikazPonastaviNastavitve(int stUporabnika);
void prikaziAvto(int zamikX,int zamikY, slikica* slika);
void izdelajZnake();
void standardnoOpozaranjanje(podatki* pointerPodatki);


//SENZORJI
float temperatura(void);
float razdalja(void);
int Hitrost(void);
int idealnaVarnostna(int hitrost, long msIdealneVarnostne);
int koefVarnostneRazdalje(int hitrost, float razdalja, long msIdealneVarnostne);
long razdeli(long x, long in_min, long in_max, long out_min, long out_max);

//EEPROM
void zapisiNaEEPROM(int naslov, podatki podatek);
void beriIzEEPROM(int naslov, podatki *podatek);



#endif /* VARNOSTNA_H_ */
