/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 1 - januar 2015. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 21 // +1 zbog '\0'

typedef struct Dete
{
	char ime[MAX];
	char poklon[MAX];
	struct Dete *sledece;
} Dete;

typedef struct Zapis
{
	char ime[MAX];
	char ulica[MAX];
	unsigned int broj;
} Zapis;

typedef struct ElementListe
{
	struct Zapis zapis;
	struct ElementListe *sledeci;
} ElementListe;

typedef struct NajvisePojavljivanja
{
	char ulica[MAX];
	int brojPojavljivanja;
	struct NajvisePojavljivanja *sledeci;
} NajvisePojavljivanja;

void napraviBinarnuDatoteku()
{
	FILE *d = fopen("adresar.dat", "wb");

	for (int i = 1;i <= 5;i++)
	{
		Zapis z;

		scanf("%s %s %d", &z.ime, &z.ulica, &z.broj);
		fwrite(&z, sizeof(Zapis), 1, d);
	}

	fclose(d);
}

int proveriDaLiSadrzi(NajvisePojavljivanja *lista, ElementListe *t)
{
	NajvisePojavljivanja *p = lista;

	if (lista == NULL)
		return 0;

	while (t)
	{
		while (p)
		{
			if (strcmp(p->ulica, t->zapis.ulica) == 0)
				return 1;

			p = p->sledeci;
		}

		p = lista;
		t = t->sledeci;
	}

	return 0;
}

NajvisePojavljivanja *nadiNajvisePojavljivanja(ElementListe *lista)
{
	NajvisePojavljivanja *rez = NULL;
	NajvisePojavljivanja *pocetak = NULL;

	while (lista)
	{
		if (proveriDaLiSadrzi(pocetak, &lista->zapis))
		{
			rez = pocetak;

			while (rez)
			{
				if (strcmp(rez->ulica, lista->zapis.ulica) == 0)
				{
					rez->brojPojavljivanja++;
					break;
				}

				rez = rez->sledeci;
			}

			rez = pocetak;
		}
		else
		{
			NajvisePojavljivanja *t = malloc(sizeof(NajvisePojavljivanja));

			if (t == NULL)
				return;

			strcpy(t->ulica, lista->zapis.ulica);
			t->brojPojavljivanja = 1;
			t->sledeci = NULL;

			if (pocetak == NULL)
				pocetak = t;
			else
			{
				t->sledeci = pocetak;
				pocetak = t;
			}
		}

		lista = lista->sledeci;
	}

	int max=0;
	NajvisePojavljivanja *rezultat = NULL;

	while (pocetak)
	{
		if (pocetak->brojPojavljivanja > max)
		{
			max = pocetak->brojPojavljivanja;
			rezultat = pocetak;
		}

		pocetak = pocetak->sledeci;
	}

	return rezultat;
}

void main()
{
	FILE *zelje = fopen("zelje.txt", "r");

	Dete *listaDece = NULL;
	ElementListe *lista = NULL;
	char ime[MAX];
	char poklon[MAX];
	char adresa[MAX];
	unsigned int broj;

	while (fscanf(zelje, "%s %s", &ime, &poklon) != EOF)
	{
		Dete *t = malloc(sizeof(Dete));

		if (t == NULL)
			break;

		strcpy(t->ime, ime);
		strcpy(t->poklon, poklon);
		t->sledece = NULL;

		if (listaDece == NULL)
			listaDece = t;
		else
		{
			t->sledece = listaDece;
			listaDece = t;
		}
	}

	fclose(zelje);

	FILE *adresar = fopen("adresar.dat", "rb");

	if (adresar == NULL)
		return;

	Zapis z;

	while (fread(&z, sizeof(Zapis), 1, adresar))
	{
		ElementListe *e = malloc(sizeof(ElementListe));

		e->zapis = z;
		e->sledeci = NULL;
		
		if (lista == NULL)
			lista = e;
		else
		{
			e->sledeci = lista;
			lista = e;
		}
	}

	fclose(adresar);

	NajvisePojavljivanja np = *nadiNajvisePojavljivanja(lista);

	printf("%s\n", np.ulica);

	ElementListe *zaBrisanje = lista;

	while (lista)
	{
		if (strcmp(lista->zapis.ulica, np.ulica) == 0)
		{
			printf("%d %s ", lista->zapis.broj, lista->zapis.ulica);

			Dete *ppp = listaDece;
			
			while (listaDece)
			{
				if (strcmp(listaDece->ime, lista->zapis.ime) == 0)
				{
					printf("%s", listaDece->poklon);
					break;
				}

				listaDece = listaDece->sledece;
			}

			listaDece = ppp;

			putchar('\n');
		}

		lista = lista->sledeci;
	}

	// oslobadanje memorije
	while (listaDece)
	{
		Dete *t = listaDece->sledece;
		free(listaDece);
		listaDece = t;
	}

	while (lista)
	{
		ElementListe *t = lista->sledeci;
		free(lista);
		lista = t;
	}
}