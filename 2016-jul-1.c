/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 1 - jul 2016. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

int palindrom(int broj)
{
	for (int i = 0;i < 31;i++)
	{
		int levi = (broj >> (31 - i)) & 0x0001;
		int desni = (broj >> i) & 0x0001;

		if (levi != desni)
			return 0;
	}

	return 1;
}

void main()
{
	unsigned int *niz = NULL;
	int n = 0;

	while (1)
	{
		int t;
		scanf("%d", &t);

		if (t < 0)
			break;

		niz = realloc(niz, (n + 1) * 8 * sizeof(unsigned int));

		if (niz == NULL)
		{
			printf("Nema dovoljno prostora u memoriji. Bice provereni da li su palindromi samo do sada uneti elementi bez trenutnog.");
			break;
		}

		niz[n] = t;
		n++;
	}

	for (int i = 0;i < n;i++)
	{
		if (palindrom(niz[i]))
			printf("Element %d je palindrom\n", niz[i]);
		else
			printf("Element %d nije palindrom\n", niz[i]);
	}

	free(niz);
}