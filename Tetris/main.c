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
#include <stdbool.h>
#include "tablero.h"
#include "graficos.h"

int main()
{
    srand(time(NULL));
    char bolsa_actual[]={'I','J','L','O','S','T','Z'};
    int indice=0;
    Tablero *t = tablero_crear();
    if (!t)
    {
        fprintf(stderr, "Error creando tablero\n");
        return 1;
    }
    PiezaActual p;
    p.tetromino = NULL;
    crearNuevaPieza(bolsa_actual,&indice,&p);
    // while(1)
    // {
    //     if(kbhit())
    //     {
    //         tecla = getch();
    //         if(tecla == 27)   // ESC
    //             break;

    //         if(tecla == 'a')
    //         {
    //             if(puedeMover(&p,tecla,t))
    //                 p.columna--;

    //         }

    //         if(tecla == 'd')
    //         {
    //             if(puedeMover(&p,tecla,t))
    //                 p.columna++;
    //         }

    //         if(tecla == 's')
    //         {
    //             if(puedeMover(&p,tecla,t))
    //                 p.fila++;
    //         }
    //         if(tecla == 'x')
    //         {
    //             rotar(&p,tecla,t);
    //         }
    //         if(tecla == 'z')
    //         {
    //             rotar(&p,tecla,t);
    //         }


    //     }

    //     system("cls");
    //     actualizarJuego(t,bolsa_actual,&indice,&p);
    //     render(t,&p);

    //     Sleep(200); // un sleep para que no vaya todo rapido

    // }

    if (graficosIniciar() != 0){
        tablero_destruir(t);
        return 1;
    }

    bool corriendo = true;

    while (corriendo){
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) corriendo = false;

        if (gbt_tecla_sostenida(GBTK_a)){
            if (puedeMover(&p, -1, 0, t)) p.columna--;
        }

        if (gbt_tecla_sostenida(GBTK_d)){
            if (puedeMover(&p, 1, 0, t)) p.columna++;
        }

        if (gbt_tecla_sostenida(GBTK_s)){
            if (puedeMover(&p, 0, 1, t)) p.fila++;
        }

        if (gbt_tecla_presionada(GBTK_q)){
            rotar(&p, 0, t); // Rotar izq
        }

        if (gbt_tecla_presionada(GBTK_e)){
            rotar(&p, 1, t); // Rotar der
        }

        actualizarJuego(t, bolsa_actual, &indice, &p);

        graficosComenzarFrame();
        graficosDibujarTablero(t, &p);
        graficosPresentarFrame();

        gbt_esperar(200);
    }

    graficosCerrar();
    tablero_destruir(t);
    return 0;
}
