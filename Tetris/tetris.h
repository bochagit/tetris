#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#define CLASICO_FILAS_VISIBLES 20
#define CLASICO_FILAS_OCULTAS 4
#define CLASICO_COLUMNAS 10
#define CELDA_VACIA '.'
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int filasVisibles;
  int filasOcultas;
  int filasTotales;
  int columnas;
  char** celdas;
} Tablero;
typedef struct {
  char tipo;     // I,J,L,O,S,T,Z
  int fila;
  int columna;
} PiezaActual;

extern int (*tetrominos[7])[4];

void mezclarBolsa(char* bolsa, int n);
void mostrarBolsa(char* bolsa, int n);
void crearNuevaPieza(char* bolsa, int* indiceBolsa, PiezaActual *p);
char siguientePieza(char* bolsa, int* indiceBolsa);
int tipoAIndice(char tipo);
void actualizarJuego(Tablero *tablero,char* bolsa, int* indiceBolsa,PiezaActual* p);
int puedeBajar(Tablero *tablero, PiezaActual *p);
void fijarPieza(Tablero *tablero, PiezaActual *p);

#endif // TETRIS_H_INCLUDED
