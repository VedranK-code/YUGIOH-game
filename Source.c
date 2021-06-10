#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "header.h"





int main(void) {
	srand((unsigned)time(NULL));
	int m[5];
	int* c;
	c = m;
	KARTE* karte;
	karte = unosm(30);
	UnosKarti(karte, 30);
	MainMenu(karte);
	//odabir();
	c = Ruka(karte, c);
	polje(karte, igraj(karte, c),c);



	return 0;
}