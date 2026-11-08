#include <stdio.h>
#include <stdbool.h>
#define TAM 8

bool esValido(int laberinto[][TAM], int posX, int posY) {
    if (posX >= TAM || posY >= TAM) {
        return false;
    } else if (laberinto[posX][posY] == 1) {
        return false;
    }
    return true;
}

bool evaluarLaberinto(int laberinto[][TAM], int posX, int posY, int movX[], int movY[]) {
    if (posX == TAM - 1 && posY == TAM - 1) {
        laberinto[posX][posY] = 2;
        return true;
    }

    if (esValido(laberinto, posX, posY)) {
        laberinto[posX][posY] = 2;
        for (int i = 0; i < 2; i++) {
            int pX = posX + movX[i];
            int pY = posY + movY[i];
            if (evaluarLaberinto(laberinto, pX, pY, movX, movY)) {
                return true;
            }
        }
        laberinto[posX][posY] = 0;
        return false;
    } else {
        return false;
    }
}

int main() {
    int miLaberinto[TAM][TAM] = {
    {0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 1, 1},
    {1, 0, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 1, 0, 1, 1, 1, 0},
    {1, 1, 1, 0, 0, 0, 0, 0}
    };
    int posiblesMovX[2] = {0, 1};
    int posiblesMovY[2] = {1, 0};

    if (evaluarLaberinto(miLaberinto, 0, 0, posiblesMovX, posiblesMovY)) {
        for (int i = 0; i < TAM; i++) {
            printf("[ ");
            for (int j = 0; j < TAM - 1; j++) {
                printf("%d ", miLaberinto[i][j]);
            }
            printf("%d]\n", miLaberinto[i][TAM - 1]);
        }
    } else {
        printf("No se encontro una salida.\n");
    }
    return 0;
}