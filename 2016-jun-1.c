/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 1 - jun 2016. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define brojkarakteraURedu 10
#define maksimalniBrojRedova 5000

void main()
{
	char **string = NULL;
	int brojReciPoRedu, brojRedova = 0;

	char lastChar = 0, c;

	string = malloc(maksimalniBrojRedova * sizeof(char*));

	if (string == NULL)
		return;

	// ucitavanje karaktera
	while ((c = getchar()) != '*')
	{
		string[brojRedova] = malloc(brojkarakteraURedu * sizeof(char));
		int n = 0, max = brojkarakteraURedu;

		if (string[brojRedova] == NULL)
			return;

		do
		{
			if (n >= max)
			{
				string[brojRedova] = realloc(string[brojRedova], (((max/brojkarakteraURedu) + 1)*brojkarakteraURedu) * sizeof(char));
				max += brojkarakteraURedu;

				if (string[brojRedova] == NULL)
					return;
			}

			string[brojRedova][n] = c;
			n++;
		} while ((c = getchar()) != '\n');

		if (n >= max)
		{
			string[brojRedova] = realloc(string[brojRedova], (((max / brojkarakteraURedu) + 1)*brojkarakteraURedu) * sizeof(char));
			max += brojkarakteraURedu;

			if (string[brojRedova] == NULL)
				return;
		}
		string[brojRedova][n] = '\0';

		lastChar = c;
		brojRedova++;
	}

	// unosenje maksimalnog broja reci po redu
	printf("Unesite broj reci po redu: \n");
	scanf("%d", &brojReciPoRedu);
	printf("Rezultat obrade je: \n");

	// obrada stringa
	int trenutniBrojReciURedu = 0;
	char trenutniKarakter, prethodniKarakter = 0;

	// javljaju se samo razmaci i slova
	for (int i = 0;i < brojRedova;i++)
	{
		int j = 0;

		while ((trenutniKarakter = string[i][j]) != '\0')
		{
			if (prethodniKarakter == ' ' && trenutniKarakter != ' ')
				trenutniBrojReciURedu++;

			if (trenutniBrojReciURedu == brojReciPoRedu)
			{
				trenutniBrojReciURedu = 0;

				putchar('\n');
			}

			putchar(string[i][j]);

			prethodniKarakter = trenutniKarakter;
			j++;
		}

		if (trenutniKarakter == '\0' && prethodniKarakter != ' ')
		{
			trenutniBrojReciURedu++;
			putchar(' ');
		}
	}

	// oslobadanje memorije
	for (int i = 0;i < brojRedova;i++)
		free(string[i]);

	free(string);
}