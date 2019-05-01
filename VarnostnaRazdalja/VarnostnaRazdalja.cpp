#include <Arduino.h>
#include <HardwareSerial.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <stddef.h>

#include "/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/standard/pins_arduino.h"
#include "Varnostna.h"

#define velikostGlavniMeni 3
#define velikostIzborPrikazaMeni 5
#define velikostNastavitve 3

int velikostGM = velikostGlavniMeni;
int velikostIP = velikostIzborPrikazaMeni;
int velikostNS = velikostNastavitve;
int msVarnostneRazdalje = 1500;

LiquidCrystal_I2C lcd(0x3F, 20, 4);


//AVTO//
/////////////////////////////////////////////////////7
byte kolo[8] = { 0x0E, 0x0E, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, };

byte prednjiDel[8] = { 0x0, 0x0, 0x0, 0x0, 0x1, 0x1F, 0x1F, 0x1F, };

byte srednjiDel[8] = { 0x0, 0x0, 0x0, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, };

byte zadnjiDel[8] { 0x0, 0x0, 0x0, 0x0, 0x10, 0x1F, 0x1F, 0x1F, };
/////////////////////////////////////////////////////////////////////////


//DRUGA GRAFIKA//
////////////////////////////////////////////
byte crtaDesna[8] = {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};

byte polniBlok[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};



////////////////////////////////////////////////777


char *glavniMeni[] = {
"Prikaz             ",
"Izbor prikaza      ",
"Nastavitve         ",
 };

char *izborPrikaza[] = {
"Osnovni prikaz     ",
"Hitrost            ",
"Razdalje           ",
"Graficni prikaz 1  ",
"Graficni prikaz 2  ", };

char *nastavitve[] = {
"Idealna varnost    ",
"Vpliv temeperature ",
"Poonastavi privzet ",
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
 { '1', '2', '3', 'A' },
 { '4', '5', '6', 'B' },
 {'7', '8', '9', 'C' },
 { '*', '0', '#', 'D' },
 };
byte rowPins[ROWS] = { A15, A14, A13, A12 }; //connect to the row pinouts of the keypad // @suppress("Symbol is not resolved")
byte colPins[COLS] = { A11, A10, A9, A8 }; //connect to the column pinouts of the keypad // @suppress("Symbol is not resolved")

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS,
		COLS);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	init();
	Serial.begin(9600);
	pinMode(pinTemp, INPUT);
	pinMode(pinTrig, OUTPUT);
	pinMode(pinEcho, INPUT);
	lcd.init();
	lcd.backlight();
	lcd.cursor();
	/////////////////////////////////////////////////
	lcd.createChar(1, kolo);
	lcd.createChar(2, prednjiDel);
	lcd.createChar(3, srednjiDel);
	lcd.createChar(4, zadnjiDel);
	lcd.createChar(5, crtaDesna);
	lcd.createChar(6, polniBlok);

	//////////////////////////////////////////////////
	prikaziMeni(0, velikostGM, glavniMeni);
	void (*prikazPointer)() = prikazOsnovni;
	int *velikostPointer = &velikostGM;
	char **meniPointer = glavniMeni;
	int zacetek;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////77
	while (1) {
		zacetek = prikazujMeni(meniPointer, *velikostPointer);
		if (meniPointer == glavniMeni) {
			switch (zacetek) {
			case 0:
				prikazPointer();
				break;
			case 1:
				meniPointer = izborPrikaza;
				velikostPointer = &velikostIP;
				break;
			case 2:
				meniPointer = nastavitve;
				velikostPointer = &velikostNS;
				break;

			}
		} else if (meniPointer == izborPrikaza) {
			switch (zacetek) {
			case -1:
				meniPointer = glavniMeni;
				velikostPointer = &velikostGM;
				break;
			case 0:
				prikazPointer = prikazOsnovni;
				prikazSpremenjen("Osnovni prikaz");
				break;
			case 1:
				prikazPointer = prikazHitrost;
				prikazSpremenjen("Prikaz hitrost");
				break;
			case 2:
				prikazPointer = prikazRazdalje;
				prikazSpremenjen("Prikaz razdalj");
				break;
			case 3:
				prikazPointer = prikazGraficni1;
				prikazSpremenjen("Grafika 1 ");
				break;
			case 4:
				prikazPointer = prikazRazdalje;
				prikazSpremenjen(" ");
				break;

			}
		} else if(meniPointer == nastavitve) {
			switch(zacetek) {
			case -1:
				meniPointer = glavniMeni;
				velikostPointer = &velikostGM;
				break;
			case 0:
				spremeniIdealnoVarnostno();
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////7
int prikazujMeni(char **meniPointer, int velikostMenija) {
	char a = NULL;
	int zacetek = 0;
	lcd.clear();
	prikaziMeni(0, velikostMenija, meniPointer);
	while (a != '5') {
		a = customKeypad.getKey();
		if (a == NAZAJ)
			return -1;
		if (a == '2' && zacetek > 0) {
			zacetek -= 1;
			prikaziMeni(zacetek, velikostMenija, meniPointer);
		}
		if (a == '8') {
			if (zacetek < velikostMenija - 1) {
				zacetek += 1;
			} else {
				zacetek = 0;
			}
			prikaziMeni(zacetek, velikostMenija, meniPointer);
		}
	}
	return zacetek;
}

void prikazOsnovni(void) { //najbolj osnoven prikaz (pokaže meritve vseh senzorjev na mikrokontrolerju)
	static unsigned long int time1 = millis();
	float temp, dolzina;
	int hitrost, koef;
	lcd.clear();
	lcd.noCursor();
	char a = NULL; //inicializirano da nebi slučajno takoj skočlo vn iz prikaza, preden prvič vstopiš v while zanko
	lcd.setCursor(0, 0);
	lcd.print("Temperatura: ");
	lcd.setCursor(0, 1);
	lcd.print("Razdalja: ");
	lcd.setCursor(0, 2);
	lcd.print("Hitrost: ");
	lcd.setCursor(0, 3);
	lcd.print("Koeficient: ");
	while (a != NAZAJ) {
		if (millis() - time1 > 500) {

			temp = temperatura();
			dolzina = razdalja();
			hitrost = Hitrost();
			koef = koefVarnostneRazdalje(hitrost, dolzina, msVarnostneRazdalje);
			lcd.setCursor(12, 0);
			lcd.print(temp);
			lcd.print(" C");
			lcd.setCursor(9, 1);
			lcd.print(dolzina);
			lcd.print(" m   ");
			lcd.setCursor(8, 2);
			lcd.print(hitrost);
			lcd.print(" km/h   ");
			lcd.setCursor(11, 3);
			lcd.print(koef);
			lcd.print("   ");
			time1 += 500;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
	lcd.clear();
}

void prikaziMeni(int zacetekPrikaza, int velikostMenija, char **meni) {
	if (velikostMenija < 4) {
		for (int i = 4 - velikostMenija; i > 0; i--) {
			lcd.setCursor(0, 4 - i);
			lcd.print("                   ");
		}
	}
	if (zacetekPrikaza <= 3) {
		for (int i = 0, k = 0; i <= 3 && i < velikostMenija; i++, k++) {
			lcd.setCursor(0, k);
			lcd.print(meni[i]);
			lcd.setCursor(19, zacetekPrikaza);
		}
	} else {
		for (int i = zacetekPrikaza - 3, k = 0;
				i < velikostMenija && i <= zacetekPrikaza; i++, k++) {
			lcd.setCursor(0, k);
			lcd.print(meni[i]);
			lcd.setCursor(19, 3);
		}
	}
}

void prikazSpremenjen(char tekst[]) {
	lcd.clear();
	lcd.setCursor(0, 1);
	lcd.print("Prikaz");
	lcd.setCursor(0, 2);
	lcd.print("Spremenjen");
	lcd.setCursor(0, 3);
	lcd.print(tekst);
	lcd.noCursor();
	delay(1000);
	lcd.cursor();
	lcd.clear();
}

void prikazRazdalje(void) {
	static unsigned long int time1 = millis();
	int idealVarnostna, varnostna;
	lcd.clear();
	lcd.noCursor();
	char a = NULL; //inicializirano da nebi slučajno takoj skočlo vn iz prikaza, preden prvič vstopiš v while zanko
	lcd.setCursor(0, 0);
	lcd.print("Varnostna razdalja: ");
	lcd.setCursor(0, 2);
	lcd.print("Idealna varnostna: ");
	while (a != NAZAJ) {
		if (millis() - time1 > 500) {
			varnostna = razdalja();
			idealVarnostna = idealnaVarnostna(Hitrost(), msVarnostneRazdalje);
			lcd.setCursor(8, 1);
			lcd.print(varnostna);
			lcd.print("m     ");
			lcd.setCursor(8, 3);
			lcd.print(idealVarnostna);
			lcd.print("m     ");
			time1 += 500;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
	lcd.clear();
}

void prikazHitrost(void) {
	char a = NULL;
	static unsigned long time1 = millis();
	lcd.clear();
	lcd.noCursor();
	lcd.print("Hitrost:");
	while (a != NAZAJ) {
		if (millis() - time1 > 500) {
			lcd.setCursor(8, 1);
			lcd.print(Hitrost());
			lcd.print(" km/h   ");
			time1 += 500;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
}

void prikazGraficni1(void) {
	char a = NULL;
	int zamikX = 0, zamikY = 0, koef;

	static unsigned long time1 = millis();
	lcd.clear();
	lcd.noCursor();
	while (a != NAZAJ) {
		if (millis() - time1 > 500) {
			lcd.setCursor(0,0);
			lcd.print("                   ");
			lcd.setCursor(0,1);
			lcd.print("                   ");
			lcd.setCursor(6,2);
			lcd.print(char(5));
			lcd.setCursor(6,3);
			lcd.print(char(5));
			for(int i = 0; i < 4; i++){
				lcd.setCursor(19,i);
				lcd.print(char(6));
			}
			koef = koefVarnostneRazdalje(Hitrost(), razdalja(), msVarnostneRazdalje);
			zamikX = razdeli(koef, 0 , 150 , 16, 0);
			lcd.setCursor(0 + zamikX, 1 + zamikY);
			lcd.print(char(1));
			lcd.setCursor(2 + zamikX, 1 + zamikY);
			lcd.print(char(1));
			lcd.setCursor(0 + zamikX, 0 + zamikY);
			lcd.print(char(2));
			lcd.setCursor(1 + zamikX, 0 + zamikY);
			lcd.print(char(3));
			lcd.setCursor(2 + zamikX, 0 + zamikY);
			lcd.print(char(4));
			time1 += 500;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
}

void spremeniIdealnoVarnostno(void){
	char a = NULL;
	int celota = 0, i ;
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Idealna varnostna: ");
	lcd.setCursor(0, 1);
	lcd.print(msVarnostneRazdalje);
	lcd.setCursor(0,3);
	lcd.print("Spremeba --> D  ");
	while (a != NAZAJ) {
		a = customKeypad.getKey();
		if(a == 'D'){
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Vpisite ms: ");
			lcd.setCursor(0,1);
			lcd.print("(med 500 in 5000)");
			lcd.setCursor(0,2);
			lcd.print("Koncaj --> A");
			lcd.setCursor(0,3);
			for(i = 0;a != 'A'&& i < 5;){
				a = customKeypad.getKey();
				if (a >= '0' && a <= '9') {
					a -= '0';
					celota *= 10;
					celota += (int) a;
					lcd.print((int) a);
					i++;
				}
			}
			if(i == 5){
				lcd.clear();
				lcd.noCursor();
				lcd.print("PREVELIKA ST");
				delay(1000);
				lcd.cursor();
				return;
			}
			else if(500 < celota && celota < 5000){
				 msVarnostneRazdalje = celota;
				 lcd.clear();
				 lcd.noCursor();
				 lcd.print("Vnos uspel");
				 delay(1000);
				 lcd.cursor();
				 return;
			}
			else {
				lcd.clear();
				lcd.noCursor();
				lcd.print("NAPACEN VNOS");
				delay(1000);
				lcd.cursor();
				return;
			}
		}
	}
}

void izbrisiToFunkcijo(void) {
	int stevilo = 0;
	char a;
	int celota = 0;
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Kalkulator");
	lcd.setCursor(0, 1);
	while (1) {
		a = customKeypad.getKey();
		if (a >= '0' && a <= '9') {
			a -= '0';
			celota *= 10;
			celota += (int) a;
			lcd.print((int) a);
		} else if (a == NAZAJ) {
			celota += 5000;
			lcd.print("                  ");
			lcd.print(celota);
		}
	}
}

