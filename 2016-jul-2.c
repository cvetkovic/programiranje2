/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 2 - jul 2016. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct Autor
{
	char ime[MAX];
	char prezime[MAX];
	float bodova;
	struct Autor *sledeci;
} Autor;

int proveriDaLiPostoji(Autor *lista, char ime[], char prezime[])
{
	if (lista == NULL)
		return 0;

	while (lista)
	{
		if (strcmp(lista->ime, ime) == 0 && strcmp(lista->prezime, prezime) == 0)
		{
			return 1;
		}

		lista = lista->sledeci;
	}

	return 0;
}

void oslobodiMemoriju(Autor *lista)
{
	while (lista)
	{
		Autor *t = lista->sledeci;
		free(lista);
		lista = t;
	}
}

void main()
{
	FILE *radovi = fopen("radovi.txt", "r");

	if (radovi == NULL)
		return;

	char c = 0;

	int brojAutora=-1;
	char ime[MAX], prezime[MAX];

	Autor *lista = NULL;

	while (fscanf(radovi, "%d", &brojAutora) != EOF)
	{
		for (int i = 0;i < brojAutora;i++)
		{
			fscanf(radovi,"%s %s", &ime, &prezime);

			if (proveriDaLiPostoji(lista, ime, prezime))
			{
				// azuriranje
				Autor *kopija = lista;

				while (kopija)
				{
					if (strcmp(kopija->ime, ime) == 0 && strcmp(kopija->prezime, prezime) == 0)
					{
						kopija->bodova += 2 / (double)brojAutora;
						break;
					}

					kopija = kopija->sledeci;
				}
			}
			else
			{
				// dodavanje
				Autor *t = malloc(sizeof(Autor));

				if (t == NULL)
					return;

				strcpy(t->ime, ime);
				strcpy(t->prezime, prezime);
				t->bodova = 2 / (double)brojAutora;
				t->sledeci = NULL;

				if (lista == NULL)
					lista = t;
				else
				{
					t->sledeci = lista;
					lista = t;
				}
			}
		}

		char c;

		while (c = getc(radovi))
			if (c == '\n' || c == EOF)
				break;
	}

	fclose(radovi);

	FILE *izlaz = fopen("izlaz.txt", "w");

	Autor *tmp = lista;

	while (tmp)
	{
		if (tmp->bodova >= 1)
		{
			fprintf(izlaz, "%s %s ", tmp->ime, tmp->prezime);

			if (tmp->bodova >= 3)
				fprintf(izlaz, "vanredni profesor\n");
			else if (tmp->bodova >= 2)
				fprintf(izlaz, "vanredni profesor\n");
			else if (tmp->bodova >= 1)
				fprintf(izlaz, "docent\n");
		}

		tmp = tmp->sledeci;
	}

	oslobodiMemoriju(lista);

	fclose(izlaz);
}