#define MIN_ROWS 2
#define MAX_ROWS 10
#define MIN_COLS 2
#define MAX_COLS 10

//CVector* alokuj_vector(int size);

typedef struct
{
	int size;
	int* data;
} CVector;
typedef struct
{
	int num_vectors;
	CVector **vectors;
} CMatrix;

void zwolnij_matrix();

CMatrix *generuj_losowa_matrix();

void wyswietl_matrix(CMatrix *arr);

void podsumuj_matrix(CMatrix *mat);

void zwolnij_matrix(CMatrix *mat);

int modyfikuj_matrix(CMatrix* mat);

void dodaj_wiersz(CMatrix *mat);

void usun_wiersz(CMatrix *mat);

void zmien_losowa_wartosc(CMatrix *arr);

void usun_kolumne(CMatrix *mat);

void zwolnij_vector(CMatrix *mat);

CVector *alokuj_vector(int size);
