/*#define MIN_ROWS 2
#define MAX_ROWS 10
#define MIN_COLS 2
#define MAX_COLS 10*/

typedef enum {
    MIN_ROWS = 2,
    MAX_ROWS = 10,
    MIN_COLS = 2,
    MAX_COLS = 10
} rowsy_i_colsy;

typedef enum {
    MENU_GENERUJ = 1,
    MENU_WYSWIETL,
    MENU_MODYFIKUJ,
    MENU_PODSUMUJ,
    MENU_ZAPISZ,
    MENU_WCZYTAJ, //do tego miejsca sie same inkrementuja o 1 
    MENU_KONIEC = 0
} menu_option;

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

void zapisz_matrix_do_pliku(CMatrix *mat);

CMatrix *wczytaj_matrix_z_pliku();
