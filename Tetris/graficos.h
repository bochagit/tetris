#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED

#include "GBT/gbt.h"
#include "tablero.h"

#define ANCHO_VENTANA 320
#define ALTO_VENTANA 200
#define ESCALA_VENTANA 3

#define TABLERO_OFFSET_X 120
#define TABLERO_OFFSET_Y 15

#define CANT_COLORES 17

#define PAL_FONDO 0
#define PAL_I 1
#define PAL_J 2
#define PAL_L 3
#define PAL_O 4
#define PAL_S 5
#define PAL_T 6
#define PAL_Z 7
#define PAL_GHOST 9

#define PAL_REFLEJO 13

#define PIXELES_CELDA 8
#define PX_PADDING 1

int graficosIniciar(void);
void graficosCerrar(void);

void graficosComenzarFrame(uint8_t color);
void graficosPresentarFrame(void);

void graficosDibujarTablero(const Tablero* tablero, const PiezaActual* pieza);
void graficosDibujarCelda(uint8_t color, uint16_t oX, uint16_t oY);
void graficosDibujarRect(int x, int y, int w, int h, uint8_t color);
void graficosDibujarBorde(int x, int y, int w, int h, uint8_t color, int grosor);
void graficosDibujarLayout(const Tablero *t);
void graficosDibujarMenu(void);
void graficosDibujarJuego(const Tablero *t, const PiezaActual *p, int puntaje);
void graficosDibujarPausa(void);
void graficosDibujarGameOver(void);

#endif // GRAFICOS_H_INCLUDED
