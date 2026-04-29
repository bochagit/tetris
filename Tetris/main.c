/*
Integrantes del equipo:

Apellido: Morales Pessacq, Bruno
DNI: 44834035
Usuario: BrunoMoralesP
Entrega: Sí

Apellido: Cardozo, Gonzalo Daniel
DNI: 43777470
Usuario: bochagit
Entrega: Sí
*/

#include <stdio.h>
#include "tablero.h"

int main()
{
    Tablero *t = tablero_crear();
    if (!t){
        fprintf(stderr, "Error creando tablero\n");
        return 1;
    }

    tablero_mostrar(t);
    tablero_destruir(t);

    return 0;
}
