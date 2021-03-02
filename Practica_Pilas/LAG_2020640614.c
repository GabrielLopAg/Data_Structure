#include "LAG_2020640614.h"
// infija: (x+z)*w/t^y-v   postfija: {x z + w * t y ^ / v -}

int main() {
	Nodo *pila;
	pila = NULL;
    char ruta[20] = "";

	printf("\nPrograma para realizar el cambio de notacion de infija a postfija.\n\n");

	printf("Ingresa el nombre del archivo a leer: ");
    scanf("%s", ruta);

	pila = sufija(pila, ruta);

	printf("\n\nRealizando el cambio de notacion...\n\n");

    printf("\nCambio realizado.\n\n");
    mostrarArchivo();

    printf("\n\nRevisar el archivo postfija.txt\n\n");

	return 0;
}
