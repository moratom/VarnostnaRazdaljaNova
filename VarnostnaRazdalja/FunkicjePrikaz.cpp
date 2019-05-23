/*
 * FunkicjePrikaz.cpp
 *
 *  Created on: May 23, 2019
 *      Author: matevz
 */
#include"Varnostna.h"
//AVTO//
///////////////////////////////////////////////////////////////////////////
byte kolo[8] = { 0x0E, 0x0E, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, };

byte prednjiDel[8] = { 0x0, 0x0, 0x0, 0x0, 0x1, 0x1F, 0x1F, 0x1F, };

byte srednjiDel[8] = { 0x0, 0x0, 0x0, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, };

byte zadnjiDel[8] { 0x0, 0x0, 0x0, 0x0, 0x10, 0x1F, 0x1F, 0x1F, };

byte crtaDesna[8] = {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};

byte polniBlok[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};

byte *znaki[] = {kolo, prednjiDel, srednjiDel, zadnjiDel, crtaDesna, polniBlok};

void izdelajZnake(){
	for(int i = 1; i < 7;i++){
		lcd.createChar(i, znaki[i-1]);
	}
}
char Kolo = 1, PrednjiDel = 2, SrednjiDel = 3, ZadnjiDel = 4, CrtaDesna = 5, PolniBlok = 6; //že narejeni novi charracterji

slikica avto[] = {
		{0,1,Kolo},
		{2,1,Kolo},
		{0,0, PrednjiDel},
		{1,0, SrednjiDel},
		{2,0, ZadnjiDel},
		{-1,-1, 0}
};





int prikazujMeni(char **meniPointer, int velikostMenija) {
	/*
	 * Funkcija prikazuje meni, ki ji ga podamo, številko izbire, kjer uporabnik stisne '5' oz izbere opcijo menija
	 * če uporabnik pritisne tipo za se vrnit, funkcija vrne -1
	 */
	char a = NULL;
	int zacetek = 0;
	lcd.clear();
	lcd.cursor();
	prikaziMeni(0, velikostMenija, meniPointer);
	while (a != '5') {
		a = tipkovnica.getKey();
		if (a == NAZAJ)
			return -1;
		if (a == '2' ) {
			if(zacetek > 0){
				zacetek -= 1;
				prikaziMeni(zacetek, velikostMenija, meniPointer);
			}
			else{ // Če je na vrhu gre nazaj na dno.
				zacetek = velikostMenija - 1;
				prikaziMeni(zacetek, velikostMenija, meniPointer);
			}
		}
		if (a == '8') {
			if (zacetek < velikostMenija - 1) {
				zacetek += 1;
			} else { //Če je na dnu gre nazaj na vrh
				zacetek = 0;
			}
			prikaziMeni(zacetek, velikostMenija, meniPointer);
		}
	}
	return zacetek;
}

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

void prikazOsnovni(podatki* pointerPodatki) { //najbolj osnoven prikaz (pokaže meritve vseh senzorjev na mikrokontrolerju)
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
		standardnoOpozaranjanje(pointerPodatki);
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


void prikazRazdalje(podatki* pointerPodatki) {
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
		standardnoOpozaranjanje(pointerPodatki);
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

void prikazHitrost(podatki* pointerPodatki) {
	char a = NULL;
	lcd.clear();
	lcd.noCursor();
	lcd.print("Hitrost:");
	unsigned long time1 = millis();
	while (a != NAZAJ) {
		standardnoOpozaranjanje(pointerPodatki);
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

void prikazGraficni1(podatki* pointerPodatki) {
	char a = NULL;
	int zamikX = 0, zamikY = 0, koef;
	long msNove = (long)(*pointerPodatki).msVarnostneRazdalje * (long)(*pointerPodatki).koefTemp /100;
	lcd.clear();
	lcd.noCursor();
	unsigned long time1 = millis();
	while (a != NAZAJ) {
		standardnoOpozaranjanje(pointerPodatki);
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

void spremeniPodatek(char tekst[10],char enota[4],int *podatek, int maks, int min, byte stUporabnika, podatki* pointerPodatki){
	/*
	 * Funkcija omogoči spreminjane podatka in samodejno zapiše vse podatke
	 * o uporabniku na EEPROM
	 */
	char a = NULL;
	int celota = 0, i ;
	lcd.noCursor();
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




