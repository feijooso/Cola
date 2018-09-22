#include "cola.h"
#include <stdlib.h>

typedef struct nodo {
	void* dato;
	struct nodo* prox;
} nodo_t;

struct cola {
	nodo_t* primero;
	nodo_t* ultimo;
	size_t tam;
};

/* *****************************************************************
 *                    AUXILIARES DE LA COLA
 * *****************************************************************/

nodo_t* nodo_crear(void* valor) {

	nodo_t* nodo = malloc(sizeof(nodo_t));

	if (nodo == NULL) return NULL;

	nodo->dato = valor;
	nodo->prox = NULL;

	return nodo;
}



/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void) {

	cola_t* cola = malloc(sizeof(cola_t));

	if (cola == NULL) return NULL;
	

	cola->primero = NULL;
	cola->ultimo = NULL;
	cola->tam = 0;

	return cola;
}

bool cola_esta_vacia(const cola_t *cola) {

	if (cola->tam == 0) return true;
	return false;
}

void* cola_ver_primero(const cola_t *cola) {

	if (cola_esta_vacia(cola)) return NULL;

	return cola->primero->dato;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {

	size_t tam = cola->tam;
	for(int i = 0; i < tam; i++) {

		void* valor = cola_desencolar(cola);

		if (destruir_dato != NULL) destruir_dato(valor);
		
	}

	free(cola);
}

bool cola_encolar(cola_t *cola, void* valor) {

	nodo_t* nodo_nuevo = nodo_crear(valor);

	if (nodo_nuevo == NULL) return false;

	if (cola_esta_vacia(cola)) {

		cola->ultimo = nodo_nuevo;
		cola->primero = nodo_nuevo;
	} else {

		cola->ultimo->prox = nodo_nuevo;
		cola->ultimo = nodo_nuevo;
	}

	cola->tam ++;
	return true;
}

void* cola_desencolar(cola_t *cola){

	if (cola_esta_vacia(cola)) return NULL;

	void* valor = cola_ver_primero(cola);
	void* nodo = cola->primero;
	cola->primero = cola->primero->prox;

	free(nodo);
	cola->tam--;
	return valor;
}