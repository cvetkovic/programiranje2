/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 1 - oktobar 2016. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void main(int argc, char *argv[])
{
	FILE *izlaz = NULL, *ulaz = NULL;

	int brojSlova = 0, brojRedova = 1, brojReci = 0, brojRazmaka = 0;

	for (int i = 1;i < argc;i++)
	{
		if (i == 1)
		{
			izlaz = fopen(argv[i], "r+");

			if (izlaz == NULL)
				return;
			
			char c = 0;

			while ((c = getc(izlaz)) != EOF)
			{
				if (c == ' ')
					brojRazmaka++;
				else if (c == '\n')
					brojRedova++;
				else
					brojSlova++;

				if (c == ' ' || c == '\n')
					brojReci++;
			}

			if (argc > 1)
			{
				putc('\n', izlaz);
				brojRedova++;
				brojReci++;
			}
		}
		else
		{
			ulaz = fopen(argv[i], "r");
			char c = 0, zadnji = 0;

			if (ulaz == NULL)
				return;

			while ((c = getc(ulaz)) != EOF)
			{
				if (zadnji == '\n')
				{
					zadnji = 1;
					continue;
				}

				if (c == '\n')
					brojRedova++;
				else if (c == ' ')
					brojRazmaka++;
				else
					brojSlova++;

				if (c == ' ' || c == '\n')
					brojReci++;

				putc(c, izlaz);
				zadnji = c;
			}

			fclose(ulaz);
		}
	}

	brojReci++;

	fprintf(izlaz, "\nUkupan broj slova je: %d\n", brojSlova);
	fprintf(izlaz, "Ukupan broj redova je: %d\n", brojRedova);
	fprintf(izlaz, "Ukupan broj reci je: %d\n", brojReci);
	fprintf(izlaz, "Ukupan broj razmaka je: %d", brojRazmaka);

	fclose(izlaz);
}