#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#define TETRIS_FILAS_VISIBLES 20
#define TETRIS_FILAS_OCULTAS 4
#define TETRIS_FILAS_TOTALES (TETRIS_FILAS_VISIBLES + TETRIS_FILAS_OCULTAS)
#define TETRIS_COLUMNAS 10
#define TAM_PIEZA 4

typedef struct {
  int filasVisibles;
  int filasOcultas;
  int columnas;
  char** celdas;
} Tablero;

#endif // TETRIS_H_INCLUDED
