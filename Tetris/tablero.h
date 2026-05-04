#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "tetris.h"
#include "matriz.h"
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

Tablero *tablero_crear(void);
void tablero_destruir(Tablero *tablero);
bool tablero_vaciar(Tablero *tablero);
void tablero_mostrar(const Tablero *tablero);

#endif // TABLERO_H_INCLUDED
