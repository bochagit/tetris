#include "tetris.h"


/*
Integrantes del equipo:

Apellido:Morales Pessacq, Bruno
DNI:44834035
Usuario:BrunoMoralesP
Entrega:Sí


*/

int main()
{
    char **mat=crearMatriz(2,2);
    if(!mat)
        printf("No se creo\n");
    else
        printf("Se creo\n");


    if(cargaMatriz(mat,2,2))
        printf("cargo");
    else
        printf("no cargo");

    mostrarMatriz(mat,2,2);



    destruyeMatriz(mat,2);
    return 0;
}
