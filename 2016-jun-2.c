/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 2 - jun 2016. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 50
#define MAX_EMAIL 50

typedef struct Korisnik
{
	char ime[MAX_IME];
	char email[MAX_EMAIL];
	unsigned int vremePrijave, ukupnoVreme;
	struct Korisnik *sledeci;
} Korisnik;

Korisnik *formirajListuKorisnika(FILE *odakle)
{
	Korisnik *lista = NULL;
	Korisnik *t = NULL;
	Korisnik *prethodni = NULL;

	char ime[MAX_IME], email[MAX_EMAIL];

	while (fscanf(odakle, "%s %s", &ime, &email) != EOF)
	{
		t = malloc(sizeof(Korisnik));
		
		if (t == NULL)
			return;

		strcpy(t->ime, ime);
		strcpy(t->email, email);

		if (lista == NULL)
			lista = t;

		if (prethodni != NULL)
			prethodni->sledeci = t;

		t->vremePrijave;
		t->ukupnoVreme = 0;

		t->sledeci = NULL;
		prethodni = t;
	}

	return lista;
}

Korisnik *procitajLog(FILE *log, Korisnik *lista)
{
	Korisnik *pocetak = lista;

	char email[MAX_EMAIL];
	char c;
	int vreme;

	Korisnik *t;

	while (fscanf(log, "%s %c %d", &email, &c, &vreme) != EOF)
	{
		while (lista)
		{
			if (strcmp(lista->email, email)==0)
			{
				t = lista;
				break;
			}

			lista = lista->sledeci;
		}

		if (c == 'p')
		{
			t->vremePrijave = vreme;
		}
		else
		{
			t->ukupnoVreme += (vreme - t->vremePrijave);
			t->vremePrijave = 0;
		}

		lista = pocetak;
	}

	return pocetak;
}

void oslobodiMemoriju(Korisnik *lista)
{
	while (lista)
	{
		Korisnik *t = lista;
		lista = lista->sledeci;

		free(t);
	}
}

void main()
{
	FILE *korisnici, *log;

	korisnici = fopen("korisnici.txt", "r");
	log = fopen("log.txt", "r");

	Korisnik *listaKorisnika = formirajListuKorisnika(korisnici);
	listaKorisnika = procitajLog(log, listaKorisnika);

	Korisnik *max = NULL, *t = listaKorisnika;

	while (listaKorisnika)
	{
		if (max == NULL)
		{
			max = listaKorisnika;
		}
		else
		{
			if (max->ukupnoVreme < t->ukupnoVreme)
				max = t;
		}

		listaKorisnika = listaKorisnika->sledeci;
	}

	printf("%s", max->ime);

	oslobodiMemoriju(listaKorisnika);
}