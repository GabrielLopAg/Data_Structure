#include "2020640614_deco_LAG.h"

int main() {
    Nodo *lista = NULL;
    Nodo *arbol = NULL;
    char rutaLlave[15], rutaBin[15], *numBinarios;

    printf("Programa para realizar la decodificacion/descompresion de Huffman.\n");
    printf("\nIngresa la ruta del archivo llave: ");
    scanf("%s", rutaLlave);
    printf("\nIngresa la ruta del archivo binario: ");
    scanf("%s", rutaBin);

    printf("\nCreando lista.");
    lista = leerArchivoTxt(lista, rutaLlave);
    mostrar(lista);
    putchar('\n'); putchar('\n');
    system("pause");
    system("cls");

    printf("\nCreando arbol.\n");
    arbol = crearArbol(lista);
    printf("\nDecodificando la frase.\n");
    numBinarios = leerArchivoBin(rutaBin);
    decodificar(arbol, numBinarios);

    system("pause");
    system("cls");

    printf("\nDecodificacion/descompresion exitosa.\n");
    printf("\nRevisar el archivo generado.");

    free(numBinarios);
    putchar('\n'); putchar('\n');
    system("pause");
    return 0;
}
