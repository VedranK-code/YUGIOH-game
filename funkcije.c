#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "header.h"

int player = 8000;
int COM = 8000;
int brojpoteza = 1;


KARTE* unosm(int n) {
	KARTE* karte;
	karte = (KARTE*)calloc(n, sizeof(KARTE));
	if (karte == NULL) {
		return NULL;
	}
	return karte;
}



void UnosKarti(KARTE* const karta, int m) {

	FILE* fp = NULL;
	fp = fopen("Karte.txt", "r");
	if (fp == NULL) {
		printf("Špil ne postoji, molimo unesite svoj špil od 30 karata u mapu programa.\n");
	}
	else {
		for (int i = 0; i < m; i++)
		{
			fscanf(fp, "%s %d %d\n", (karta + i)->ime, &(karta + i)->zvijezdice, &(karta + i)->napad); (karta + i)->ind = i;
		}
	}
}

void DuelLog(int player, int COM, int i) {
	FILE* pf = NULL;
	pf = fopen("log.txt", "a+");
	if (pf == NULL) {
		pf = fopen("log.txt", "w");
		perror("Kreiranje datoteke log.txt");
		fclose(pf);
	}
	else {
		fopen("log.txt", "w+");
		fprintf(pf, "%d. potez: Igrac: %d, Racunalo: %d\t\n", i, player, COM);

	}
	
}


int brkrt(int n){
	int k;
	k = rand() % n;
	return k;

}

int Ruka(KARTE* const karte, int* m) {
	int m1;
	int d;
	printf(CYN"Vasa ruka:\n"RESET);
	for (int i = 0; i < 5; i++) {
		m[i] = brkrt(30); d = m[i];
		for (int j = 0; j < 5; j++) {
			if (m[j] == d) {
				m[i] = brkrt(30);
			}	
		}
		printf(YEL"%35s, %5d*, ATK: %4d, ind: %1d\n"RESET, karte[m[i]].ime,
			karte[m[i]].zvijezdice, karte[m[i]].napad, karte[m[i]].ind);
	}
	return m;
}
int igraj(KARTE* const karte, int* p) {

	int m,n=0;
	printf(GRN"\nIgrajte kartu:\n");
	scanf("%d"RESET, &m);
	for (int i = 0; i < 5; i++) {
		if (m == karte[p[i]].ind) { return m; n = 1; }
		/*if (m == karte[p[i]].ind) { return m; }*/
	}
	if (n == 0) { igraj(karte, p); }//cheat deactivated
}

void MainMenu(KARTE* const karte) {
	system("CLS");
	printf("\n\n\n\n\n\n\n\n\n");
	printf(YEL"\n\t\t\t\t\t\t   Yu-Gi-Oh\n"RESET);
	printf(BLU"\n\t\t\t\t\t\t1. Play Game\n"RESET);
	printf(CYN"\n\t\t\t\t\t\t2. Help\n"RESET);
	printf(RED"\n\t\t\t\t\t\t3. Exit Game\n"RESET);
	printf("\n\n\n\n\n\n\n\n\n\n");
	odabir(karte);
}

void odabir(KARTE* const karte) {
	int a;
	scanf("%d", &a);
	switch (a) {
	case 1:
		system("pause");
		system("cls");
		break;

	case 2:
		system("cls");
		selectionSort(karte,30);
		help(karte, 30);
		system("pause");
		system("cls");
		UnosKarti(karte, 30);
		MainMenu(karte);
	
		break;

	case 3:
		exit(0);
		break;

	default:
		odabir(karte);
	}

}


void selectionSort(KARTE* const karte, const int n) {
	struct karta temp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n-1-i); j++)
		{
			if (karte[j].napad < karte[j + 1].napad) {
				temp = karte[j];
				karte[j] = karte[j + 1];
				karte[j + 1] = temp;
			}
		}
	}
}
void help(KARTE* const karte,int n) {
	for(int i=0;i<n;i++){
		printf(YEL"%35s, %5d*, ATK: %4d, ind: %1d\n"RESET, karte[i].ime,
					karte[i].zvijezdice, karte[i].napad, karte[i].ind);}
}

int polje(KARTE* const karte, int m1, int* p) {

	int a = 0;
	int m2 = suparnicka_ruka(karte);
	if (m1 == 50) {
		printf("\nMoje polje:\n");
	}
	else {
		int i = 0;
		printf(BLU "\nMoje polje: %20s|%4d|\n"RESET, karte[m1].ime, karte[m1].napad);
	}
	printf(RED"\nSuparnickovo polje: %20s|%4d|\n"RESET, karte[m2].ime, karte[m2].napad);

	LpCalc(m1, m2, karte);

	DuelLog(player, COM, brojpoteza);
	brojpoteza++;
	while (player > 0 && COM > 0) {
		system("pause");
		system("CLS");
		Ruka(karte, p);
		polje(karte, igraj(karte, p), p);
	} 
	if (player <= 0 || COM <= 0 && a == 0) {
		Game_Over(player, COM);
		a = 1;
	}
	PlayAgain();
	return 0;
}

LpCalc(int m1, int m2, KARTE* const karte){
	int razlika;
	if (karte[m1].napad > karte[m2].napad) {
		razlika = karte[m1].napad - karte[m2].napad;
		COM -= razlika;
		if (COM <= 0) { COM = 0; }
	}
	if (karte[m2].napad > karte[m1].napad) {
		razlika = karte[m2].napad - karte[m1].napad;
		if (karte[m1].ind >= 24) { razlika = 0; }
		player -= razlika;
		if (player <= 0) { player = 0; }
	}
	printf(CYN"\nZivotni poeni ||Player:%4d|		|COM:%4d||\n"RESET, player, COM);
}

int suparnicka_ruka(KARTE* const karte) {
	int m[5],d;
	int najveci=0, m2;
	for (int i = 0; i < 5; i++) {
		m[i] = brkrt(30);
		d = m[i];
		for (int j = 0; j < 5; j++) {
			if (m[j] == d) {
				m[i] = brkrt(30);
			}
		}
	}
	for (int l = 0; l < 5; l++) {
		if (karte[m[l]].napad > najveci) {
			m2 = karte[m[l]].ind;
			najveci = karte[m[l]].napad;
		}
	}
	return m2;
}
int Game_Over(int player, int COM) {
	int a=0;
	if (player<=0 && a==0){
		system("CLS");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		printf(YEL"\n\t\t\t\t\t\t\tGAME OVER"RESET);
		printf(RED"\n\t\t\t\t\t\t\tYou louse\n"RESET);
		printf("\n\n\n\n\n\n\n\n\n\n");
		a = 1;
		system("pause");
	}else if(COM <= 0 && a == 0) {
		system("CLS");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		printf(YEL"\n\t\t\t\t\t\t\tGAME OVER"RESET);
		printf(CYN"\n\t\t\t\t\t\t\tYou Win\n"RESET);
		printf("\n\n\n\n\n\n\n\n\n\n");
		a = 1;
		system("pause");
	}
	return 0;
}

int PlayAgain() {
	int restart;
	printf("\nPlay again?");
	printf("\n1. Yes\n2. No\n");
	do { scanf("%d", &restart); } while (restart < 1 || restart > 2);
	if (restart == 1) {
		player = 8000;
		COM = 8000;
	}
	if (restart == 2) {
		exit(0);
	}
	return 0;
}