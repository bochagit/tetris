#include "matriz.h"


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

int main()
{
    char **mat=crearMatriz(2, 2);
    if(!mat)
        printf("No se creo\n");
    else
        printf("Se creo\n");


    if(cargaMatriz(mat, 2, 2))
        printf("Cargo\n");
    else
        printf("No cargo\n");

    mostrarMatriz(mat, 2, 2);

    destruyeMatriz(mat, 2);
    return 0;
}
