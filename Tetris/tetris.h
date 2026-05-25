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

//typedef struct{
//    Tablero *tablero;
//    PiezaActual *p;
//    char *bolsa;



//}Partida;

typedef struct {
  int anchoVentana;
  int altoVentana;
  int escala;
  int tableroOffsetX;
  int tableroOffsetY;
  int pixelesCelda;
  int pxPadding;
} Pantalla;

typedef struct {
  int filasVisibles;
  int filasOcultas;
  int filasTotales;
  int columnas;
  char** celdas;
  int LineasCompletas;
} Tablero;

typedef struct {
  char tipo;     // I, J, L, O, S, T, Z
  int fila;
  int columna;
  int GhostFila;
  char** tetromino;
} PiezaActual;

typedef struct {
  char actual[7];
  char aux[7];
  int indice;
  char siguienteTipo;
} Bolsa;

typedef enum {
  ESTADO_MENU,
  ESTADO_USER,
  ESTADO_CORRIENDO,
  ESTADO_PAUSA,
  ESTADO_GAMEOVER,
} EstadoJuego;


void mezclarBolsa(char* bolsa, int n);
void mostrarBolsa(char* bolsa, int n);
void copiarBolsa(char* destino, const char* origen, int n);
void inicializarBolsa(Bolsa* b);
int crearNuevaPieza(Bolsa* b, PiezaActual *p, Tablero * t);
char siguientePieza(Bolsa* bolsa);
void cargaPieza(PiezaActual *p);
void aplicarGravedad(Tablero *tablero,PiezaActual* p, int* lockDelay,int *gravedad, int velocidadCaida);
void fijarPieza(Tablero *tablero, PiezaActual *p);
void render(Tablero *tablero, PiezaActual *p);
char piezaOcupaCelda(const PiezaActual *p, int filaActual, int columnaActual);
bool puedeMover(PiezaActual *p, int dx, int dy, Tablero* t);
bool puedeRotar(PiezaActual *p, char temp[4][4], Tablero* t);
int rotar(PiezaActual *p, int tecla,Tablero* t);
int evaluarFilas(Tablero *tablero, char** filasCompletas);
int analizaLinea(char* fila, int columnas);
void limpiaLinea(char* fila, int columnas,char relleno);
void actualizarPuntaje(int * puntaje,int lineas);
int tetrominosObtieneUltimasFilas(int *ult);
void compactarFilas(Tablero *tablero, const int *filas, int cant);
int actualizarJuego(Tablero *tablero,Bolsa* b,PiezaActual* p, int * puntaje, int* lineasCompletas, int* lockDelay);
void calcularGhost(PiezaActual *p,Tablero *t);
void pintarFilasCompletas(Tablero *tablero, char **filasCompletas,int cantidadCompletas);
void filasCompletasEliminar(Tablero *tablero);

#endif // TETRIS_H_INCLUDED
