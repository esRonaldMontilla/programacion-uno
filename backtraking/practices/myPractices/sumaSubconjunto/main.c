#include <stdio.h>
#include <stdbool.h>
#define TAMANIO 10

bool aceptable(int vector[], int tam, int opcion);
bool sumarSubconjunto(int conjunto[], int solucion[], int n, int *m, int indiceActual, int objetivo, int suma);

int main() {
    int miArreglo[TAMANIO];
    int solucion[TAMANIO];
    int cantNumeros = 0;
    int objetivo = 25;
    for (int i = 0; i < TAMANIO; i++) {
        miArreglo[i] = i + 1;
    }
    if (sumarSubconjunto(miArreglo, solucion, TAMANIO, &cantNumeros, 0, objetivo, 0) == true) {
        for (int i = 0; i < cantNumeros; i++) {
            printf("%d ", miArreglo[solucion[i]]);
        }
    } else {
        printf("No se encontra una solucion.\n");
    }
    return 0;
}

bool aceptable(int vector[], int tam, int opcion) {
    for (int i = 0; i < tam; i++) {
        if (vector[i] == opcion) {
            return false;
        }
    }
    return true;
}

bool sumarSubconjunto(int conjunto[], int solucion[], int n, int *m, int indiceActual, int objetivo, int suma) {
    bool salida = false;
    while (indiceActual < n && salida == false) {
        suma = suma + conjunto[indiceActual];
        if (suma <= objetivo) {
            solucion[*m] = indiceActual;
            *m = *m + 1;
            if (suma == objetivo) {
                salida = true;
            } else {
                salida = sumarSubconjunto(conjunto, solucion, n, m, indiceActual + 1, objetivo, suma);
                if (salida == false) {
                    suma = suma - conjunto[indiceActual];
                    *m = *m - 1;
                }
            }
        } else {
            suma = suma - conjunto[indiceActual];
        }
        indiceActual++;
    }
    return salida;
}