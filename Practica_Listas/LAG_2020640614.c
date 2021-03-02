#include "LAG_2020640614.h"

int main() {
    Nodo *lista;
    lista = NULL;
    char ruta[20];

    printf("\nPrograma para realizar el ordenamiento de autos, ");
    printf("mediante el metodo de Seleccion Directa");

    printf("\n\nIngrese el nombre del archivo a leer: ");
    scanf("%s", ruta);
    lista = leerArchivo(lista, ruta);

    printf("\nSe esta creando la lista de autos.\n");
    mostrar(lista);

    printf("\n\nOrdenando la lista.\n");
    ordenamiento(lista);
    mostrar(lista);

    printf("\n\nSe guardo la lista ordenada en el archivo XXX.txt");
    imprimirArchivo(lista);


    putchar('\n');
    return 0;
}
