#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifndef _PILA_
#define _PILA_

typedef struct _Nodo {
	char operador;
	struct _Nodo *siguiente;
}Nodo;

Nodo *asignarMemoria(char op) {
	Nodo *nuevo;
	nuevo = (Nodo *) malloc(sizeof(Nodo));
	nuevo -> operador = op;
	nuevo -> siguiente = NULL;

	return nuevo;
}

Nodo *push(Nodo *top, char op) {
	Nodo *nuevo;
	nuevo = asignarMemoria(op);
	if(top != NULL) {
		nuevo -> siguiente = top;
	}

	return nuevo;
}

Nodo *pop(Nodo *top) {
	Nodo *aux;
	aux = top;
	if(top != NULL) {
		top = top -> siguiente;
		free(aux);
	}

	return top;
}

int prioridad(char a, char b) {
	int precedencia[6];
	int x;

	precedencia['+'] = 2;
	precedencia['-'] = 2;
	precedencia['*'] = 3;
	precedencia['/'] = 3;
	precedencia['^'] = 4;
    precedencia['('] = 1;

	if(precedencia[a] > precedencia[b]) {
		x = 1; // falso = 0  true = 1
	}
	if(precedencia[a] <= precedencia[b]) {
		x = 0;
	}

	return x;
}

Nodo *sufija(Nodo *top, char *ruta) {
	FILE *archivo;
	int i;
	char expresion[20];
	char sufija[20] = "";

	archivo = fopen(ruta, "r");
	if(archivo == NULL) {
        printf("El archivo no existe...\n");
        exit(-1);
	} else {
        if(fgets(expresion, 20, archivo) != NULL) {
            printf("\n\nExpresion infija: %s\n", expresion);
		}
		fclose(archivo);
	}

	for(i = 0 ; i < strlen(expresion) ; i++) {
		if(ispunct(expresion[i])) { // SI ES OPERADOR
			if(top == NULL) { // Si la PILA esta vacia
				top = push(top, expresion[i]);
			}
			else {	// si la pila no esta vacia
                int a = prioridad(expresion[i], top -> operador);
				if(a == 1 && expresion[i] != ')') { // si el operador es mayor apilarlo
					top = push(top, expresion[i]);
				}
				if(a == 0 && top -> operador != '(') { // Si menor o igual se saca de la pila
                    if(expresion[i] == '(') {
                        top = push(top, expresion[i]);
                       } else {
                            while(top != NULL) {
                                if(top -> operador == '(') {
                                    break;
                                } else {
                                    sufija[strlen(sufija)] = top -> operador;
                                    top = pop(top);
                                }
                            }
                            top = push(top, expresion[i]);
                       }
				}
				if(expresion[i] == ')') {
					while(top != NULL) {
						if(top -> operador == '(') {
							top = pop(top);
							break;
						} else {
							sufija[strlen(sufija)] = top -> operador;
							top = pop(top);
						}
					}
				}

			}
		}
		if(isalpha(expresion[i])) { // SI ES OPERANDO
			sufija[strlen(sufija)] = expresion[i];
		}
	}
	while(top != NULL) { // Al terminar de leer la expresion, sacar los elementos restantes de la pila
		sufija[strlen(sufija)] = top -> operador;
		top = pop(top);
	}

	archivo = fopen("postfija.txt", "w");
	if(archivo != NULL) {
		fputs(sufija, archivo);
	}
	fclose(archivo);

	return top;
}

void mostrarArchivo() {
    FILE *archivo;
    char cadena[20];
    archivo = fopen("postfija.txt", "r");
    if(archivo != NULL) {
        if(fgets(cadena, 20, archivo) != NULL) {
            printf("\nExpresion postfija: %s\n", cadena);
		}
		fclose(archivo);
    }
}

#endif
