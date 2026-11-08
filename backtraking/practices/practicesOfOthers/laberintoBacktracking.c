#include <stdio.h>

//Definicion de estructuras.
typedef struct{
    int df, dc;
}Alternativa;
typedef struct{
    int row, col;
}Posicion;
//Laberinto.
#define FILAS 5
#define COLUMNAS 5
char laberinto[FILAS][COLUMNAS] = {
    {'S', ' ', '#', ' ', ' '},
    {'#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' '},
    {' ', '#', '#', '#', ' '},
    {' ', ' ', ' ', 'E', '#'}
};
//Matriz de visitados.
int visitado[FILAS][COLUMNAS];
//Opciones.
Alternativa alternativas[3];
//Posición inicial.
Posicion inicio;
//Variables.
int solucion_encontrada;
int i, j;
//Funciones.
void inicializar_visitado(int visitado[FILAS][COLUMNAS]);
void buscar_solucion(Posicion *paso);
void procesar_solucion();
int es_alternativa_valida(Posicion *siguiente);
int es_solucion(Posicion *siguiente);
void almacenar_paso(Posicion *siguiente);
void borrar_paso(Posicion *siguiente);
//Main.
int main(){
    inicializar_visitado(visitado);
    //izquierda
    alternativas[0].df = 0;
    alternativas[0].dc = -1;
    //adelante
    alternativas[1].df = -1;
    alternativas[1].dc = 0;
    //derecha
    alternativas[2].df = 0;
    alternativas[2].dc = 1;
    for(i=0; i<FILAS; i++){
        for(j=0; j<COLUMNAS; j++){
            if(laberinto[i][j]=='E'){
                inicio.row = i;
                inicio.col = j;
            }
        }
    }
    visitado[inicio.row][inicio.col] = 1;
    solucion_encontrada = 0;
    buscar_solucion(&inicio);
    if(solucion_encontrada){
        printf("Camino Encontrado.");
    }else{
        printf("Camino no encontrado.");
    }
    return 0;
}
//Prototipado.
void inicializar_visitado(int visitado[FILAS][COLUMNAS]){
    int i, j;
    for(i=0; i<FILAS; i++){
        for(j=0; j<COLUMNAS; j++){
            visitado[i][j] = 0;
        }
    }
}
void buscar_solucion(Posicion *inicio){
    int i = 0;
    while((i<=2)&&(!solucion_encontrada)){
        Posicion siguiente;
        siguiente.row = inicio->row + alternativas[i].df;
        siguiente.col = inicio->col + alternativas[i].dc;
        if(es_alternativa_valida(&siguiente)){
            almacenar_paso(&siguiente);
            if(es_solucion(&siguiente)){
                solucion_encontrada = 1;
                procesar_solucion();
            }else{
                buscar_solucion(&siguiente);
                if(!solucion_encontrada){
                    borrar_paso(&siguiente);
                }
            }
        }
        i++; 
    }
}
void procesar_solucion() {
    int i, j;
    printf("\n--- ¡CAMINO ENCONTRADO! ---\n");
    
    for(i = 0; i < FILAS; i++) {
        for(j = 0; j < COLUMNAS; j++) {
            // Si es el inicio o la salida, dejamos su letra original
            if (laberinto[i][j] == 'E' || laberinto[i][j] == 'S') {
                printf("%c ", laberinto[i][j]);
            } 
            // Si el algoritmo pasó por aquí y es parte de la solución
            else if (visitado[i][j] == 1) {
                printf(". "); // Marcamos el camino con un punto
            } 
            // Si no, imprimimos lo que había (muro o espacio vacío)
            else {
                printf("%c ", laberinto[i][j]);
            }
        }
        printf("\n"); // Salto de línea al terminar cada fila
    }
    printf("---------------------------\n");
}
int es_alternativa_valida(Posicion *siguiente){
    return ((siguiente->row>=0)&&(siguiente->row<FILAS)&&(siguiente->col>=0)&&(siguiente->col<COLUMNAS)&&(laberinto[siguiente->row][siguiente->col]!='#')&&(!visitado[siguiente->row][siguiente->col]));
}
int es_solucion(Posicion *siguiente){
    return(laberinto[siguiente->row][siguiente->col]=='S');
}
void almacenar_paso(Posicion *siguiente){
    visitado[siguiente->row][siguiente->col] = 1;
}
void borrar_paso(Posicion *siguiente){
    visitado[siguiente->row][siguiente->col] = 0;
}