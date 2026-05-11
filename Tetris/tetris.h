#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#define CLASICO_FILAS_VISIBLES 20
#define CLASICO_FILAS_OCULTAS 4
#define CLASICO_COLUMNAS 10
#define CELDA_VACIA '.'
#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#include <time.h>

typedef struct {
  int filasVisibles;
  int filasOcultas;
  int filasTotales;
  int columnas;
  char** celdas;
} Tablero;

typedef struct {
  char tipo;     // I, J, L, O, S, T, Z
  int fila;
  int columna;
  char** tetromino;
} PiezaActual;


void mezclarBolsa(char* bolsa, int n);
void mostrarBolsa(char* bolsa, int n);
int crearNuevaPieza(char* bolsa, int* indiceBolsa, PiezaActual *p, Tablero * t);
char siguientePieza(char* bolsa, int* indiceBolsa);
void cargaPieza(PiezaActual *p);
int actualizarJuego(Tablero *tablero,char* bolsa, int* indiceBolsa,PiezaActual* p, int * puntaje);
void fijarPieza(Tablero *tablero, PiezaActual *p);
void render(Tablero *tablero, PiezaActual *p);
char piezaOcupaCelda(const PiezaActual *p, int filaActual, int columnaActual);
bool puedeMover(PiezaActual *p, int dx, int dy, Tablero* t);
bool puedeRotar(PiezaActual* p, char temp[4][4], Tablero* t);
int rotar(PiezaActual *p, int tecla,Tablero* t);
int evaluarFilas(Tablero *tablero);
int analizaLinea(char* fila, int columnas);
void limpiaLinea(char* fila, int columnas);
void actualizarPuntaje(int * puntaje,int lineas);

#endif // TETRIS_H_INCLUDED
