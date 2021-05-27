#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "header.h"





int main(void) {
	srand((unsigned)time(NULL));
	int n = 30, m[5];
	int* c;
	c = m;
	KARTE* karte;
	karte = unosm(n);
	UnosKarti(karte, 30);
	c = Ruka(karte, c);
	polje(karte, igraj(karte, c),c);


	return 0;
}