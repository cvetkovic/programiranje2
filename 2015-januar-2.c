/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 2 - januar 2015. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

#define MAX 100

int izbaciKrugoveSaPreklapanjem(float x[], float y[], float r[], int n)
{
	for (int i = 0;i < n;i++)
	{
		int preklapaSe = 0;

		for (int j = i+1;j < n;j++)
		{
			float razlika = abs(r[i] - r[j]);
			float koren = sqrt(pow((x[i] - x[j]), 2) + pow(y[i] - y[j], 2));

			if (razlika >= koren)
			{
				// preklapaju se, brisanje
				for (int m = j;m < n;m++)
				{
					x[m] = x[m + 1];
					y[m] = y[m + 1];
					r[m] = r[m + 1];
				}
				
				j--;
				n--;

				preklapaSe = 1;
			}
		}

		if (preklapaSe)
		{
			for (int m = i;m < n;m++)
			{
				x[m] = x[m + 1];
				y[m] = y[m + 1];
				r[m] = r[m + 1];
			}

			i--;
			n--;
		}
	}

	return n;
}

float pronadiNajveciKrug(float x[], float y[], float r[], int n)
{
	float max = 0;
	int indeks = -1;

	for (int i = 0;i < n;i++)
		if (r[i] > max)
		{
			max = r[i];
			indeks = i;
		}
	
	return indeks;
}

void main()
{
	float x[MAX], y[MAX], r[MAX];
	int n;

	printf("Unesite broj krugova:\n");
	scanf("%d", &n);

	printf("Unosite podatke u krugovima u obliku %x, %y, %r\n");
	for (int i = 0;i < n;i++)
		scanf("%f %f %f", &x[i], &y[i], &r[i]);

	n = izbaciKrugoveSaPreklapanjem(x, y, r, n);

	printf("Krugovi koji se ne preklapaju su krugovi sa sledecim koordinatama:\n");
	for (int i = 0;i < n;i++)
		printf("x=%f y=%f r=%f\n", x[i], y[i], r[i]);

	printf("Najveci je krug sa koordinatama:\n");
	n = pronadiNajveciKrug(x, y, r, n);
	if (n != -1)
		printf("x=%f y=%f r=%f\n", x[n], y[n], r[n]);
	else
		printf("Nema ni jednog kruga u nizu.");
}