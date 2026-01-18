#include <stdlib.h>
#include "csvm.h"
#include <time.h>

void zwolnij_matrix(CMatrix *arr) // funkcja zeruje cols
{
	free(arr);
}

void wyswietl_matrix()
{

}

void zmien_losowa_wartosc()
{

}

CMatrix *generuj_losowa_matrix()
{
    int rows = MIN_ROWS + rand() % (MAX_ROWS - MIN_ROWS + 1);
    int cols = MIN_COLS + rand() % (MAX_COLS - MIN_COLS + 1);

    CMatrix *m = malloc(sizeof(CMatrix));
    if (!m) {
        //perror("malloc CMatrix");
        return NULL;
    }
    m->num_vectors = rows;
    m->vectors     = NULL;   /* zabezpieczamy przed przypadkowym użyciem */

    m->vectors = calloc(rows, sizeof(CVector *));
    if (!m->vectors) {
       // perror("calloc vectors");
        free(m);
        return NULL;
    }

    for (int i = 0; i < rows; ++i) {
        CVector *vec = malloc(sizeof(CVector));
        if (!vec) {
         //   perror("malloc CVector");
            /* w razie błędu zwalniamy wszystko, co już było przydzielone */
            for (int j = 0; j < i; ++j) {
                free(m->vectors[j]->data);
                free(m->vectors[j]);
            }
            free(m->vectors);
            free(m);
            return NULL;
        }

        vec->size = cols;
        vec->data   = calloc(cols, sizeof(double));
        if (!vec->data) {
           // perror("calloc vec->data");
            free(vec);
            for (int j = 0; j < i; ++j) {
                free(m->vectors[j]->data);
                free(m->vectors[j]);
            }
            free(m->vectors);
            free(m);
            return NULL;
        }

        /* wypełniamy losowymi wartościami */
        for (int j = 0; j < cols; ++j)
            vec->data[j] = rand() % 100 + 1;

        m->vectors[i] = vec;   /* zapisujemy wskaźnik w tablicy */
    }

    return m;   /* gotowe! */
}

void dodaj_wiersz()
{

}

void usun_wiersz()
{

}

void podsumuj_matrix()
{

}

void usun_kolumne()
{

}

int* create_1d_array_re(int cols)
{
	int* wsk = NULL;
	wsk = (int*)malloc(cols*sizeof(int));
	return wsk;
}