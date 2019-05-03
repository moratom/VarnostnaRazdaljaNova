#include <Arduino.h>
#include <HardwareSerial.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <stddef.h>

#include "/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/standard/pins_arduino.h"
#include "Varnostna.h"

#define velikostGlavniMeni 4
#define velikostIzborPrikazaMeni 5
#define velikostNastavitve 5
#define velikostUporabniki 6


////////////////////////////////////LCD IN KEYPAD INCIALIZACIJA CLASSOV/////////////////////////////
LiquidCrystal_I2C lcd(0x3F, 20, 4);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
 { '1', '2', '3', 'A' },
 { '4', '5', '6', 'B' },
 {'7', '8', '9', 'C' },
 { '*', '0', '#', 'D' },
 };
byte rowPins[ROWS] = { A15, A14, A13, A12 }; // @suppress("Symbol is not resolved")
byte colPins[COLS] = { A11, A10, A9, A8 }; // @suppress("Symbol is not resolved")
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
//////////////////////////////////////////////////////////////////////////////////////////////////

int velikostGM = velikostGlavniMeni;
int velikostIP = velikostIzborPrikazaMeni;
int velikostNS = velikostNastavitve;
int velikostUP = velikostUporabniki;

///////////////////////////////////////////////////////////////////////////////////////////////
podatki privzeto = {1500, 500,100, 3 , prikazOsnovni};
podatki uporabnik[6];
podatki *pointerPodatki = &privzeto;
byte stUporabnika;




//AVTO//
///////////////////////////////////////////////////////////////////////////
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
"Izberi uporabnika  ",
 };

char *izborPrikaza[] = {
"Osnovni prikaz     ",
"Hitrost            ",
"Razdalje           ",
"Graficni prikaz 1  ",
"Graficni prikaz 2  ",
};

char *nastavitve[] = {
"Idealna varnost    ",
"Vpliv temeperature ",
"Refresh rate       ",
"Mejna temperatura  ",
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

	///EEPROM BRANJE///////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 0; i < 6; i++){
		beriIzEEPROM(i*(sizeof(podatki)), uporabnik + i);
		//*(uporabnik + i) = privzeto; //ZA POENOSTAVIT VSE UPORABNIKE NA PRIVZETE VREDNOSTI
		//zapisiNaEEPROM(i * sizeof(podatki), *(uporabnik + i));
	}
	stUporabnika = EEPROM.read(6*sizeof(podatki));
	pointerPodatki = uporabnik + stUporabnika;


	//////////////////////////////
	prikaziMeni(0, velikostGM, glavniMeni);
	int *velikostPointer = &velikostGM;
	char **meniPointer = glavniMeni;
	int zacetek;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////77
	while (1) {
		zacetek = prikazujMeni(meniPointer, *velikostPointer);
		if (meniPointer == glavniMeni) {
			switch (zacetek) {
			case 0:
				(*pointerPodatki).prikazPointer();
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
			case 4:
				(*pointerPodatki).prikazPointer = prikazRazdalje;
				zapisiNaEEPROM(stUporabnika * sizeof(podatki), *pointerPodatki);
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
				spremeniPodatek("varnostna",&(*pointerPodatki).msVarnostneRazdalje, 5000 , 500);
				break;
			case 1:
				spremeniPodatek("koef temp",&(*pointerPodatki).koefTemp, 300 , 100);
				break;
			case 2:
				spremeniPodatek("refr rate", &(*pointerPodatki).refreshRate, 2000, 100);
				break;
			case 3:
				spremeniPodatek("mejna temp", &(*pointerPodatki).temp, 30, 0);
				break;
			case 4:
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
				EEPROM.write(6*sizeof(podatki),stUporabnika);
				uporabnikSpremenjen(stUporabnika + 1);
				break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void prikazOsnovni(void) { //najbolj osnoven prikaz (pokaže meritve vseh senzorjev na mikrokontrolerju)
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
	unsigned long int time1 = millis();
	while (a != NAZAJ) {
		if (millis() - time1 > (*pointerPodatki).refreshRate) {

			temp = temperatura();
			dolzina = razdalja();
			hitrost = Hitrost();
			koef = koefVarnostneRazdalje(hitrost, dolzina, (*pointerPodatki).msVarnostneRazdalje);
			if(temp < (*pointerPodatki).temp){
				koef = koefVarnostneRazdalje(hitrost, dolzina, ((*pointerPodatki).msVarnostneRazdalje * ((*pointerPodatki).koefTemp / 10))/10);
			}
			lcd.setCursor(12, 0);
			lcd.print(temp);
			lcd.print(" C ");
			lcd.setCursor(9, 1);
			lcd.print(dolzina);
			lcd.print(" m   ");
			lcd.setCursor(8, 2);
			lcd.print(hitrost);
			lcd.print(" km/h   ");
			lcd.setCursor(11, 3);
			lcd.print(koef);
			lcd.print("   ");
			time1 += (*pointerPodatki).refreshRate;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
	lcd.clear();
}


void prikazRazdalje(void) {
	int idealVarnostna, varnostna;
	lcd.clear();
	lcd.noCursor();
	char a = NULL; //inicializirano da nebi slučajno takoj skočlo vn iz prikaza, preden prvič vstopiš v while zanko
	lcd.setCursor(0, 0);
	lcd.print("Varnostna razdalja: ");
	lcd.setCursor(0, 2);
	lcd.print("Idealna varnostna: ");
	unsigned long int time1 = millis();
	while (a != NAZAJ) {
		if (millis() - time1 > (*pointerPodatki).refreshRate) {
			varnostna = razdalja();
			idealVarnostna = idealnaVarnostna(Hitrost(), (*pointerPodatki).msVarnostneRazdalje);
			if(temperatura() < (*pointerPodatki).temp){
				idealVarnostna = idealnaVarnostna(Hitrost(), ((*pointerPodatki).msVarnostneRazdalje * ((*pointerPodatki).koefTemp / 10))/10);
			}
			lcd.setCursor(8, 1);
			lcd.print(varnostna);
			lcd.print("m     ");
			lcd.setCursor(8, 3);
			lcd.print(idealVarnostna);
			lcd.print("m     ");
			time1 += (*pointerPodatki).refreshRate;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
	lcd.clear();
}

void prikazHitrost(void) {
	char a = NULL;
	lcd.clear();
	lcd.noCursor();
	lcd.print("Hitrost:");
	unsigned long time1 = millis();
	while (a != NAZAJ) {
		if (millis() - time1 > (*pointerPodatki).refreshRate) {
			lcd.setCursor(8, 1);
			lcd.print(Hitrost());
			lcd.print(" km/h   ");
			time1 += (*pointerPodatki).refreshRate;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
}

void prikazGraficni1(void) {
	char a = NULL;
	int zamikX = 0, zamikY = 0, koef;
	lcd.clear();
	lcd.noCursor();
	unsigned long time1 = millis();
	while (a != NAZAJ) {
		if (millis() - time1 > (*pointerPodatki).refreshRate) {
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
			if(temperatura() < (*pointerPodatki).temp){
				koef = koefVarnostneRazdalje(Hitrost(), razdalja(), (*pointerPodatki).msVarnostneRazdalje);
			}
			koef = koefVarnostneRazdalje(Hitrost(), razdalja(), ((*pointerPodatki).msVarnostneRazdalje * ((*pointerPodatki).koefTemp / 10))/10);
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
			time1 += (*pointerPodatki).refreshRate;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

void uporabnikSpremenjen(int stUporabnika) {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Uporabnik");
	lcd.setCursor(0, 1);
	lcd.print("spremenjen:");
	lcd.setCursor(0, 2);
	lcd.print(stUporabnika);
	lcd.print(" uporabnik.");
	lcd.noCursor();
	delay(1000);
	lcd.cursor();
	lcd.clear();
}

void prikazPonastaviNastavitve(int stUporabnika) {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Nastavitve pooenost. ");
	lcd.setCursor(0, 1);
	lcd.print("za uporabnika ");
	lcd.print(stUporabnika);
	lcd.noCursor();
	delay(1000);
	lcd.cursor();
	lcd.clear();
}





void spremeniPodatek(char tekst[10], int *podatek, int maks, int min){
	char a = NULL;
	int celota = 0, i ;
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Vrednost ");
	lcd.print(tekst);
	lcd.print(": ");
	lcd.setCursor(0, 1);
	lcd.print(*podatek);
	lcd.setCursor(0,2);
	lcd.print("Uporabnik: ");
	lcd.print((unsigned int)stUporabnika +1);
	lcd.setCursor(0,3);
	lcd.print("Spremeba --> D  ");
	while (a != NAZAJ) {
		a = customKeypad.getKey();
		if(a == 'D'){
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Vpisite ");
			lcd.print(tekst);
			lcd.print(": ");
			lcd.setCursor(0,1);
			lcd.print("(med ");
			lcd.print(min);
			lcd.print(" in ");
			lcd.print(maks);
			lcd.print(")");
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
			else if(min <= celota && celota <= maks){
				 *podatek = celota;
				 zapisiNaEEPROM((unsigned int)stUporabnika * sizeof(podatki), *pointerPodatki);
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

///////////////////////////////////////////////////////////////////////////////////////////////////
////EEPROM/////

void zapisiNaEEPROM(int naslov, podatki podatek){
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

