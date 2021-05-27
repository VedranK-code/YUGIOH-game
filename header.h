#ifndef HEADER_H
#define HEADER_H

typedef struct karta {
	char ime[40];
	int zvijezdice;
	int napad;
	int obrana;
	int ind;
}KARTE;


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

KARTE* unosm(int n);
void UnosKarti(KARTE* const karte, int m);
int brkrt(int n);
int Ruka(KARTE* const karte, int* m);
int igraj(KARTE* const karte, int* p);
void polje(KARTE* const karte, int m1, int* p);
int Game_Over(int player, int COM);
#endif
