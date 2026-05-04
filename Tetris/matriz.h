#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char** crearMatriz(int cantFilas, int cantColumnas);
bool destruyeMatriz(char **mat, int cantFilas);
bool cargaMatriz(char **mat, int cantFilas, int cantColumnas, char relleno);
// void mostrarMatriz(char **mat, int cantFilas, int cantColumnas);
#endif // MATRIZ_H_INCLUDED
