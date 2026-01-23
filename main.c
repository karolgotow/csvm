//gcc main.c csvm.c -o mainc		<-tak kompilujemy
//./mainc				<-tak uruchomjemy

#include "csvm.h" //<-main.c wspoldziei naglowki tutaj
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// gotowe części kodu
// Definicje stałych dla granic macierzy

int generuj_losowa(int min, int max) {
    if (min > max) return min;
    return rand() % (max - min + 1) + min;
}

int modyfikuj_matrix(CMatrix* mat) {
    if (!mat || mat->num_vectors == 0) {
        printf("[!] Najpierw wygeneruj macierz (Opcja 1).\n");
        return 0;
    }

    printf("\n--- Modyfikacja CMatrix ---\n");

    // Losowe wybranie typu modyfikacji
    int operation = generuj_losowa(1, 4);

    switch (operation) {
    case 1: // Dodaj wiersz
        dodaj_wiersz(mat);
        break;
    case 2: // Usuń wiersz
        usun_wiersz(mat);
        break;
    case 3: // Zmień losową wartość
        zmien_losowa_wartosc(mat);
        break;
    case 4: // Usuń kolumnę
        usun_kolumne(mat);
        break;
    }

    printf("---------------------------\n");
    return 1;
}


void wyswietl_menu() {
    printf("\n============================================\n");
    printf("  Zarzadzanie Zlozonymi Strukturami (CSVM)\n");
    printf("============================================\n");
    printf("1. Generuj nowa losowa CMatrix\n");
    printf("2. Wyswietl aktualna CMatrix\n");
    printf("3. Modyfikuj CMatrix (Losowa operacja)\n");
    printf("4. Podsumuj CMatrix (Suma elementow)\n");
    printf("5. Zapisz CMatrix do pliku\n");
    printf("6. Wczytaj CMatrix z pliku\n");
    printf("0. Wyjscie i zwolnienie pamieci\n");
    printf("Wybierz opcje: ");
}

int main() {
    // Inicjalizacja generatora liczb losowych
    srand((unsigned int)time(NULL));

    CMatrix* my_matrix = NULL;
    int choice;

    do {
        wyswietl_menu();
        if (scanf("%d", &choice) != 1) {
            // Czyszczenie bufora wejścia w przypadku błędnego typu
            while (getchar() != '\n');
            choice = -1;
            continue;
        }
	choice = (menu_option)choice; //rzutowanie dla kompilatora ale bez potrzeby tutaj raczej
        switch (choice) {
        case MENU_GENERUJ:
            // Zwalniamy stara macierz przed alokacja nowej
            if (my_matrix != NULL) {
                zwolnij_matrix(my_matrix);
                my_matrix = NULL;
            }
            printf("\n[OPERACJA] Generowanie nowej macierzy...\n");
            my_matrix = generuj_losowa_matrix();
            if (my_matrix) {
                printf("[SUKCES] Macierz wygenerowana. Rozmiar: %d wierszy.\n", my_matrix->num_vectors);
                wyswietl_matrix(my_matrix);
            }
	    printf("---------------------------\n");
            break;

        case MENU_WYSWIETL:
            wyswietl_matrix(my_matrix);
	    printf("---------------------------\n");
            break;

        case MENU_MODYFIKUJ:
            if (modyfikuj_matrix(my_matrix)) {
                printf("\n[SUKCES] Macierz zmodyfikowana. Stan po operacji:\n");
                wyswietl_matrix(my_matrix);
            }
	    printf("---------------------------\n");
            break;

        case MENU_PODSUMUJ:
            podsumuj_matrix(my_matrix);
	    printf("---------------------------\n");
            break;

        case MENU_ZAPISZ:
            zapisz_matrix_do_pliku(my_matrix);
	    printf("---------------------------\n");
            break;

        case MENU_WCZYTAJ:
            my_matrix = wczytaj_matrix_z_pliku();
	 wyswietl_matrix(my_matrix);
	    printf("---------------------------\n");
            break;

        case MENU_KONIEC:
            printf("\n[WYJSCIE] Zwalnianie pamieci i zakonczenie programu.\n");
            break;

        default:
            printf("[OSTRZEZENIE] Nieznana opcja. Sprobuj ponownie.\n");
        }
    } while (choice != 0);

    // Konieczne zwolnienie pamięci przy wyjściu
    zwolnij_matrix(my_matrix);

    return 0;
}
