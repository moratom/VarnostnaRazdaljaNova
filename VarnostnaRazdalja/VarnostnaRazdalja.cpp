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
"Tisa               ",
"Nastavitve senzoB  ",
"Nastavitve prikazB ",
"Splosne nastavitvB ",
"Ponastavi nastavit ",
"Test               "
};





const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A15, A14, A13, A12}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A11, A10, A9, A8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


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






int main() {
  init();
  Serial.begin(9600);
  pinMode(pinTemp, INPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.cursor();
  prikaziMeni(0,velikostGM, glavniMeni);
  int *velikostPointer = &velikostGM;
  char **meniPointer = glavniMeni;

  while(1){
    static int zacetek = 0;

    char a = customKeypad.getKey();

    if(zacetek == 0 && a == '5'){
      static bool dolz = 0, temperat = 0;
      static unsigned long int time1 = 0, time2 = 0;
      float temp, dolzina;
      lcd.clear();
      lcd.noCursor();

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
    if(a == '1') {
      prikaziMeni(0, *velikostPointer, meniPointer);
    }

    if(a == '2' && zacetek > 0){
      zacetek -= 1;
      prikaziMeni(zacetek, *velikostPointer, meniPointer);
    }
    if(a == '8'){
      if(zacetek < *velikostPointer -1){
        zacetek += 1;
      }
      else {
        zacetek = 0;
      }
      prikaziMeni(zacetek, *velikostPointer, meniPointer);
    }
    if(a == 'A'){
      meniPointer = nastavitveSenzorja;
      velikostPointer = &velikostNS;
      zacetek = 0;
      prikaziMeni(zacetek, *velikostPointer, meniPointer);
    }
  }
}
