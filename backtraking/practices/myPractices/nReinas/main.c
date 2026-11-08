#include <stdio.h>
#include <stdbool.h>
#define TAM_TABLERO 5

bool esAlternativaValida(int vector[], int dimTablero, int actual, int seleccion) {
    if (actual == 0) {
        return true;
    } else if (seleccion - 1 != vector[actual - 1] && seleccion + 1 != vector[actual - 1]) {
        for (int i = 0; i < actual; i++) {
            if (vector[i] == seleccion) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool nReinas(int vector[], int dimTablero, int pasoX, int cantReinas) {
    int pasoY = 0;
    while (pasoX < dimTablero && pasoY < dimTablero) {
        if (esAlternativaValida(vector, dimTablero, pasoX, pasoY)) {
            vector[pasoX] = pasoY;
            cantReinas--;
            if (cantReinas == 0) {
                return true;
            } else {
                if (nReinas(vector, dimTablero, pasoX + 1, cantReinas) == 1) {
                    return true;
                }
                vector[pasoX] = -1;
                cantReinas++;
            }
        }
        pasoY++;
    }
    return false;
}

int main() {
    int miTablero[TAM_TABLERO] = {-1};
    if (nReinas(miTablero, TAM_TABLERO, 0, 5)) {
        for (int i = 0; i < TAM_TABLERO; i++) {
            printf("Reina en: TABLERO[%d][%d]\n", miTablero[i], i);
        }
    } else {
        printf("No se encontro solucion.\n");
    }
    return 0;
}