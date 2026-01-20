//gcc main.c csvm.c -o mainc		<-tak kompilujemy
//./mainc				<-tak uruchomjemy

#include <stdlib.h>
#include <stdio.h>
#include "csvm.h"
#include <time.h>

void zwolnij_vector(CMatrix *mat)
{
	for(int i =0; i<mat->num_vectors; i++)
	{
		free(mat->vectors[i]);
	}

}

void zwolnij_matrix(CMatrix *mat) // funkcja czysci malloca macierzy i zeruje wskaznik
{
	if(mat != NULL)
	{
		zwolnij_vector(mat);
		free(mat);
		mat = NULL;
	}
}

void wyswietl_matrix(CMatrix *arr)
{
	if(arr == NULL){printf("\n[BLAD] Macierz nie istnieje!\n");} //sprawdzamy czy macierz istnieje zeby 
									//uniknac segfaulta
	else
	{
		printf("\n");
		for(int i =0; i<arr->num_vectors; i++)
		{
			for(int j=0; j<arr->vectors[i]->size; j++)
			{
				if(arr->vectors[i]->data[j] > 9)
				{			
					printf("%d ", arr->vectors[i]->data[j]);
				}
				else
				{
					printf("%d  ", arr->vectors[i]->data[j]);
				}
			}
			printf("\n");
		}
	}
	
}

void zmien_losowa_wartosc(CMatrix *arr)
{
	int rows = rand() % (arr->num_vectors);
	int cols = rand() % (arr->vectors[rows]->size);
	int x = rand() % 99 + 1;

	printf("[OPERACJA] Losuje wiersz %d i kolumne %d do modyfikacji wartosci na %d.", rows+1, cols+1, x);

	arr->vectors[rows]->data[cols] = x;
}

CVector *alokuj_vector(int size)
{
	CVector *vec = malloc(sizeof(CVector));

	vec->size = size;
	vec->data   = calloc(size, sizeof(double));

	for (int j = 0; j < size; ++j) {vec->data[j] = rand() % 99 + 1;} //99  sie aldniej wyswietla 
	return vec;
}

CMatrix *generuj_losowa_matrix()
{
	int rows = MIN_ROWS + rand() % (MAX_ROWS - MIN_ROWS + 1);
	int cols = 0; //rolujemy co iteracje //MIN_COLS + rand() % (MAX_COLS - MIN_COLS + 1);

	CMatrix *m = malloc(sizeof(CMatrix));
	if (!m) 
	{
		return NULL;
	}
	m->num_vectors = rows;
	m->vectors     = NULL;   /* zabezpieczamy przed przypadkowym użyciem */

	m->vectors = calloc(rows, sizeof(CVector *));
	if (!m->vectors) 
	{
		free(m);
		return NULL;
	}

	for (int i = 0; i < rows; ++i) 
	{
		cols = MIN_COLS + rand() % (MAX_COLS - MIN_COLS + 1);
		m->vectors[i] = alokuj_vector(cols);   /* zapisujemy wskaźnik w tablicy */
	}

	return m;   /* gotowe! */
}

void dodaj_wiersz()
{

}

void usun_wiersz()
{

}

void podsumuj_matrix(CMatrix *mat)
{
	if(mat == NULL){printf("\n[BLAD] Macierz nie istnieje!\n");}
	else
	{
		int x = 0;
		printf("\n");
		for(int i =0; i<mat->num_vectors; i++)
		{
			for(int j=0; j<mat->vectors[i]->size; j++)
			{			
				x += mat->vectors[i]->data[j];
			}
		}
		printf("[SUKCES] Suma elemntow macierzy wynosi: %d.", x);
		printf("\n");
	}
	
}

void usun_kolumne()
{

}
