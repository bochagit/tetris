#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED

#include "GBT/gbt.h"
#include "tablero.h"

#define ANCHO_VENTANA 80
#define ALTO_VENTANA 120
#define ESCALA_VENTANA 5

#define CANT_COLORES 8

#define PAL_FONDO 0
#define PAL_I 1
#define PAL_J 2
#define PAL_L 3
#define PAL_O 4
#define PAL_S 5
#define PAL_T 6
#define PAL_Z 7

#define PIXELES_CELDA 4
#define PX_PADDING 1

int graficosIniciar(void);
void graficosCerrar(void);

void graficosComenzarFrame(void);
void graficosPresentarFrame(void);

void graficosDibujarTablero(const Tablero* tablero, const PiezaActual* pieza);

#endif // GRAFICOS_H_INCLUDED
