#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#define TAM_MAX 400

typedef struct _Nodo {
	char dato;
	int frecuencia;
	struct _Nodo *siguiente, *anterior;
	struct _Nodo *izquierda, *derecha;
}Nodo;

typedef struct _NodoLista {
	char dato;
	char codigo[15];
	struct _NodoLista *siguiente;
}NodoLista;

Nodo *asignarMemoria(char);
NodoLista *crearNodo(char, char*);
Nodo *insertFinal(Nodo*, char);
NodoLista *ingresarFinal(NodoLista*, char, char*);
int contarElementos(Nodo*);
void mostrar(Nodo*);
void ordenamiento(Nodo*);
Nodo *guardarEnLista(Nodo*, char);
Nodo *intercambiarCaracteres(Nodo*, char*);
char *leerFraseArchivo(char*);
char *fraseArreglada(char*);
void acomodar(Nodo*, Nodo*);
Nodo *insertNodo(Nodo*);
void imprimirArchivo(char, char*);
void obtenerBinario(Nodo*, int, char[]);
void binarioToDecimal(NodoLista*, char*);
void postOrder(Nodo*);
void imprimirLlave(Nodo*);

Nodo *asignarMemoria(char d) {
	Nodo *nuevo;
	nuevo = (Nodo *) malloc(sizeof(Nodo));
	nuevo -> dato = d;
	nuevo -> frecuencia = 1;
	nuevo -> siguiente = NULL;
    nuevo -> anterior = NULL;
    nuevo -> izquierda = NULL;
    nuevo -> derecha = NULL;
	return nuevo;
}

NodoLista *crearNodo(char d, char *c) {
	NodoLista *nuevo;
	nuevo = (NodoLista *) malloc(sizeof(Nodo));
	nuevo -> dato = d;
	strcpy(nuevo -> codigo, c);
	nuevo -> siguiente = NULL;
	return nuevo;
}

Nodo *insertFinal(Nodo *frente, char d) {
    Nodo *nuevo;
    Nodo *aux;
    nuevo = asignarMemoria(d);
    if(frente == NULL) {
        frente = nuevo;
    } else {
        aux = frente;
        while(aux -> siguiente != NULL) {
            aux = aux -> siguiente;
        }
        aux -> siguiente = nuevo;
        nuevo -> anterior = aux;
    }

    return frente;
}

NodoLista *ingresarFinal(NodoLista *frente, char d, char *c) {
    NodoLista *nuevo;
    NodoLista *aux;
    nuevo = crearNodo(d, c);
    if(frente == NULL) {
        frente = nuevo;
    } else {
        aux = frente;
        while(aux -> siguiente != NULL) {
            aux = aux -> siguiente;
        }
        aux -> siguiente = nuevo;
    }

    return frente;
}

int contarElementos(Nodo *frente) {
	int c = 0;
	if(frente == NULL) {
		//printf("\nLa FILA esta vacia...\n");
	} else {
		while(frente != NULL) {
			frente = frente -> siguiente;
			c++;
		}
	}
	return c;
}

void mostrar(Nodo *frente) {
    if(frente == NULL) {
        printf("\nLa FILA esta vacia...");
    } else {
        while(frente != NULL) {
            printf("\nDato: %c Fre: %d", frente->dato, frente->frecuencia);
            frente = frente -> siguiente;
        }
    }
}

/*void ordenamiento(Nodo* frente) { /// NO FUNCIONA BIEN (Selección Directa Estable)
    Nodo *temp = frente;
    Nodo *valorMin = NULL;
    Nodo *aux = NULL;

    while (temp) {
        valorMin = temp;
        aux = temp -> siguiente;
        while(aux) {
            if (valorMin -> frecuencia > aux -> frecuencia)
                valorMin = aux;

            aux = aux -> siguiente;
        }
        char caracter = valorMin -> dato;
        int f = valorMin -> frecuencia;

        while(valorMin > temp) {
            valorMin -> dato = valorMin -> anterior -> dato;
            valorMin -> frecuencia = valorMin -> anterior -> frecuencia;
            valorMin = valorMin -> anterior;
        }
        temp -> dato = caracter;
        temp -> frecuencia = f;
        temp = temp -> siguiente;
    }
}*/

// FUNCION QUE ORDENA LA LISTA RESPECTO AL NUMERO DE FRECUENCIA
void ordenamiento(Nodo *frente) {
    Nodo *aux = frente;
    Nodo *aux2 = NULL;
    int i, f;
    char caracter;
    int lenght = contarElementos(frente);

    for(i = 0 ; i < lenght ; i++) {
        aux2 = aux;
        caracter = aux2 -> dato;
        f = aux2 -> frecuencia;
        while(aux2->anterior != NULL && aux2->anterior->frecuencia > f) {
            aux2->frecuencia = aux2->anterior->frecuencia;
            aux2->dato = aux2->anterior->dato;
            aux2 = aux2->anterior;
        }
        aux2 -> frecuencia = f;
        aux2 -> dato = caracter;
        aux = aux -> siguiente;
    }
}

// FUNCION QUE GUARDA EN LA LISTA LOS CARACTERES DE LA FRASE SIN REPETIR
Nodo *guardarEnLista(Nodo *frente, char d) {
    Nodo *aux;
    int i, cont = 0, lenght = 0;
    lenght = contarElementos(frente);
    if(frente == NULL) {
        frente = insertFinal(frente, d);
    } else {
        aux = frente;
        for(i = 1 ; i <= lenght ; i++) {
            if(aux -> dato == d) {
                aux -> frecuencia += 1;
                cont++;
                break;
            } else {
                aux = aux -> siguiente;
            }
        }
        if(cont == 0)
            frente = insertFinal(frente, d);
    }

    return frente;
}

// FUNCION QUE LEE CADA CARACTER DE LA FRASE Y LOS CARACTERES ESPECIALES LOS CAMBIA A CARACTERES ESTANDAR
/*
    El codigo ascii se compone de los caracteres estandares y los caracteres extendibles, los caracteres estandares son de 1 byte (8 bits)
    y los extendibles de 2 bytes (16 bits), por tanto al momento de leer un caracter especial como por ejemplo 'á' transfomara el caracter a hexadecimal
    que seria c3a1 y como son dos bytes primero convierte el c3 a el complemento a 2 del decimal que seria -61 y  despues para el hexadecimal a1
    convierte el complemento a dos del decimal nos da -95, y asi para los demas caracteres decimales aplica lo mismo.
    http://www.utf8-chartable.de/
    https://es.stackoverflow.com/questions/61819/c%C3%B3mo-puedo-quitar-los-tildes-a-los-char-de-un-arreglo
*/
Nodo *intercambiarCaracteres(Nodo *frente, char *ruta) {
    int i;
    char *frase = leerFraseArchivo(ruta);
    printf("\nFrase leida: %s\n", frase);
    printf("\nCreando lista.");
    for(i = 0 ; i < strlen(frase) ; i++) {
        switch(frase[i]) {
            case -61: break;
            case -95:
            case -127:
                frente = guardarEnLista(frente, 'a'); break;
            case -87:
            case -119:
                frente = guardarEnLista(frente, 'e'); break;
            case -83:
            case -115:
                frente = guardarEnLista(frente, 'i'); break;
            case -77:
            case -109:
                frente = guardarEnLista(frente, 'o'); break;
            case -70:
            case -102:
                frente = guardarEnLista(frente, 'u'); break;
            case -79:
            case -111:
                frente = guardarEnLista(frente, 'n'); break;
            case 32:
                frente = guardarEnLista(frente, '_'); break;
            default:
                frente = guardarEnLista(frente, tolower(frase[i])); break;
        }
    }
    free(frase);
    mostrar(frente);
    printf("\n\nOrdenando lista.");
    ordenamiento(frente);
    return frente;
}

// EN ESTA FUNCION SE LEE EL ARCHIVO QUE CONTIENE LA FRASE INICIAL
char *leerFraseArchivo(char *ruta) {
    FILE *archivo;
    char *aux;
    char *frase = malloc(TAM_MAX);
    archivo = fopen(ruta, "r");
    if(archivo == NULL) {
        printf("Error al abrir el archivo...\n");
        exit(-1);
	} else {
        while(!feof(archivo)) {
            fgets(frase, TAM_MAX, archivo);
        }
        fclose(archivo);
    }
    return frase;
}

char *fraseArreglada(char *ruta) {
    int i;
    char *frase = leerFraseArchivo(ruta);

    for(i = 0 ; i < strlen(frase) ; i++) {
        switch(frase[i]) {
            case -61: break;
            case -95:
            case -127:
                frase[i] = 'a'; break;
            case -87:
            case -119:
                frase[i] = 'e'; break;
            case -83:
            case -115:
                frase[i] = 'i'; break;
            case -77:
            case -109:
                frase[i] = 'o'; break;
            case -70:
            case -102:
                frase[i] = 'u'; break;
            case -79:
            case -111:
                frase[i] = 'n'; break;
            case 32:
                frase[i] = '_'; break;
            default:
                frase[i] = tolower(frase[i]); break;
        }
    }
    return frase;
}

// ACOMODA EL NODO * EN LA LISTA CON RESPECTO AL NUMERO DE FRECUENCIA
void acomodar(Nodo *frente, Nodo *nodoInterior) {
    if(frente -> siguiente == NULL) {
        frente -> siguiente = nodoInterior;
        return;
    }
    while(frente -> siguiente != NULL) {
        if(frente -> siguiente -> frecuencia > nodoInterior -> frecuencia){
            break;
        }
        frente = frente -> siguiente;
        if(frente -> siguiente == NULL) {
            frente -> siguiente = nodoInterior;
            return;
        }
    }
    nodoInterior -> siguiente = frente -> siguiente;
    frente -> siguiente = nodoInterior;
}

// INSERTA NODO * EN LA LISTA
Nodo *insertNodo(Nodo *frente) {
    Nodo *nuevo, *raiz;

    while(frente != NULL) {
        nuevo = asignarMemoria('*');
        nuevo -> izquierda = frente;
        nuevo -> frecuencia = frente -> frecuencia;
        if(frente -> siguiente != NULL) {
            frente = frente -> siguiente;
            nuevo -> derecha = frente;
            nuevo -> frecuencia += frente -> frecuencia;
        }
        frente = frente -> siguiente;
        if(frente == NULL) {
            break;
        }
        if(nuevo -> frecuencia < frente -> frecuencia) {
            nuevo -> siguiente = frente;
            frente = nuevo;
        } else {
            acomodar(frente, nuevo);
        }
    }
    raiz = nuevo;

    return raiz;
}

void imprimirArchivo(char c, char *codigo) {
    FILE *archivo;
    archivo = fopen("codigos.txt", "a");
    if(archivo != NULL)
        fprintf(archivo, "%c %s\n", c, codigo);

    fclose(archivo);
}

void obtenerBinario(Nodo *arbol, int pos, char codigo[]) {
    int i;
    char aux[15] = "";
    if(arbol -> izquierda != NULL) {
        codigo[pos] = '0';
        obtenerBinario(arbol -> izquierda, pos+1, codigo);
    }
    if(arbol -> derecha != NULL) {
        codigo[pos] = '1';
        obtenerBinario(arbol -> derecha, pos+1, codigo);
    }
    if(arbol -> izquierda == NULL && arbol -> derecha == NULL) { // si es un nodo hoja
        for(i = 0 ; i < pos ; i++)
            aux[i] = codigo[i];

        imprimirArchivo(arbol -> dato, aux);
    }
}

void binarioToDecimal(NodoLista *lista, char *ruta) {
    FILE *f1;
    NodoLista *aux;
    char c, codigo[15], numBinarios[TAM_MAX] = ""; // EN EL ARREGLO 'CODIGO' GUARDO LOS CODIGOS DE CADA CARACTER
    int i = 0, resultado;

    f1 = fopen("codigos.txt", "r");
    if(f1 != NULL) {
        while(!feof(f1)) {
            fscanf(f1, "%c %s\n", &c, codigo);
            lista = ingresarFinal(lista, c, codigo); // AQUI HAGO UNA LISTA QUE GUARDA EL CARACTER Y EL CODIGO DEL CARACTER
        }
        fclose(f1);
    }

    char *frase = fraseArreglada(ruta);
    //printf("%s\n", frase); // imprimo: la_ruta_natural.
    while(frase[i]) {
        aux = lista;
        while(aux) {
            if(frase[i] == aux -> dato) {
                strcat(numBinarios, aux -> codigo);
                break;
            }
            else
                aux = aux -> siguiente;
        }
        i++;
    }

    int len = strlen(numBinarios);
    int decimal = 0, multiplicador = 1, j = 1, pos = 0, cont = 0;
    int *cadenaDecimales;   // EN 'cadenaDecimales' GUARDO EN UNA CADENA JUNTA LOS NUMEROS DECIMALES
    cadenaDecimales = (int *) malloc(TAM_MAX * sizeof(int));

    while((len % 7) != 0) {
        strcat(numBinarios, "0");
        len++;
    }
    for(i = len-1 ; i >= 0 ; i--, j++) {
        if(numBinarios[i] == '1') {
            decimal += multiplicador;
        }
        multiplicador *= 2;
        if(j == 7) {
            j = 0;
            multiplicador = 1;
            cadenaDecimales[pos] = decimal;
            pos++;
            decimal = 0;
        }
    }

    int copia[pos+1];
    copia[0] = pos; // 'pos' SERIA EL CONJUNTO DE 7 BITS
    for(i = pos-1, j = 1 ; i >= 0 ; i--, j++) {
        copia[j] = cadenaDecimales[i]; // INVIERTO LA CADENA DE DECIMALES
        //printf("%d ", copia[j]);
    }

    FILE *f2 = fopen("codigo.bin", "wb");;
    if(f2 != NULL) {
        resultado = fwrite(copia, sizeof(int), sizeof(copia)/sizeof(int), f2);
    }
    if(resultado != sizeof(copia)/sizeof(int))
        printf("No se han escrito todos los %d números del array.\n", sizeof(copia)/sizeof(int));

    fclose(f2);
    free(cadenaDecimales);
    free(frase);
}

void imprimirLlave(Nodo *raiz) {
    FILE *archivo;
    archivo = fopen("llave.txt", "a");
    if(archivo != NULL)
        fprintf(archivo, "%c %d ", raiz->dato, raiz->frecuencia);

    fclose(archivo);
}

void postOrder(Nodo *raiz) {
    if(raiz != NULL) {
        postOrder(raiz -> izquierda);
        postOrder(raiz -> derecha);
        //printf("%c %d ", raiz -> dato, raiz -> frecuencia);
        imprimirLlave(raiz);
    }
}

#endif
