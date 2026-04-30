#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#define CLASICO_FILAS_VISIBLES 20
#define CLASICO_FILAS_OCULTAS 4
#define CLASICO_COLUMNAS 10
#define CELDA_VACIA '.'

typedef struct {
  int filasVisibles;
  int filasOcultas;
  int filasTotales;
  int columnas;
  char** celdas;
} Tablero;

#endif // TETRIS_H_INCLUDED
