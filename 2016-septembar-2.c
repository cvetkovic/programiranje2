/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 2 - septembar 2016. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

void main()
{
	FILE *ukrstenica = fopen("ukrstenica.txt", "r");
	int n;
	int tHorizontalno = 0, tVertikalno = 0, maxHorizontalno = 0, maxVertikalno = 0;
	int minHorizontalno = 0, minVertikalno = 0;
	int t;

	int matrica[MAX][MAX];

	if (ukrstenica == NULL)
		return;

	fscanf(ukrstenica, "%d", &n);

	// popunjavanje matrica (moze da se napravi i dinamicka matrica)
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			fscanf(ukrstenica, "%d", &t);

			matrica[i][j] = t;
		}
	}

	fclose(ukrstenica);

	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			// HORIZONTALA
			// po horizontali - maksimum
			if (matrica[i][j] == 0)
				tHorizontalno++;
			else
			{
				// minimum
				if (minHorizontalno == 0)
					minHorizontalno = tHorizontalno;
				else
					if (tHorizontalno < minHorizontalno && tHorizontalno != 0)
						minHorizontalno = tHorizontalno;
				
				// restartovanje brojača jer je kraj reči
				tHorizontalno = 0;
			}

			if (tHorizontalno > maxHorizontalno)
				maxHorizontalno = tHorizontalno;

			// VERTIKALA
			// po vertikali - maksimum
			if (matrica[j][i] == 0)
				tVertikalno++;
			else
			{
				// minimum
				if (minVertikalno == 0)
					minVertikalno = tVertikalno;
				else
					if (tVertikalno < minVertikalno && tVertikalno != 0)
						minVertikalno = tVertikalno;

				// restartovanje brojača jer je kraj reči
				tVertikalno = 0;
			}

			if (tVertikalno > maxVertikalno)
				maxVertikalno = tVertikalno;

			if (j == (n - 1))
			{
				// minimum
				if (minVertikalno == 0)
					minVertikalno = tVertikalno;
				else
					if (tVertikalno < minVertikalno && tVertikalno != 0)
						minVertikalno = tVertikalno;

				// restartovanje brojača jer je kraj reči
				tVertikalno = 0;
			}
		}

		// minimum
		if (minHorizontalno == 0)
			minHorizontalno = tHorizontalno;
		else
			if (tHorizontalno < minHorizontalno && tHorizontalno != 0)
				minHorizontalno = tHorizontalno;

		// restartovanje brojača jer je kraj reči, tj. reda
		tHorizontalno = 0;
	}

	FILE *recnik = fopen("reci.txt", "r");
	char rec[MAX];

	if (recnik == NULL)
		return;

	while (fscanf(recnik, "%s", &rec) != EOF)
	{
		int l = strlen(rec);

		if (((minHorizontalno <= l) && (l <= minVertikalno)) || ((minVertikalno <= l) && (l <= maxVertikalno)))
			printf("%s\n", rec);
	}

	fclose(recnik);
}