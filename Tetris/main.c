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
#include "graficos.h"

int main()
{
    Tablero *t = tablero_crear();
    if (!t){
        fprintf(stderr, "Error creando tablero\n");
        return 1;
    }

    tablero_mostrar(t);
    tablero_destruir(t);

    if (gbt_iniciar() != 0){
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    char nombreVentana[128];
    sprintf(nombreVentana, "Ventana %dx%d", ANCHO_VENTANA, ALTO_VENTANA);

    if (gbt_crear_ventana(nombreVentana, ANCHO_VENTANA, ALTO_VENTANA, ESCALA_VENTANA) != 0){
        fprintf(stderr, "Error al iniciar el modulo de graficos de GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    bool corriendo = true;

    while (corriendo){
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) corriendo = false;

        gbt_esperar(16);
    }

    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
