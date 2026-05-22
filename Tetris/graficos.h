#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED

#include "GBT/gbt.h"
#include "tablero.h"

#define CANT_COLORES 18

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

int graficosIniciar(const Pantalla* pant);
void graficosCerrar(void);

void graficosComenzarFrame(uint8_t color);
void graficosPresentarFrame(void);

void graficosDibujarTablero(const Pantalla* pant, const Tablero* tablero, const PiezaActual* pieza);
void graficosDibujarCelda(const Pantalla* pant, uint8_t color, uint16_t oX, uint16_t oY);
void graficosDibujarRect(int x, int y, int w, int h, uint8_t color);
void graficosDibujarBorde(int x, int y, int w, int h, uint8_t color, int grosor);
void graficosDibujarMenu(const Pantalla* pant);
void graficosDibujarJuego(const Pantalla* pant, const Tablero* t, const PiezaActual* p, int puntaje, int nivel, int lineasCompletas);
void graficosDibujarPausa(const Pantalla* pant);
void graficosDibujarGameOver(const Pantalla* pant);
void graficosConfigurarResolucion(Pantalla* pant, int res, int escala);

#endif // GRAFICOS_H_INCLUDED
