#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"
#include <ctype.h>


void kreiranjeDatoteke(const char* const ime_Datoteke) {
	int brojRacuna = 0;
	if (ime_Datoteke != NULL) {
		brojRacuna = ucitavanjeBrojRacuna();
	}
	FILE* pF = fopen(ime_Datoteke, "ab+");
	if (pF == NULL) {
		perror("Kreiranje datoteke studenti.bin");
		exit(EXIT_FAILURE);
	}
	fwrite(&brojRacuna, sizeof(int), 1, pF);
	fclose(pF);
}


int ucitavanjeBrojRacuna() {
	int brRacuna = 0;
	FILE* datoteka = NULL;
	char* ime_dat = "racuni.bin";
	datoteka = fopen(ime_dat, "rb");
	if (datoteka != NULL) {
		rewind(datoteka);
		fread(&brRacuna, sizeof(int), 1, datoteka);
		fclose(datoteka);
	}
	else {
		brRacuna = 0;
		//printf("Nemoguce je saznati koliki je racuna u datoteci!\n");
		//printf("\nKraj programa\n");
		//exit(EXIT_FAILURE);
	}
	return brRacuna;
}


RACUN* ucitavanjeRacuna(RACUN* racuni) {
	FILE* datoteka = NULL;
	char* ime_dat = "racuni.bin";
	int brojRacuna;
	brojRacuna = ucitavanjeBrojRacuna();
	racuni = (RACUN*)calloc(brojRacuna, sizeof(RACUN));
	datoteka = fopen(ime_dat, "rb");
	if (racuni != NULL) {
		if (datoteka == NULL) {
			printf("Neuspjesno otvaranje datoteke za citanje\n");
		}
		else {
			rewind(datoteka);
			fseek(datoteka, 4, SEEK_SET);
			fread(racuni, sizeof(RACUN), brojRacuna, datoteka);
			fclose(datoteka);
		}
	}
	else {
		fclose(datoteka);
		printf("Neuspjesno otvaranje");
	}
	return racuni;
}

void dodavanjeRacuna(const char* const ime_Datoteke, RACUN* const poljeRacuna) {
	int brojRacuna;
	brojRacuna = ucitavanjeBrojRacuna();
	srand((unsigned)time(NULL));
	int uspjesno = 0;
	FILE* pF = fopen(ime_Datoteke, "rb+");
	if (pF == NULL) {
		perror("Dodavanje racuna u datoteke racuni.bin");
		exit(EXIT_FAILURE);
	}
	fread(&brojRacuna, sizeof(int), 1, pF);
	printf("brojRacuna: %d\n", brojRacuna);
	RACUN temp = { 0 };
	getchar();
	printf("Unesite ime!\n");
	scanf("%19[^\n]", temp.ime);
	printf("Unesite prezime!\n");
	getchar();
	scanf("%19[^\n]", temp.prezime);
	int i;
	int PIN;
	/*PIN = 1000 + (float)rand() / RAND_MAX * (10000 - 1000);*/
	if (pF == NULL) PIN = 1000 + (float)rand() / RAND_MAX * (10000 - 1000);
	else {
		do {
			PIN = 1000 + (float)rand() / RAND_MAX * (10000 - 1000);
			for (i = 0; i < brojRacuna; i++)
			{
				if (PIN == (poljeRacuna + i)->pin) {
					PIN = 0;
				}
			}
		} while (PIN == 0);
	}
	temp.pin = PIN;
	printf("Unesite stanje racuna:\n");
	scanf("%f", &temp.stanje);

	printf("\n");
	fseek(pF, sizeof(RACUN) * brojRacuna, SEEK_CUR);
	brojRacuna++;
	temp.broj = brojRacuna;
	fwrite(&temp, sizeof(RACUN), 1, pF);
	rewind(pF);

	fwrite(&brojRacuna, sizeof(int), 1, pF);
	fclose(pF);
	printf("Vas PIN %d\n", PIN);
}

RACUN* ucitajRacun(const char* const ime_Datoteke) {
	int brojRacuna;
	brojRacuna = ucitavanjeBrojRacuna();
	FILE* pF = fopen(ime_Datoteke, "rb");
	if (pF == NULL) {
		perror("Ucitavanje racuna iz datoteke racuni.bin");
		return NULL;
		//exit(EXIT_FAILURE);
	}
	printf("brojRacuna: %d\n", brojRacuna);
	RACUN* poljeRacuna = (RACUN*)calloc(1, sizeof(RACUN));
	if (poljeRacuna == NULL) {
		perror("Zauzimanje memorije za racune");
		return NULL;
		//exit(EXIT_FAILURE);
	}
	fread(poljeRacuna, sizeof(RACUN), brojRacuna, pF);
	return poljeRacuna;
}

void* stanjeRacuna(RACUN* poljeRacuna) {
	int brojRacuna;
	brojRacuna = ucitavanjeBrojRacuna();
	if (poljeRacuna == NULL) {
		printf("Polje racuna je prazno!\n");
		return NULL;
	}
	int i;
	int trazeniPin;
	printf("Unesite PIN.\n");
	scanf("%d", &trazeniPin);
	for (i = 0; i < brojRacuna; i++)
	{
		if (trazeniPin == (poljeRacuna + i)->pin) {
			printf("Trenutno stanje racuna iznosi: %.2f \n", (poljeRacuna + i)->stanje);
			return NULL;
		}
	}
	printf("Vas PIN ne odgovara niti jednom racunu.\nPokusajte ponovno.\n");
	return NULL;
}

void* podizanjeNovca(RACUN* const poljeRacuna, const char* ime_Datoteke) {
	int brojRacuna;
	brojRacuna = ucitavanjeBrojRacuna();
	if (poljeRacuna == NULL) {
		printf("Polje racuna je prazno!\n");
		return NULL;
	}
	int i;
	int nekiIznos;
	int trazeniPin;
	printf("Unesite PIN.\n");
	scanf("%d", &trazeniPin);
	for (i = 0; i < brojRacuna; i++)
	{
		if (trazeniPin == (poljeRacuna + i)->pin) {
			printf("Unesite iznos koji zelite podici:\t");
			printf("\n100\t\t200\n400\t\t600\n800\t\t1000\nU slucaju da zelite podici neki drugi iznos upisite 1\n");
			scanf("%d", &nekiIznos);
			if (nekiIznos == 100) {
				if ((poljeRacuna + i)->stanje < 100) {
					printf("Svota na racunu nije dovoljna.");
					break;
				}
				(poljeRacuna + i)->stanje -= nekiIznos;
				printf("Transakcija izvedena.\n");
				FILE* pF = fopen(ime_Datoteke, "rb+");
				if (pF == NULL) {
					perror("Dodavanje racuna u datoteke racuni.bin");
					exit(EXIT_FAILURE);
				}
				rewind(pF);
				fseek(pF, 4, SEEK_SET);
				fseek(pF, sizeof(RACUN) * (i - 1), SEEK_SET);
				fwrite((poljeRacuna + i), sizeof(RACUN), 1, pF);
				fclose(pF);
			}
			else if (nekiIznos == 200) {
				if ((poljeRacuna + i)->stanje < 200) {
					printf("Svota na racunu nije dovoljna.");
					break;
				}
				(poljeRacuna + i)->stanje -= nekiIznos;
				printf("Transakcija izvedena.\n");
				FILE* pF = fopen(ime_Datoteke, "rb+");
				if (pF == NULL) {
					perror("Dodavanje racuna u datoteke racuni.bin");
					exit(EXIT_FAILURE);
				}
				rewind(pF);
				fseek(pF, 4, SEEK_SET);
				fseek(pF, sizeof(RACUN) * (i - 1), SEEK_SET);
				fwrite((poljeRacuna + i), sizeof(RACUN), 1, pF);
				fclose(pF);
			}
			else if (nekiIznos == 400) {
				if ((poljeRacuna + i)->stanje < 400) {
					printf("Svota na racunu nije dovoljna.");
					break;
				}
				(poljeRacuna + i)->stanje -= nekiIznos;
				printf("Transakcija izvedena.\n");
				FILE* pF = fopen(ime_Datoteke, "rb+");
				if (pF == NULL) {
					perror("Dodavanje racuna u datoteke racuni.bin");
					exit(EXIT_FAILURE);
				}
				rewind(pF);
				fseek(pF, 4, SEEK_SET);
				fseek(pF, sizeof(RACUN) * (i - 1), SEEK_SET);
				fwrite((poljeRacuna + i), sizeof(RACUN), 1, pF);
				fclose(pF);
			}
			else if (nekiIznos == 600) {
				if ((poljeRacuna + i)->stanje < 600) {
					printf("Svota na racunu nije dovoljna.");
					break;
				}
				(poljeRacuna + i)->stanje -= nekiIznos;
				printf("Transakcija izvedena.\n");
				FILE* pF = fopen(ime_Datoteke, "rb+");
				if (pF == NULL) {
					perror("Dodavanje racuna u datoteke racuni.bin");
					exit(EXIT_FAILURE);
				}
				rewind(pF);
				fseek(pF, 4, SEEK_SET);
				fseek(pF, sizeof(RACUN) * (i - 1), SEEK_SET);
				fwrite((poljeRacuna + i), sizeof(RACUN), 1, pF);
				fclose(pF);
			}
			else if (!nekiIznos == 800) {
				if ((poljeRacuna + i)->stanje < 800) {
					printf("Svota na racunu nije dovoljna.");
					break;
				}
				(poljeRacuna + i)->stanje -= nekiIznos;
				printf("Transakcija izvedena.\n");
				FILE* pF = fopen(ime_Datoteke, "rb+");
				if (pF == NULL) {
					perror("Dodavanje racuna u datoteke racuni.bin");
					exit(EXIT_FAILURE);
				}
				rewind(pF);
				fseek(pF, 4, SEEK_SET);
				fseek(pF, sizeof(RACUN) * (i - 1), SEEK_SET);
				fwrite((poljeRacuna + i), sizeof(RACUN), 1, pF);
				fclose(pF);
			}
			else if (nekiIznos == 1000) {
				if ((poljeRacuna + i)->stanje < 1000) {
					printf("Svota na racunu nije dovoljna.");
					break;
				}
				(poljeRacuna + i)->stanje -= nekiIznos;
				printf("Transakcija izvedena.\n");
				FILE* pF = fopen(ime_Datoteke, "rb+");
				if (pF == NULL) {
					perror("Dodavanje racuna u datoteke racuni.bin");
					exit(EXIT_FAILURE);
				}
				rewind(pF);
				fseek(pF, 4, SEEK_SET);
				fseek(pF, sizeof(RACUN) * (i - 1), SEEK_SET);
				fwrite((poljeRacuna + i), sizeof(RACUN), 1, pF);
				fclose(pF);
			}
			else if (nekiIznos == 1) {
				do {
					printf("Unesite iznos.\nIznos moze biti minimalno 50 kuna.\n");
					scanf("%d", &nekiIznos);
					if (nekiIznos % 50 != 0) {
						printf("Iznos mora biti djeljiv sa 50.\n");
						break;
					}
					if ((poljeRacuna + i)->stanje < nekiIznos) {
						printf("Svota na racunu nije dovoljna.\n");
						break;
					}
				} while (nekiIznos % 50 != 0);
				(poljeRacuna + i)->stanje -= (float)nekiIznos;
				printf("Transakcija izvedena.\n");
				FILE* pF = fopen(ime_Datoteke, "rb+");
				if (pF == NULL) {
					perror("Dodavanje racuna u datoteke racuni.bin");
					exit(EXIT_FAILURE);
				}
				rewind(pF);
				fseek(pF, 4, SEEK_SET);
				fseek(pF, sizeof(RACUN) * (i - 1), SEEK_SET);
				fwrite((poljeRacuna + i), sizeof(RACUN), 1, pF);
				fclose(pF);

			}
		}
	}
	return NULL;
}

void* spremanjeNovca(RACUN* const poljeRacuna, const char* ime_Datoteke) {
	int brojRacuna;
	brojRacuna = ucitavanjeBrojRacuna();
	if (poljeRacuna == NULL) {
		printf("Polje racuna je prazno!\n");
		return NULL;
	}
	int i;
	int nekiIznos;
	int trazeniPin;
	printf("Unesite PIN.\n");
	scanf("%d", &trazeniPin);
	for (i = 0; i < brojRacuna; i++)
	{
		if (trazeniPin == (poljeRacuna + i)->pin) {
			printf("Unesite iznos novca koji zelite spremiti:");
			scanf("%d", &nekiIznos);
			if (nekiIznos % 50 != 0) {
				printf("Iznos mora biti djeljiv s 50.");
			}
			else {
				(poljeRacuna + i)->stanje += (float)nekiIznos;
				printf("Novac je spremljen na vas racun.\n");
				FILE* pF = fopen(ime_Datoteke, "rb+");
				if (pF == NULL) {
					perror("Podizanje novca u datoteke racuni.bin");
					exit(EXIT_FAILURE);
				}
				rewind(pF);
				fseek(pF, 4, SEEK_SET);
				fseek(pF, sizeof(RACUN) * (i - 1), SEEK_SET);
				fwrite((poljeRacuna + i), sizeof(RACUN), 1, pF);
				fclose(pF);
				return NULL;
			}

		}

	}
	printf("Pogresan PIN");
	return NULL;
}




int izlazIzPrograma(RACUN* poljeRacuna) {
	printf("Zatvaranje programa\tDa?\tNe?\n");
	char potvrda[3] = { '\0' };
	scanf("%2s", potvrda);
	if (strcmp("da", tolower(potvrda))) {
		return 1;
		free(poljeRacuna);

	}
	return 0;
}