/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 1 - jun 2015. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

int daLiJeRecSifrovana(char *pocetak, char *kraj)
{
	if (isupper(pocetak[0])==1 && pocetak[1] == '@' && isupper(kraj[0])==1)
	{
		for (int i = 2;i < (kraj - pocetak);i++)
		{
			if (!isdigit(pocetak[i]))
				return 0;
		}

		return 1;
	}

	return 0;
}

int indeksSledecegRazmaka(char *string, int pozicija, int duzina)
{
	for (int i = pozicija;i < duzina;i++)
	{
		if (string[i] == ' ' || string[i] == '\0')
			return i;
	}

	return -1;
}

void main()
{
	int brojReci = 0;
	int brojSifrovanihReci = 0;

	char *string = NULL;
	char c;
	int n = 0;
		
	while ((c = getchar()) != '\n')
	{
		if (n % MAX == 0)
		{
			string = realloc(string, ((n / MAX) + 1)*MAX * sizeof(char));

			if (string == NULL)
				return;
		}

		string[n] = c;
		n++;

		if (c == ' ')
			brojReci++;
	}

	if (n % MAX == 0)
	{
		string = realloc(string, ((n / MAX) + 1)*MAX * sizeof(char));

		if (string == NULL)
			return;
	}

	string[n] = '\0';
	brojReci++;

	int zadnjiRazmak = 0;
	char last = 0;

	// obrada
	for (int i = 0;i < n;i++)
	{
		if (last == ' ' || string[i] == '\n' || i==0)
		{
			int duzina = strlen(string);

			if (daLiJeRecSifrovana(&string[i], &string[indeksSledecegRazmaka(string, i, duzina)-1]))
			{
				brojSifrovanihReci++;
				int lng = indeksSledecegRazmaka(string, i, duzina) - i;
				
				for (int j = i;j < duzina;j++)
				{
					string[j - 1] = string[j + lng];
				}

				n = strlen(string);
			}
		}

		last = string[i];
	}
	
	printf("%s\n", string);
	printf("%.0f%%", ((double)brojSifrovanihReci / brojReci) * 100);

	free(string);
}