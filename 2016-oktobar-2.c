/*	Univerzitet u Beogradu, Elektrotehnički fakultet
	Programiranje 2 (13E111P2)

	Zadatak br. 2 - oktobar 2016. godine

	Rešio: Lazar M. Cvetković
	E-mail: l.cvetkovic.997@gmail.com */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
	int value;
	int numberOfOccurrent;
	struct Element *following;
} Element;

Element *list;

int numberOfOccurrences(Element *pointer, int number)
{
	int numberOfOccurrence = 0;

	while (pointer)
	{
		if (pointer->value == number)
			numberOfOccurrence++;

		pointer = pointer->following;
	}

	return numberOfOccurrence;
}

int maxOccurrence(Element *pointer)
{
	int max = 0;

	while (pointer)
	{
		if (pointer->numberOfOccurrent > max)
			max = pointer->numberOfOccurrent;

		pointer = pointer->following;
	}

	return max;
}

void writeElements(Element *pointer, int max)
{
	while (pointer)
	{
		if (pointer->numberOfOccurrent == max)
			printf("%d se pojavljuje %d\n", pointer->value, max);

		pointer = pointer->following;
	}
}

void destructor(Element *pointer)
{
	while (pointer)
	{
		Element *t = pointer->following;

		free(pointer);

		pointer = t;
	}
}

void addOccurrence(Element *pointer, int number)
{
	if (!numberOfOccurrences(pointer, number))
	{
		Element *toBeAdded = malloc(sizeof(Element));

		toBeAdded->value = number;
		toBeAdded->numberOfOccurrent = 0;

		if (pointer == NULL)
		{
			toBeAdded->following = NULL;
			list = toBeAdded;
		}
		else
		{
			toBeAdded->following = pointer;

			list = toBeAdded;
		}
	}
	else
	{
		while (pointer)
		{
			if (pointer->value == number)
				pointer->numberOfOccurrent += 1;

			pointer = pointer->following;
		}
	}
}

void main()
{
	int entry = 1;

 	while (entry != 0)
	{
		scanf("%d", &entry);

		if (entry != 0)
			addOccurrence(list, entry);
	}

	writeElements(list, maxOccurrence(list));

	destructor(list);
}