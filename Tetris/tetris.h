#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char**crearMatriz(int cantFilas, int cantColumnas);
bool destruyeMatriz(char **mat, int cantFilas);
bool cargaMatriz(char **mat, int cantFilas, int cantColumnas);
void mostrarMatriz(char **mat, int cantFilas, int cantColumnas);
#endif // TETRIS_H_INCLUDED
