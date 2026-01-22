//gcc main.c csvm.c -o mainc		<-tak kompilujemy
//./mainc				<-tak uruchomjemy

#include <stdlib.h>
#include <stdio.h>
#include "csvm.h"
#include <time.h>
#include <string.h>

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

void wyswietl_matrix(CMatrix *mat)
{
	if(mat == NULL || mat->num_vectors == 0){printf("\n[BLAD] Macierz nie istnieje!\n");return;}
	printf("\n");
	printf("--- CMatrix (Rozmiar: %dx?) ---\n", mat->num_vectors);
	for(int i =0; i<mat->num_vectors; i++)
	{
		char spacja[1]="";
		//if(mat->vectors[i]->size < 10){spacja[0]=32;}
		printf("Wiersz %02d (Rozm: %02d): [ ", i+1, mat->vectors[i]->size);
		for(int j=0; j<mat->vectors[i]->size; j++)
		{
			//if(mat->vectors[i]->data[j] > 9)
			//{			
			printf("%02d ", mat->vectors[i]->data[j]);
			//}
			//else
			//{
			//	printf("%d  ", mat->vectors[i]->data[j]);
			//}
		}
		printf("]\n");
	}
}

void zmien_losowa_wartosc(CMatrix *mat)
{
	int rows = rand() % (mat->num_vectors);
	int cols = rand() % (mat->vectors[rows]->size);
	int x = rand() % 99 + 1;

	printf("[OPERACJA] Losuje wiersz %d i kolumne %d do modyfikacji wartosci na %d.\n", rows+1, cols+1, x);

	mat->vectors[rows]->data[cols] = x;
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

void dodaj_wiersz(CMatrix *mat)
{
	int cols = MIN_COLS + rand() % (MAX_COLS - MIN_COLS + 1);
	printf("[OPERACJA] Dodaje wiersz na koncu macierzy o dlugosci %d.", cols+1);
	if(mat->num_vectors > 9){printf("\n[BLAD] Macierz ma juz 10 wierszy!\n");return;}

	CVector **tmp = realloc(mat->vectors,
	(mat->num_vectors + 1) * sizeof *mat->vectors);
	
	mat->vectors = tmp;                     /* nowa tablica wskaźników */
	mat->vectors[mat->num_vectors] = alokuj_vector(cols);    /* wstawiamy nowy wiersz na koniec */
	mat->num_vectors++;                     /* aktualizujemy licznik */

	printf("\n[Sukces] Dodano 1 wiersz do macierzy!\n");
	return;                             /* sukces */
}

void usun_wiersz(CMatrix *mat)
{
	printf("[OPERACJA] Usuwam wiersz na koncu macierzy");
	CVector *ostatni = mat->vectors[mat->num_vectors - 1];
	free(ostatni);

	if (mat->num_vectors == 1) 
	{
		free(mat->vectors);
		mat->vectors = NULL;
		mat->num_vectors = 0;
		printf("\n[SUKCES] Usunieto jedyny wiersz macierzy!\n");
		return;
	}
	CVector **tmp = realloc(mat->vectors,
	(mat->num_vectors - 1) * sizeof *mat->vectors);
	if (!tmp) 
	{
		printf("\n[BLAD] Problem z realokowaniem!\n");
		return;
	}

	mat->vectors = tmp;
	mat->num_vectors--;
	printf("\n[SUKCES] Macierz zostala skrucona o ostatni wiersz!\n");
	return;
}

void podsumuj_matrix(CMatrix *mat)
{
	if(mat == NULL || mat->num_vectors == 0){printf("\n[BLAD] Macierz nie istnieje!\n");return;}
	int suma_wartosci = 0;
	int suma_elementow = 0;
	
	printf("\n");
	for(int i =0; i<mat->num_vectors; i++)
	{
		for(int j=0; j<mat->vectors[i]->size; j++)
		{			
			suma_wartosci += mat->vectors[i]->data[j];
			suma_elementow++;
		}
	}
	printf("--- Podsumowanie Cmatrix ---\n");
	printf("Liczba wierszy: %d\n", mat->num_vectors);
	printf("Liczba wszystkich elementow: %d\n", suma_elementow);
	printf("Suma wszystkich elementow wynosi: %d.", suma_wartosci);
	printf("\n");
}

void usun_kolumne(CMatrix *mat)
{
	int cols = rand() % (MAX_COLS-1);
	printf("[OPERACJA] Usuwam kolumne %d macierzy.\n", cols+1);
	int usuwane_kolumny = 0;
	for (int i = 0; i < mat->num_vectors; ++i) 
	{
		CVector *vector = mat->vectors[i];
		if (cols > 0 && cols <= vector->size)
		{	usuwane_kolumny++; //albo -=1 
		}	
	}
	if(usuwane_kolumny <= 0)
	{
		printf("[BLAD] Zla kolumna sie wylosowala\n");
		return;                     /* indeks poza zakresem */
	}

	for (int i = 0; i < mat->num_vectors; ++i) 
	{
		CVector *vector = mat->vectors[i];
		int temp_cols = vector->size;

		if (cols < temp_cols - 1) 
		{
			memmove(&vector->data[cols],
			&vector->data[cols + 1],
			(size_t)(temp_cols - cols - 1) * sizeof *vector->data);
		

			int *tmp = realloc(vector->data,
			(size_t)(temp_cols - 1) * sizeof *vector->data);

			if (!tmp && temp_cols - 1 > 0) 
			{
				printf("[BLAD] Realokacja nie powoiodla sie!\n");
				return;
			}
			vector->data = tmp;                    
			vector->size = temp_cols - 1;       
		}

		else
		{
			int *tmp = realloc(vector->data,
			(size_t)(temp_cols) * sizeof *vector->data);

			if (!tmp && temp_cols > 0) 
			{
				printf("[BLAD] Realokacja nie powoiodla sie!\n");
				return;
			}
			vector->data = tmp;                    
			vector->size = temp_cols;    
		}
	}
	printf("[Sukces] Usunieto kolumne %d macierzy.\n", cols+1);
	return;
}
