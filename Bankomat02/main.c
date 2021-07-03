#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "Header.h"
#include "functions.h"

int main() {
	char ime_Datoteke[] = { "racuni.bin" };
	kreiranjeDatoteke(ime_Datoteke);
	RACUN* racuni = NULL;
	racuni = ucitavanjeRacuna(racuni);
	int a;
	a = ucitavanjeBrojRacuna();
	for (int i = 0; i < a; i++) {
		printf("%d\n", racuni[i].broj);
		printf("%d\n", racuni[i].pin);
		printf("%s\n", racuni[i].ime);
		printf("%s\n", racuni[i].prezime);
		printf("%.2f\n", racuni[i].stanje);
	}


	int uvijet = 1;
	while (uvijet) {
		uvijet = izbornik(ime_Datoteke);
	}
	free(racuni);
	printf("Zavrsetak programa!\n");
	return 0;
}