#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Varnostna.h"
#define pinEcho 2
#define pinTrig 3
#define pinTemp A1
#define velikostGlavniMeni 7
#define velikostNastavitveSenzorja 6
#define ledPin 10

int velikostGM = velikostGlavniMeni;
int velikostNS = velikostNastavitveSenzorja;


LiquidCrystal_I2C lcd(0x3F, 20, 4);



char *glavniMeni[] =
{
"Prikaz             ",
"Nastavitve senzor  ",
"Nastavitve prikaza ",
"Splosne nastavitve ",
"Ponastavi nastavit ",
"Test               ",
"Razsirljivost      "
};

char *nastavitveSenzorja[] =
{
"Preklinjaj         ",
"Nastavitve senzoB  ",
"Nastavitve prikazB ",
"Splosne nastavitvB ",
"Ponastavi nastavit ",
"Test               "
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A15, A14, A13, A12}; //connect to the row pinouts of the keypad // @suppress("Symbol is not resolved")
byte colPins[COLS] = {A11, A10, A9, A8}; //connect to the column pinouts of the keypad // @suppress("Symbol is not resolved")

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {
  init();
  Serial.begin(9600);
  pinMode(pinTemp, INPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(ledPin,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.cursor();
  prikaziMeni(0,velikostGM, glavniMeni);
  void (*prikazPointer)() = prikaz1;
  int *velikostPointer = &velikostGM;
  char **meniPointer = glavniMeni;


 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////77
  while(1){
    int zacetek = prikazujMeni(meniPointer, *velikostPointer);
    if(meniPointer == glavniMeni){
		switch (zacetek){
			case 0: prikazPointer(); break;
			case 1: meniPointer = nastavitveSenzorja; velikostPointer = &velikostNS;
			case 2: izbrisiToFunkcijo();
		}
    }
    else if(meniPointer == nastavitveSenzorja){
    	switch (zacetek){
    	 	case -1: meniPointer = glavniMeni; velikostPointer = &velikostGM;break;
     		case 0: prikazPointer = prikaz2; prikazSpremenjen(); break;
    	}
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////7
int prikazujMeni(char **meniPointer, int velikostMenija){
	char a = NULL;
	int zacetek = 0;
	prikaziMeni(0, velikostMenija, meniPointer);
	while(a != '5'){
	    a = customKeypad.getKey();
	    if(a == '1') return -1;
	    if(a == '2' && zacetek > 0){
	      zacetek -= 1;
	      prikaziMeni(zacetek, velikostMenija, meniPointer);
	    }
	    if(a == '8'){
	      if(zacetek < velikostMenija -1){
	        zacetek += 1;
	      }
	      else {
	        zacetek = 0;
	      }
	      prikaziMeni(zacetek, velikostMenija, meniPointer);
	    }
	}
	return zacetek;
}


void prikaz1(void){
	static bool dolz = 0, temperat = 0;
	static unsigned long int time1 = millis();
	float temp, dolzina;
	lcd.clear();
	lcd.noCursor();
	char a = NULL; //inicializirano da nebi slučajno takoj skočlo vn iz prikaza

	while(a != '1'){
		if(millis() - time1 > 500){

		  temp = temperatura();
		  dolzina = razdalja();
		  lcd.setCursor(0,0);
		  lcd.print("Temperatura: ");
		  lcd.print(temp);
		  lcd.print(" C  ");
		  lcd.setCursor(0,1);
		  lcd.print("Razdalja: ");
		  lcd.print(dolzina);
		  lcd.print(" cm      ");

		  time1 += 500;
		}
		a = customKeypad.getKey();
	}
	lcd.cursor();
	lcd.clear();
}


void prikaziMeni(int zacetekPrikaza, int velikostMenija, char **meni){
  if(zacetekPrikaza <= 3){
    for(int i = 0, k = 0; i <= 3 && i < velikostMenija; i++, k++){
      lcd.setCursor(0,k);
      lcd.print(meni[i]);
      lcd.setCursor(19,zacetekPrikaza);
    }
  }
  else{
    for(int i = zacetekPrikaza - 3, k = 0; i < velikostMenija && i <= zacetekPrikaza; i++, k++){
      lcd.setCursor(0,k);
      lcd.print(meni[i]);
      lcd.setCursor(19,3);
    }
  }
}


void prikazSpremenjen(void){
	lcd.clear();
	lcd.setCursor(0,1);
	lcd.print("Prikaz");
	lcd.setCursor(0,2);
	lcd.print("Spremenjen");
	delay(1000);
	lcd.clear();
}


void prikaz2(void){
	char a = NULL;
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("POZDRAVLJENA ZVEZDA");
	while(a != '1') a = customKeypad.getKey();
}

void izbrisiToFunkcijo(void){
	int stevilo = 0;
	char a;
	int celota = 0;
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Kalkulator");
	lcd.setCursor(0,1);
	while(1){
		a = customKeypad.getKey();
		if(a >= '0' && a <= '9'){
			a -= '0';
			celota *= 10;
			celota += (int)a;
			lcd.print((int)a);
		}
		else if(a == '*'){
			celota += 50;
			lcd.print("                  ");
			lcd.print(celota);
		}

	}
}


