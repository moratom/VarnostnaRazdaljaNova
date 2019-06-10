#include <Arduino.h>
#include <HardwareSerial.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <stddef.h>

#include "Varnostna.h"

#define velikostGlavniMeni 4
#define velikostIzborPrikazaMeni 4
#define velikostNastavitve 6
#define velikostUporabniki 6


////////////////////////////////////LCD IN KEYPAD INCIALIZACIJA CLASSOV/////////////////////////////

LiquidCrystal_I2C lcd(0x3F, 20, 4);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
 { '1', '2', '3', 'A' },
 { '4', '5', '6', 'B' },
 {'7', '8', '9', 'C' },
 { '*', '0', '#', 'D' },
 };
byte rowPins[ROWS] = { A15, A14, A13, A12 }; // @suppress("Symbol is not resolved")
byte colPins[COLS] = { A11, A10, A9, A8 }; // @suppress("Symbol is not resolved")
Keypad tipkovnica = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//////////////////////////////////////////////////////////////////////////////////////////////////
//Velikosti menijev, incializirane kot spremenljivke, da se jih da podat po naslovu
int velikostGM = velikostGlavniMeni;
int velikostIP = velikostIzborPrikazaMeni;
int velikostNS = velikostNastavitve;
int velikostUP = velikostUporabniki;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Deklarirani podatki in privzete nastavitve za uporabnika (glej v header file, kjer je definiran tip podatki
podatki privzeto = {1500, 500,100, 3 , 0 , 1, prikazOsnovni}; // @suppress("Invalid arguments")
podatki uporabnik[6];
podatki *pointerPodatki = &privzeto;
byte stUporabnika; //podatek o tem kdo je trenutni uporabnik


char *glavniMeni[] = {
"Prikaz             ",
"Izbor prikaza      ",
"Nastavitve         ",
"Izberi uporabnika  ",
 };

char *izborPrikaza[] = {
"Osnovni prikaz     ",
"Hitrost            ",
"Razdalje           ",
"Graficni prikaz    ",
};

char *nastavitve[] = {
"Idealna varnost    ",
"Vpliv temeperature ",
"Refresh rate       ",
"Mejna temperatura  ",
"Zvocno opozorilo   ",
"Ponastavi privzeto ",
};

char *uporabniki[] = {
"Uporabnik 1        ",
"Uporabnik 2        ",
"Uporabnik 3        ",
"Uporabnik 4        ",
"Uporabnik 5        ",
"Uporabnik 6        ",
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void) {
	init();
	Serial.begin(9600);
	pinMode(pinTemp, INPUT);
	pinMode(pinTrig, OUTPUT);
	pinMode(pinEcho, INPUT);
	pinMode(pinZvok, OUTPUT);
	digitalWrite(pinZvok, 0);
	lcd.init();
	lcd.backlight();
	lcd.cursor();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
	//Ustvari nove znake za grafiko
	izdelajZnake();
	///EEPROM BRANJE///////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 0; i < 6; i++){
		beriIzEEPROM(i*(sizeof(podatki)), uporabnik + i);
		/*//ZA POENOSTAVIT VSE UPORABNIKE NA PRIVZETE VREDNOSTI
		*(uporabnik + i) = privzeto;
		zapisiNaEEPROM(i * sizeof(podatki), *(uporabnik + i));
		*/
	}
	stUporabnika = EEPROM.read(6*sizeof(podatki));
	pointerPodatki = uporabnik + stUporabnika;


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	prikaziMeni(0, velikostGM, glavniMeni);
	int *velikostPointer = &velikostGM;
	char **meniPointer = glavniMeni;
	int zacetek;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (1) {
		zacetek = prikazujMeni(meniPointer, *velikostPointer);
		if (meniPointer == glavniMeni) {
			switch (zacetek) {
			case 0:
				(*pointerPodatki).prikazPointer(pointerPodatki);
				break;
			case 1:
				meniPointer = izborPrikaza;
				velikostPointer = &velikostIP;
				break;
			case 2:
				meniPointer = nastavitve;
				velikostPointer = &velikostNS;
				break;
			case 3:
				meniPointer = uporabniki;
				velikostPointer = &velikostUP;
			}

		} else if (meniPointer == izborPrikaza) {
			switch (zacetek) {
			case -1:
				meniPointer = glavniMeni;
				velikostPointer = &velikostGM;
				break;
			case 0:
				(*pointerPodatki).prikazPointer= prikazOsnovni;
				zapisiNaEEPROM((unsigned int)stUporabnika * sizeof(podatki), *pointerPodatki);
				prikazSpremenjen("Osnovni prikaz");
				break;
			case 1:
				(*pointerPodatki).prikazPointer = prikazHitrost;
				zapisiNaEEPROM(stUporabnika * sizeof(podatki), *pointerPodatki);
				prikazSpremenjen("Prikaz hitrost");
				break;
			case 2:
				(*pointerPodatki).prikazPointer = prikazRazdalje;
				zapisiNaEEPROM(stUporabnika * sizeof(podatki), *pointerPodatki);
				prikazSpremenjen("Prikaz razdalj");
				break;
			case 3:
				(*pointerPodatki).prikazPointer = prikazGraficni1;
				zapisiNaEEPROM(stUporabnika * sizeof(podatki), *pointerPodatki);
				prikazSpremenjen("Grafika 1 ");
				break;
			}
		} else if(meniPointer == nastavitve) {
			switch(zacetek) {
			case -1:
				meniPointer = glavniMeni;
				velikostPointer = &velikostGM;
				break;
			case 0:
				spremeniPodatek("varnostna","ms",&(*pointerPodatki).msVarnostneRazdalje, 5000 , 500, stUporabnika,pointerPodatki);
				break;
			case 1:
				spremeniPodatek("koef temp", "%",&(*pointerPodatki).koefTemp, 300 , 100,stUporabnika,pointerPodatki);
				break;
			case 2:
				spremeniPodatek("refr rate", "ms",&(*pointerPodatki).refreshRate, 2000, 100,stUporabnika,pointerPodatki);
				break;
			case 3:
				spremeniPodatek("mejna temp", "C",&(*pointerPodatki).temp, 30, 0,stUporabnika,pointerPodatki);
				break;
			case 4:
				spremeniPodatek("zvok", " ",&(*pointerPodatki).zvok, 1, 0,stUporabnika,pointerPodatki);
				break;
			case 5:
				*pointerPodatki = privzeto;
				zapisiNaEEPROM((unsigned int)stUporabnika * sizeof(podatki), *pointerPodatki);
				prikazPonastaviNastavitve(stUporabnika + 1);
				break;
			}
		} else if(meniPointer == uporabniki) {
			switch(zacetek) {
			case -1:
				meniPointer = glavniMeni;
				velikostPointer = &velikostGM;
				break;
			default:
				stUporabnika = zacetek;
				pointerPodatki = uporabnik + stUporabnika;
				EEPROM.write(6*sizeof(podatki),stUporabnika); //vrednost stUporabnika se nahaja za podatki
				meniPointer = glavniMeni;
				velikostPointer = &velikostGM;
				uporabnikSpremenjen(stUporabnika + 1);
				break;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
////EEPROM/////

void standardnoOpozaranjanje(podatki* pointerPodatki){
	static unsigned long time = 0;
	static bool piskaj = 1;
	static unsigned int delay = 300;
	int koef = koefVarnostneRazdalje(Hitrost(), razdalja(), (*pointerPodatki).msVarnostneRazdalje);
	if(pointerPodatki->zvok){
		if(millis()- time > delay){
			time += delay;
			delay = koef != 0 ? razdeli(koef,30,100,200,500):500;
			if(delay >= 500){
				digitalWrite(pinZvok, 0);
			}
			else{
				digitalWrite(pinZvok, piskaj);
				piskaj = !piskaj;
			}
		}
	}
	if(pointerPodatki->lucke){
		;	//za napisat
	}
}

void zapisiNaEEPROM(int naslov, podatki podatek){
	/*
	 * Zapise podatke od podanega naslova na EEPROM
	 */
	byte *pointer = (byte*)&podatek;
	for(int i = 0; i < sizeof(podatki); i++){
		EEPROM.write((naslov + i),*(pointer + i));
	}
}

void beriIzEEPROM(int naslov, podatki *podatek){
	byte *pointer = (byte*)podatek;
	for(int i = 0; i < sizeof(podatki); i++){
		*(pointer + i) = EEPROM.read(naslov + i);
	}
}

