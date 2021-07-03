#pragma once
#ifndef functions_h
#define functions_h
#include "Header.h"
int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodavanjeRacuna(const char* const, RACUN* const);
RACUN* ucitajRacun(const char* const);
void* stanjeRacuna(RACUN* const);
void* podizanjeNovca(RACUN* const, const char*);
void* spremanjeNovca(RACUN* const, const char*);
int izlazIzPrograma(RACUN*);
RACUN* ucitavanjeRacuna(RACUN* racuni);
int ucitavanjeBrojRacuna();



#endif //functions_h
