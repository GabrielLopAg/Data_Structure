#include "LAG_2020640614.h"

int main() {
    Nodo *recepcion, *cobros, *depositos;
    recepcion = cobros = depositos = NULL;
    char ruta[20];
    int x;

    printf("Programa para realizar la simulacion de una fila de atencion a clientes.\n\n");

    printf("Ingresa la ruta del archivo a leer: ");
    scanf("%s", ruta);
    recepcion = leerArchivo(recepcion, ruta);

    printf("\nSe esta atendiendo a las personas en recepcion.\n\n");
    printf("Turnos asignados.\n");

    srand(time(NULL));
    while(recepcion != NULL) {
        x = rand() % 2;
        if(x == 0) { // cobros (0)
            cobros = insert(cobros, recepcion -> nombre, recepcion -> numCuenta, recepcion -> saldo);
            recepcion = delete(recepcion);}
        if(x == 1) { // depositos (1)
            depositos = insert(depositos, recepcion -> nombre, recepcion -> numCuenta, recepcion -> saldo);
            recepcion = delete(recepcion);
        }}

    printf("\nFila para realizar cobros.\n");
    printf("\nNOMBRE\tCUENTA\tSALDO");
    mostrarFila(cobros);

    printf("\n\nFila para realizar depositos.\n");
    printf("\nNOMBRE\tCUENTA\tSALDO");
    mostrarFila(depositos);


    imprimirArchivo(cobros, depositos);
    printf("\n\nRevisar los archivos de bitacora.\n");

    return 0;
}
