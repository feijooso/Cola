#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void destruir_dato(void* dato){

	free(dato);
}

void prueba_cola_vacia(){

	cola_t *cola = cola_crear();

	printf("PRUEBAS CON COLA VACIA\n");

	print_test("La cola fue creada", cola != NULL);
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	print_test("Intento desencolar", cola_desencolar(cola) == NULL);
	print_test("Intento ver el primer elemento",cola_ver_primero(cola) == NULL);
	free(cola);

}

void prueba_cola_con_elementos(){

	cola_t *cola = cola_crear();

	printf("PRUEBAS DE ENCOLAR\n");

	int a = 2;
	print_test("Se encolo un elemento de tipo int", cola_encolar(cola, &a));
	print_test("Veo el primer nodo", cola_ver_primero(cola) == &a);
	char b = 'b';
	print_test("Se encolo un elemento de tipo char", cola_encolar(cola, &b));
	print_test("Veo el primer nodo", cola_ver_primero(cola) == &a);
	int c = 10;
	print_test("Se encolo un elemento de tipo int",cola_encolar(cola, &c));
	print_test("Veo el primer nodo", cola_ver_primero(cola) == &a);
	

	printf("PRUEBAS DE DESENCOLAR\n");

	print_test("Se desencolo el primer nodo", cola_desencolar(cola));
	print_test("Veo el nuevo primer nodo", cola_ver_primero(cola) == &b);
	print_test("Se desencolo el primer nodo", cola_desencolar(cola));
	print_test("Veo el nuevo primer nodo", cola_ver_primero(cola) == &c);
	print_test("Se desencolo el primer nodo", cola_desencolar(cola));
	print_test("La cola esta vacia", cola_esta_vacia(cola));

	printf("PRUEBAS DE DESTRUIR COLA SIN DESTRUIR DATO\n");

	print_test("Se encolo un elemento de tipo int", cola_encolar(cola, &a));
	print_test("Se encolo un elemento de tipo int", cola_encolar(cola, &a));
	print_test("Se encolo un elemento de tipo int", cola_encolar(cola, &a));
	cola_destruir(cola, NULL);
	print_test("Se destruyo la cola", true);

	cola_t* cola1 = cola_crear();

	printf("PRUEBAS DE DESTRUIR COLA CON DESTRUIR DATO\n");

	int* vector1 = malloc(5 * sizeof(int));
	int* vector2 = malloc(4 * sizeof(int));
	int* vector3 = malloc(10 * sizeof(int));
	print_test("Se encolo un vector de int", cola_encolar(cola1, vector1));
	print_test("Se encolo un vector de int", cola_encolar(cola1, vector2));
	print_test("Se encolo un vector de int", cola_encolar(cola1, vector3));

	cola_destruir(cola1, destruir_dato);
	print_test("Se destruyo la cola", true);
}

void prueba_cola_volumen(int volumen){

	cola_t *cola = cola_crear();

	printf("PRUEBAS VOLUMEN\n");

	int* vector = malloc(volumen * sizeof(int));

    bool ok = true; 
    for(int i = 0; i < volumen; i++) {
    	vector[i] = i;
    	ok &= cola_encolar(cola, &vector[i]);
    }
    print_test("Se encolaron todos los elementos", ok);

    ok = true;

    for(int i = 0; i < volumen; i++) {
    	ok &= (cola_ver_primero(cola) == cola_desencolar(cola));
    }
    print_test("Se desapilaron todos los elementos", ok);

    free(vector);
    free(cola);
}




void pruebas_cola_alumno() {

	prueba_cola_vacia();
	prueba_cola_con_elementos();
	prueba_cola_volumen(100);

}

