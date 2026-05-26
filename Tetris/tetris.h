#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#define CLASICO_FILAS_VISIBLES 20
#define CLASICO_FILAS_OCULTAS 4
#define CLASICO_COLUMNAS 10
#define DELUXE_COLUMNAS_DIFICIL 8
#define DELUXE_COLUMNAS_FACIL 16
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
  char* actual;
  char* aux;
  int indice;
  char siguienteTipo;
  size_t tam;
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
void cargarBolsa(char *bolsa, int modo);
void inicializarBolsa(Bolsa* b,int modo);
int crearNuevaPieza(Bolsa* b, PiezaActual *p, Tablero * t, int modo);
char siguientePieza(Bolsa* bolsa,int modo);
void cargaPieza(PiezaActual *p);
void aplicarGravedad(Tablero *tablero,PiezaActual* p, int* lockDelay,int *gravedad, int velocidadCaida,int modo);
void fijarPieza(Tablero *tablero, PiezaActual *p,int modo);
bool puedeMover(PiezaActual *p, int dx, int dy, Tablero* t,int modo);
bool puedeRotar(PiezaActual *p, char temp[4][4], Tablero* t, int modo);
int rotar(PiezaActual *p, int tecla,Tablero* t, int modo);
int evaluarFilas(Tablero *tablero, char** filasCompletas);
int analizaLinea(char* fila, int columnas);
void limpiaLinea(char* fila, int columnas,char relleno);
void actualizarPuntaje(int * puntaje,int lineas);
int actualizarJuego(Tablero *tablero,Bolsa* b,PiezaActual* p, int * puntaje, int* lineasCompletas, int* lockDelay, int modo);
void calcularGhost(PiezaActual *p,Tablero *t, int modo);
void pintarFilasCompletas(Tablero *tablero, char **filasCompletas,int cantidadCompletas);
void filasCompletasEliminar(Tablero *tablero);
char piezaOcupaCelda(const PiezaActual *p,int filaTablero,int colTablero,int columnas);

#endif // TETRIS_H_INCLUDED
