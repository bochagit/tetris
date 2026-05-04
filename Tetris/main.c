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
    int tecla;
    char bolsa_actual[]={'I','J','L','O','S','T','Z'};
    int indice=0;
    Tablero *t = tablero_crear();
    if (!t)
    {
        fprintf(stderr, "Error creando tablero\n");
        return 1;
    }

    mezclarBolsa(bolsa_actual,(sizeof(bolsa_actual)/sizeof(bolsa_actual[0])));
    while(1)
    {
        if(kbhit())
        {
            tecla = getch();
            if(tecla == 27)   // ESC
                break;
        }





        system("cls");
        tablero_mostrar(t);
        mostrarBolsa(bolsa_actual,(sizeof(bolsa_actual)/sizeof(bolsa_actual[0])));
        indice++;
        if(indice==7)
        {
            mezclarBolsa(bolsa_actual,(sizeof(bolsa_actual)/sizeof(bolsa_actual[0])));
            indice=0;
        }
        Sleep(750); // un sleep para que no vaya todo rapido

    }
    tablero_destruir(t);
    return 0;
}
