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

typedef enum {
  ESTADO_MENU,
  ESTADO_CORRIENDO,
  ESTADO_PAUSA,
  ESTADO_GAMEOVER,
} EstadoJuego;


void mezclarBolsa(char* bolsa, int n);
void mostrarBolsa(char* bolsa, int n);
int crearNuevaPieza(char* bolsa, int* indiceBolsa, PiezaActual *p, Tablero * t);
char siguientePieza(char* bolsa, int* indiceBolsa);
void cargaPieza(PiezaActual *p);
void aplicarGravedad(Tablero *tablero,PiezaActual* p, int* lockDelay,int *gravedad, int velocidadCaida);
void fijarPieza(Tablero *tablero, PiezaActual *p);
void render(Tablero *tablero, PiezaActual *p);
char piezaOcupaCelda(const PiezaActual *p, int filaActual, int columnaActual);
bool puedeMover(PiezaActual *p, int dx, int dy, Tablero* t);
bool puedeRotar(PiezaActual *p, char temp[4][4], Tablero* t);
int rotar(PiezaActual *p, int tecla,Tablero* t);
int evaluarFilas(Tablero *tablero);
int analizaLinea(char* fila, int columnas);
void limpiaLinea(char* fila, int columnas);
void actualizarPuntaje(int * puntaje,int lineas);
int tetrominosObtieneUltimasFilas(int *ult);
void compactarFilas(Tablero *tablero, const int *filas, int cant);
int actualizarJuego(Tablero *tablero,char* bolsa, int* indiceBolsa,PiezaActual* p, int * puntaje, int* lockDelay);

#endif // TETRIS_H_INCLUDED
