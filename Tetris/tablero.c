#include "tablero.h"

Tablero *tablero_crear(void){
  Tablero *t = malloc(sizeof(Tablero));
  if (!t) return NULL;

  t->filasVisibles = CLASICO_FILAS_VISIBLES;
  t->filasOcultas = CLASICO_FILAS_OCULTAS;
  t->filasTotales = t->filasOcultas + t->filasVisibles;
  t->columnas = CLASICO_COLUMNAS;

  t->celdas = crearMatriz(t->filasTotales, t->columnas);
  if (!t->celdas){
    free(t);
    return NULL;
  }

  cargaMatriz(t->celdas, t->filasTotales, t->columnas, CELDA_VACIA);

  return t;
}

void tablero_destruir(Tablero *tablero){
  if (!tablero) return;
  if (tablero->celdas) destruyeMatriz(tablero->celdas, tablero->filasTotales);
  free(tablero);
}

bool tablero_vaciar(Tablero *tablero){
  if (!tablero || !tablero->celdas) return false;
  return cargaMatriz(tablero->celdas, tablero->filasTotales, tablero->columnas, CELDA_VACIA);
}

void tablero_mostrar(const Tablero *tablero){
  if (!tablero || !tablero->celdas){
    printf("Tablero no inicializado\n");
    return;
  }

  int ini = tablero->filasOcultas;
  int fin = tablero->filasOcultas + tablero->filasVisibles;

  for (int i = ini; i < fin; i++){
    for (int j = 0; j < tablero->columnas; j++){
      putchar(tablero->celdas[i][j]);
      putchar(' ');
    }
    printf("%d", (i - (tablero->filasOcultas - 1))); // debug
    putchar('\n');
  }
}
