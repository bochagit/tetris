#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED

#include "GBT/gbt.h"
#include "tablero.h"

#define CANT_COLORES 22

#define PAL_FONDO 0
#define PAL_I 1
#define PAL_J 2
#define PAL_L 3
#define PAL_O 4
#define PAL_S 5
#define PAL_T 6
#define PAL_Z 7
#define PAL_X 17
#define PAL_C 18
#define PAL_P 19
#define PAL_V 20
#define PAL_GHOST 9

#define PAL_REFLEJO 13

int graficosIniciar(const Pantalla* pant, int modo);
void graficosCerrar(void);

void graficosComenzarFrame(uint8_t color);
void graficosPresentarFrame(void);

void graficosDibujarTablero(const Pantalla* pant, const Tablero* tablero, const PiezaActual* pieza, int origenX, int origenY);
void graficosDibujarCelda(const Pantalla* pant, int origenX, int origenY, uint8_t color, uint16_t oX, uint16_t oY);
void graficosDibujarRect(int x, int y, int w, int h, uint8_t color);
void graficosDibujarBorde(int x, int y, int w, int h, uint8_t color, int grosor);
void graficosDibujarMenu(const Pantalla* pant, int modo, int opcionMenu, int totalOpciones);
void graficosDibujarJuego(const Pantalla* pant, const Tablero* t, const PiezaActual* p, int puntaje, int nivel, int lineasCompletas, const char user[4], char siguienteTipo, int modo);
void graficosDibujarPausa(const Pantalla* pant);
void graficosDibujarGameOver(const Pantalla* pant,Leaderboard *lb,int puntaje);
void graficosConfigurarResolucion(Pantalla* pant, int res, int escala);
void graficosDibujarConfig(const Pantalla* pant, const char user[4], int cursor, int configPaso, int modoSel, int velSel, int paletaSel, int resSel);
void graficosDibujarPreview(char tipo, int cx, int cy, int block, int pad, uint8_t color);
void graficosDibujarPanelIzq(int panelIzqX, int panelIzqY, int panelIzqW, int panelIzqH, int escalaFuente, int escalaCharTitulo, int gapEstadisticas, int gapTitulo, int puntaje, int nivel, int lineasCompletas, const char user[]);
void graficosDibujarPanelDerecho(int panelDerX, int panelDerY, int panelDerW, int panelDerH, char siguienteTipo, const Pantalla* pant);
void graficosDibujarPanelIzqGrande(int panelDerX, int panelDerY, int panelDerW, int panelDerH, char siguienteTipo, const Pantalla* pant, int puntaje, int nivel, int filasCompletas);
void graficosSetModo(int modo);
void graficosAplicarPaletaAntimateria(bool activaAntiMateria);

#endif // GRAFICOS_H_INCLUDED
