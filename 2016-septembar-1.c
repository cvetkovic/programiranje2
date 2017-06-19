/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 1 - septembar 2016. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
	int naziv;
	int kapacitet;
	int vremePocetka;
	int vremeKraja;
	struct Element *sledeci;
} Element;

Element *dodajTermin(Element *lista, Element *novi)
{
	if (lista == NULL)
		novi->sledeci = NULL;
	else
		novi->sledeci = lista;

	return novi;
}

Element *pronadiOdgovarajuceSale(Element *lista, int sati, int ljudi)
{
	Element *pocetnaPozicija = lista;
	Element *prethodni = NULL, *sledeci = NULL;

	while (lista)
	{
		if ((lista->kapacitet < ljudi) || ((lista->vremeKraja) - (lista->vremePocetka) < sati))
		{
			// brisanje

			if (prethodni == NULL)
			{
				pocetnaPozicija = lista->sledeci;
			}
			else
			{
				prethodni->sledeci = lista->sledeci;
				prethodni = lista;
			}

			Element *naNovi = lista->sledeci;
			free(lista);
			lista = naNovi;

			continue;
		}

		prethodni = lista;
		lista = lista->sledeci;
	}

	return pocetnaPozicija;
}

Element *sortirajRezultat(Element *lista)
{
	for (Element *i = lista;i != NULL;i = i->sledeci)
	{
		for (Element *j = i;j != NULL;j = j->sledeci)
		{
			if ((i->kapacitet > j->kapacitet) || ((i->naziv == j->naziv) && (i->vremePocetka > j->vremePocetka)))
			{
				int t = j->naziv;
				j->naziv = i->naziv;
				i->naziv = t;

				t = j->kapacitet;
				j->kapacitet = i->kapacitet;
				i->kapacitet = t;

				t = j->vremePocetka;
				j->vremePocetka = i->vremePocetka;
				i->vremePocetka = t;

				t = j->vremeKraja;
				j->vremeKraja = i->vremeKraja;
				i->vremeKraja = t;
			}
		}
	}

	return lista;
}

void main()
{
	int brojPotrebnihSati, brojLjudi;
	scanf("%d %d", &brojPotrebnihSati, &brojLjudi);

	Element *lista = NULL;

	char c;

	while ((c = getchar()) != '*')
	{
		int brojSale = 0, brojStudenata = 0, pocetak = 0, kraj = 0;
		int pozicija = 0;

		do
		{
			if (c == ' ' || c == '\n')
			{
				if (pozicija == 3)
				{
					Element *novi = malloc(sizeof(Element));

					if (novi == NULL)
						return;

					novi->naziv = brojSale;
					novi->kapacitet = brojStudenata;
					novi->vremePocetka = pocetak;
					novi->vremeKraja = kraj;

					lista = dodajTermin(lista, novi);

					pozicija = 1;

					pocetak = 0;
					kraj = 0;
				}
				
				if (c == '\n')
					break;

				pozicija++;

				continue;
			}
			else if (c == '-')
			{
				pozicija = 3;
				continue;
			}

			if (pozicija == 0)
			{
				brojSale = brojSale * 10 + (c - '0');
			}
			else if (pozicija == 1)
			{
				brojStudenata = brojStudenata * 10 + (c - '0');
			}
			else if (pozicija == 2)
			{
				pocetak = pocetak * 10 + (c - '0');
			}
			else if (pozicija == 3)
			{
				kraj = kraj * 10 + (c - '0');
			}
		} while ((c = getchar()));

		pozicija = 0;
	}

	lista = pronadiOdgovarajuceSale(lista, brojPotrebnihSati, brojLjudi);
	lista = sortirajRezultat(lista);

	if (lista != NULL)
	{
		int prethodnaIspisanaSala = -1;

		while (lista)
		{/*
			if (lista->naziv == prethodnaIspisanaSala)
				printf("%d-%d ", lista->vremePocetka, lista->vremeKraja);
			else
				printf("\n%d %d %d-%d ", lista->naziv, lista->kapacitet, lista->vremePocetka, lista->vremeKraja);*/
			if (lista->naziv != prethodnaIspisanaSala)
				printf("\n%d %d %d-%d ", lista->naziv, lista->kapacitet, lista->vremePocetka, lista->vremeKraja);


			prethodnaIspisanaSala = lista->naziv;
			lista = lista->sledeci;
		}
	}
	else
	{
		printf("Ne postoji slobodan termin!");
	}

	// oslobadanje memorije
	while (lista)
	{
		Element *sledeci = lista->sledeci;
		free(lista);
		lista = sledeci;
	}
}