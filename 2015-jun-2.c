/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 2 - jun 2015. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct Univerzitet
{
	char ime[30];
	int prisutnost, uticaj, otvorenost, izuzetnost;
	float sPoeni, sRang, nPoeni, nRang;
	struct Univerzitet *sledeci;
} Univerzitet;

float sBrojBodova(Univerzitet *data)
{
	return data->prisutnost *0.2 + data->uticaj * 0.5 + data->otvorenost * 0.15 + data->izuzetnost*0.12;
}

float nBrojBodova(Univerzitet *data)
{
	return data->prisutnost *0.5 + data->uticaj / 6 + data->otvorenost / 6 + data->izuzetnost / 6;
}

Univerzitet *ucitajPodatke()
{
	FILE *fajl = fopen("univerziteti.txt", "r");

	if (fajl == NULL)
		return;

	char ime[MAX];
	int prisutnost, uticaj, otvorenost, izuzetnost;

	Univerzitet *lista = NULL;

	while (fscanf(fajl, "%s %d %d %d %d", &ime, &prisutnost, &uticaj, &otvorenost, &izuzetnost) != EOF)
	{
		Univerzitet *t = malloc(sizeof(Univerzitet));

		if (t == NULL)
			return;
		
		strcpy(t->ime, ime);
		t->prisutnost = prisutnost;
		t->uticaj = uticaj;
		t->otvorenost = otvorenost;
		t->izuzetnost = izuzetnost;

		t->sPoeni = sBrojBodova(t);
		t->nPoeni = nBrojBodova(t);
		t->sledeci = NULL;

		if (lista == NULL)
			lista = t;
		else
		{
			t->sledeci = lista;
			lista = t;
		}
	}

	fclose(fajl);

	return lista;
}

void odrediRang (Univerzitet *lista)
{
	Univerzitet *pocetak = lista;
	int i = 1;

	// po starom
	for (Univerzitet *i = pocetak;i != NULL;i = i->sledeci)
	{
		for (Univerzitet *j = i;j != NULL;j = j->sledeci)
		{
			if (i->sPoeni > j->sPoeni)
			{
				float t = i->sPoeni;
				i->sPoeni = j->sPoeni;
				j->sPoeni = t;
			}
		}
	}
	
	while (lista)
	{
		lista->sRang = i++;

		lista = lista->sledeci;
	}

	lista = pocetak;
	i = 1;

	// po novom
	for (Univerzitet *i = pocetak;i != NULL;i = i->sledeci)
	{
		for (Univerzitet *j = i;j != NULL;j = j->sledeci)
		{
			if (i->nPoeni > j->nPoeni)
			{
				float t = i->nPoeni;
				i->nPoeni = j->nPoeni;
				j->nPoeni = t;
			}
		}
	}
	
	while (lista)
	{
		lista->nRang = i++;

		lista = lista->sledeci;
	}
}

float najvecaPromena(Univerzitet *lista)
{
	Univerzitet *t;
	float maxDx = 0;

	while (lista)
	{
		float dx = abs(lista->sRang - lista->nRang);

		if (dx > maxDx)
		{
			maxDx = dx;
			t = lista;
		}

		lista = lista->sledeci;
	}

	return maxDx;
}

void main()
{
	Univerzitet *lista = ucitajPodatke();
	odrediRang(lista);
	float mdx = najvecaPromena(lista);
	FILE *izlaz = fopen("izlaz.txt", "w");

	if (izlaz == NULL)
		return;

	Univerzitet *t = lista;

	while (t)
	{
		if (abs(t->sRang - t->nRang) == mdx)
			fprintf(izlaz, "%s\n", t->ime);

		// oslobađanje memorije
		Univerzitet *tn = t->sledeci;
		free(t);
		t = tn;
	}

	fclose(izlaz);
}