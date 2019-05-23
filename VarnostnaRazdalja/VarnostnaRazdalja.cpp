#include <Arduino.h>
#include <HardwareSerial.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <stddef.h>

#include "Varnostna.h"

#define velikostGlavniMeni 4
#define velikostIzborPrikazaMeni 5
#define velikostNastavitve 5
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
podatki privzeto = {1500, 500,100, 3 , prikazOsnovni};
podatki uporabnik[6];
podatki *pointerPodatki = &privzeto;
byte stUporabnika; //podatek o tem kdo je trenutni uporabnik




//AVTO//
///////////////////////////////////////////////////////////////////////////
byte kolo[8] = { 0x0E, 0x0E, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, };

byte prednjiDel[8] = { 0x0, 0x0, 0x0, 0x0, 0x1, 0x1F, 0x1F, 0x1F, };

byte srednjiDel[8] = { 0x0, 0x0, 0x0, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, };

byte zadnjiDel[8] { 0x0, 0x0, 0x0, 0x0, 0x10, 0x1F, 0x1F, 0x1F, };

char Kolo = 1, PrednjiDel = 2, SrednjiDel = 3, ZadnjiDel = 4, CrtaDesna = 5, PolniBlok = 6; //že narejeni novi charracterji

slikica avto[] = {
		{0,1,Kolo},
		{2,1,Kolo},
		{0,0, PrednjiDel},
		{1,0, SrednjiDel},
		{2,0, ZadnjiDel},
		{-1,-1, 0}
};

/////////////////////////////////////////////////////////////////////////


//DRUGA GRAFIKA//
////////////////////////////////////////////
byte crtaDesna[8] = {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};

byte polniBlok[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
////////////////////////////////////////////////777


char *glavniMeni[] = {
"Prikaz a           ",
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
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
	//Ustvari nove znake za grafiko
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
				spremeniPodatek("varnostna","ms",&(*pointerPodatki).msVarnostneRazdalje, 5000 , 500);
				break;
			case 1:
				spremeniPodatek("koef temp", "%",&(*pointerPodatki).koefTemp, 300 , 100);
				break;
			case 2:
				spremeniPodatek("refr rate", "ms",&(*pointerPodatki).refreshRate, 2000, 100);
				break;
			case 3:
				spremeniPodatek("mejna temp", "C",&(*pointerPodatki).temp, 30, 0);
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
				EEPROM.write(6*sizeof(podatki),stUporabnika); //vrednost stUporabnika se nahaja za podatki
				meniPointer = nastavitve;
				uporabnikSpremenjen(stUporabnika + 1);
				break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////


void prikaziMeni(int zacetekPrikaza, int velikostMenija, char **meni) {
	/*
	 * Funkcija prejme array stringov in ga prikaže.
	 */
	if (velikostMenija < 4) { //Pobriše samo prazne vrstice, dela boljše kot lcd.clear(), ker potem ni utripanja
		for (int i = 4 - velikostMenija; i > 0; i--) {
			lcd.setCursor(0, 4 - i);
			lcd.print("                   ");
		}
	}
	if (zacetekPrikaza <= 3) { //Vedno prikaže isto, premika se le cursor
		for (int i = 0, k = 0; i <= 3 && i < velikostMenija; i++, k++) {
			lcd.setCursor(0, k);
			lcd.print(meni[i]);
			lcd.setCursor(19, zacetekPrikaza);
		}
	} else {//Prikaže tistega na ki je zbran in 3 nad njim
		for (int i = zacetekPrikaza - 3, k = 0; i < velikostMenija && i <= zacetekPrikaza; i++, k++) {
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
	long msNove = (long)(*pointerPodatki).msVarnostneRazdalje * (long)(*pointerPodatki).koefTemp /100;
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
				koef = koefVarnostneRazdalje(hitrost, dolzina,(int)msNove);
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
		a = tipkovnica.getKey();
	}
	lcd.cursor();
	lcd.clear();
}


void prikazRazdalje(void) {
	int idealVarnostna, varnostna;
	long msNove = (long)(*pointerPodatki).msVarnostneRazdalje * (long)(*pointerPodatki).koefTemp /100;
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
				idealVarnostna = idealnaVarnostna(Hitrost(),(int)msNove);
			}
			lcd.setCursor(8, 1);
			lcd.print(varnostna);
			lcd.print("m     ");
			lcd.setCursor(8, 3);
			lcd.print(idealVarnostna);
			lcd.print("m     ");
			time1 += (*pointerPodatki).refreshRate;
		}
		a = tipkovnica.getKey();
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
		a = tipkovnica.getKey();
	}
	lcd.cursor();
}

void prikazGraficni1(void) {
	char a = NULL;
	int zamikX = 0, zamikY = 0, koef;
	long msNove = (long)(*pointerPodatki).msVarnostneRazdalje * (long)(*pointerPodatki).koefTemp /100;
	lcd.clear();
	lcd.noCursor();
	unsigned long time1 = millis();
	while (a != NAZAJ) {
		if (millis() - time1 > (*pointerPodatki).refreshRate) {
			if(temperatura() > (*pointerPodatki).temp){
				koef = koefVarnostneRazdalje(Hitrost(), razdalja(), (*pointerPodatki).msVarnostneRazdalje);
			}
			else {
				koef = koefVarnostneRazdalje(Hitrost(), razdalja(), (int)msNove);
			}
			if( zamikX != razdeli(koef,0, 150,16,0)){ //Popravljeno utripanje avta (na novo nariše avto, samo če se spremeni pozicija)
				zamikX = razdeli(koef,0 ,150 ,16 ,0);
				prikaziAvto(zamikX, zamikY, avto);
			}
			time1 += (*pointerPodatki).refreshRate;
		}
		a = tipkovnica.getKey();
	}
	lcd.cursor();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void prikaziAvto(int zamikX,int zamikY, slikica* slika){
	lcd.setCursor(0,0);
	lcd.print("                   ");
	lcd.setCursor(0,1);
	lcd.print("                   ");
	lcd.setCursor(6,2);
	lcd.print(CrtaDesna);
	lcd.setCursor(6,3);
	lcd.print(CrtaDesna);
	for(int i = 0; i < 4; i++){
		lcd.setCursor(19,i);
		lcd.print(PolniBlok);
	}
	for(int i = 0; slika[i].x != -1; i++){
		lcd.setCursor(slika[i].x + zamikX, slika[i].y + zamikY);
		lcd.print(slika[i].slikica);
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
	lcd.print("Nastavitve ponast. ");
	lcd.setCursor(0, 1);
	lcd.print("za uporabnika ");
	lcd.print(stUporabnika);
	lcd.noCursor();
	delay(1000);
	lcd.cursor();
	lcd.clear();
}





void spremeniPodatek(char tekst[10],char enota[4],int *podatek, int maks, int min){
	/*
	 * Funkcija omogoči spreminjane podatka in samodejno zapiše vse podatke
	 * o uporabniku na EEPROM
	 */
	char a = NULL;
	int celota = 0, i ;
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Vrednost ");
	lcd.print(tekst);
	lcd.print(": ");
	lcd.setCursor(0, 1);
	lcd.print(*podatek);
	lcd.print(enota);
	lcd.setCursor(0,2);
	lcd.print("Uporabnik: ");
	lcd.print((unsigned int)stUporabnika +1);
	lcd.setCursor(0,3);
	lcd.print("Spremeni vrednost: D");
	while (a != NAZAJ) {
		a = tipkovnica.getKey();
		if(a == 'D'){
			a = NULL;
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
			lcd.print("Za zakljucit: D");
			lcd.setCursor(0,3);
			for(i = 0;a != 'D'&& i < 5;){
				a = tipkovnica.getKey();
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

