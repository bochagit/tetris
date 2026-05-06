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
    PiezaActual p;
    crearNuevaPieza(bolsa_actual,&indice,&p);
    while(1)
    {
        if(kbhit())
        {
            tecla = getch();
            if(tecla == 27)   // ESC
                break;

            if(tecla == 'a')
            {
                if(puedeMover(&p,tecla,t))
                    p.columna--;

            }

            if(tecla == 'd')
            {
                if(puedeMover(&p,tecla,t))
                    p.columna++;
            }

            if(tecla == 's')
            {
                if(puedeMover(&p,tecla,t))
                    p.fila++;
            }

        }




        system("cls");
        actualizarJuego(t,bolsa_actual,&indice,&p);
        render(t,&p);

        Sleep(200); // un sleep para que no vaya todo rapido

    }
    tablero_destruir(t);
    return 0;
}
