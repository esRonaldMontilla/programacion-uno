#include <stdio.h>

#define MAX 10

int n;
int perm[MAX];
int usado[MAX];

void permutar(int pos) {
    if (pos == n) {                      // solución completa
        for (int i = 0; i < n; i++)
            printf("%d ", perm[i]);
        printf("\n");
        return;
    }
    for (int num = 1; num <= n; num++) {
        if (!usado[num - 1]) {           // poda: no repetir
            perm[pos] = num;             // elegir
            usado[num - 1] = 1;
            permutar(pos + 1);           // explorar
            usado[num - 1] = 0;          // deshacer
        }
    }
}

int main(void) {
    n = 4;
    permutar(0);
    return 0;
}