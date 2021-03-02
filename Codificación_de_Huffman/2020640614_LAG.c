#include "2020640614_LAG.h"
/**
    En el bloc de notas utilice codificación UTF-8 para el cambio de caracteres
**/
int main() {
    remove("llave.txt");
    Nodo *lista = NULL;
    Nodo *arbol = NULL;
    NodoLista *lista2 = NULL;
    char ruta[20], codigo[10] = "";

    printf("Programa para realizar la codificacionfras/compresion de Huffman.");
    printf("\n\nIngrese el nombre del archivo a leer: ");
    scanf("%s", ruta);

    lista = intercambiarCaracteres(lista, ruta);
    mostrar(lista);
    printf("\n\nCreando el arbol.\n");
    arbol = insertNodo(lista);
    printf("\nGenerando los codigos de cada caracter.\n");

    obtenerBinario(arbol, 0, codigo);
    printf("\nCreando el archivo binario.\n");
    binarioToDecimal(lista2, ruta);
    printf("\nCreando el archivo llave.\n\n");
    postOrder(arbol);
    putchar('\n');

    system("pause");
    system("cls");

    printf("\nCodificacion/compresion exitosa.\n");
    printf("\nRevisar los archivos generados.");

    putchar('\n'); putchar('\n');
    remove("codigos.txt"); system("pause");
    return 0;
}
