#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED

#include "GBT/gbt.h"
#include "tablero.h"

#define ANCHO_VENTANA 128
#define ALTO_VENTANA 128
#define ESCALA_VENTANA 5

int graficosIniciar(void);
void graficosCerrar(void);

void graficosDibujarTablero(const Tablero* tablero);

#endif // GRAFICOS_H_INCLUDED
