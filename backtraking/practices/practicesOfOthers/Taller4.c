#include <stdio.h>
//Estructura para la pieza dominó.
typedef struct{
    int izq, der;
}pieza_domino;
//Variables Globales que se vana usar en el main y las funciones.
int n_espacios, m_piezas, solucion_encontrada; //Variable para el número de espacios y piezas disponibles, y la variable que determina si la solución fue hallada.
pieza_domino inicial, final, disponibles[100]; //Piezas de domino inicial y final, y conjunto de piezas disponibles.
int usada[100]; //Control para no repetir piezas.
pieza_domino tablero[100]; //Guarda la secuencia de piezas para hallar la solución.
//Prototipado.
void buscar_conjunto_de_piezas(int paso);
int es_valida(pieza_domino p, int paso);
//Función principal.
int main(){
    //Variables para recorrer el archivo y para el archivo de salida.
    FILE *entrada = fopen("piezas.txt", "r");
    FILE *salida = fopen("solucion.txt", "w");
    //Condición para detectar si el archivo está vacio.
    if(entrada==NULL){
        printf("Se produjo un error, el archivo esta vacio.\n");
        return 1;
    }
    //Sale del while si n_espacios es igual a 0 como dice el enunciado, también leemos el n espacios.
    while((fscanf(entrada, "%d", &n_espacios)==1)&&(n_espacios!=0)){
        //Lee m_piezas disponibles.
        fscanf(entrada, "%d", &m_piezas);
        //Lee la primera pieza que va del lado extremo izquierdo.
        fscanf(entrada, "%d %d", &inicial.izq, &inicial.der);
        //Lee la segunda pieza de lado extremo derecho.
        fscanf(entrada, "%d %d", &final.izq, &final.der);
        //Lee las m piezas.
        for (int i = 0; i < m_piezas; i++) {
            fscanf(entrada, "%d %d", &disponibles[i].izq, &disponibles[i].der);
            usada[i] = 0; //0 para indicar que no han sido usadas.
        }
        //Inicializamos que la solución ha sido encontrada antes de buscarla.
        solucion_encontrada = 0;
        //Asignamos la pieza inicial para la validación en nuestra búsqueda.
        tablero[0] = inicial;
        //Backtracking.
        buscar_conjunto_de_piezas(1);
        //Se escribe en el archivo de salida en el formato específicado.
        if(solucion_encontrada){
            //Para cuando la solución fue hallada.
            fprintf(salida, "YES\n");
        }else{
            //Para cuando la solución no es hallada.
            fprintf(salida, "NO\n");
        }
    }//Y se repite el ciclo si todavia quedan más juegos de domino solitario.
    //Para cerrar los archivos.
    fclose(entrada);
    fclose(salida);
    //Verifica que el programa ha terminado exitosamente.
    return 0;
}
//Función de backtracking que intenta conectar todas las posibilidades de piezas para encontrar una solución.
void buscar_conjunto_de_piezas(int paso) {
    //Paso final, verifica que el último espacio con una pieza coincida con 
    if (paso > n_espacios) {
        // Verificamos si la última pieza colocada conecta con la pieza FINAL
        if (tablero[n_espacios].der == final.izq) {
            solucion_encontrada = 1;
        }
        return;
    }

    // Intentar con cada una de las M piezas
    for (int i = 0; i < m_piezas && !solucion_encontrada; i++) {
        if (!usada[i]) {
            
            // Probar pieza original y girada
            pieza_domino p_actual = disponibles[i];
            
            for (int giro = 0; giro < 2 && !solucion_encontrada; giro++) {
                if (giro == 1) { // Rotar: [2|5] -> [5|2]
                    int temp = p_actual.izq;
                    p_actual.izq = p_actual.der;
                    p_actual.der = temp;
                }

                if (es_valida(p_actual, paso)) {
                    tablero[paso] = p_actual; // Almacenar paso
                    usada[i] = 1;

                    buscar(paso + 1); // Llamada recursiva

                    if (!solucion_encontrada) {
                        usada[i] = 0; // Borrar paso (Backtracking)
                    }
                }
            }
        }
    }
}

int es_valida(pieza_domino p, int paso) {
    // Es válida si su izquierda conecta con la derecha de la pieza anterior en el tablero
    return (p.izq == tablero[paso - 1].der);
}