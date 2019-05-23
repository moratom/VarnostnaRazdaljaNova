/*
 * FunkicjePrikaz.cpp
 *
 *  Created on: May 23, 2019
 *      Author: matevz
 */
#include"Varnostna.h"

int prikazujMeni(char **meniPointer, int velikostMenija) {
	/*
	 * Funkcija prikazuje meni, ki ji ga podamo, številko izbire, kjer uporabnik stisne '5' oz izbere opcijo menija
	 * če uporabnik pritisne tipo za se vrnit, funkcija vrne -1
	 */
	char a = NULL;
	int zacetek = 0;
	lcd.clear();
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




