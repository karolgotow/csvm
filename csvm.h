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

void wyswietl_matrix();

void modyifkuj_matrix();

void podsumuj_matrix();

void zwolnij_matrix(CMatrix *arr);

void dodaj_wiersz();

void usun_wiersz();

void zmien_losowa_wartosc();

void usun_kolumne();