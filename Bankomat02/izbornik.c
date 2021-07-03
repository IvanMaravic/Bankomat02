#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include "functions.h"


int izbornik(const char* const ime_Datoteke) {
	RACUN* poljeRacuna = NULL;
	poljeRacuna = ucitavanjeRacuna(poljeRacuna);
	printf("Odaberite jednu od ponudenih opcija:\n");
	printf("\t\t\tOpcija 1: Dodavanje racuna\n");
	printf("\t\t\tOpcija 2: Provjerite stanje racuna\n");
	printf("\t\t\tOpcija 3: Podignite novac\n");
	printf("\t\t\tOpcija 4: Stavite novac na racun\n");
	printf("\t\t\tOpcija 5: Kraj\n");
	printf("======================================\
======================================\n");
	int uvijet = 0;
	scanf("%d", &uvijet);
	switch (uvijet) {
	case 1:
		dodavanjeRacuna(ime_Datoteke, poljeRacuna);
		if (poljeRacuna != NULL) {
		}
		poljeRacuna = (RACUN*)ucitajRacun(ime_Datoteke);
		if (poljeRacuna == NULL) {
			exit(EXIT_FAILURE);
		}
		break;
	case 2:
		stanjeRacuna(poljeRacuna);
		break;
	case 3:
		podizanjeNovca(poljeRacuna, ime_Datoteke);
		break;
	case 4:
		spremanjeNovca(poljeRacuna, ime_Datoteke);
		break;
	case 5:
		uvijet = izlazIzPrograma(poljeRacuna);
		break;
	default:
		uvijet = 10;
	}
	/*upisPoljaUDatoteku(poljeRacuna);*/
	return uvijet;
}