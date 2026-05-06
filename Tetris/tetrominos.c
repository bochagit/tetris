#include "tetris.h"

int pieza_I[4][4] = {
  {0,0,0,0},
  {1,1,1,1},
  {0,0,0,0},
  {0,0,0,0}
};
int pieza_J[4][4] = {
  {1,0,0,0},
  {1,1,1,0},
  {0,0,0,0},
  {0,0,0,0}
};

int pieza_L[4][4] = {
  {0,0,0,1},
  {0,1,1,1},
  {0,0,0,0},
  {0,0,0,0}
};
int pieza_O[4][4] = {
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0},
  {0,0,0,0}
};
int pieza_S[4][4] = {
  {0,1,1,0},
  {1,1,0,0},
  {0,0,0,0},
  {0,0,0,0}
};
int pieza_T[4][4] = {
  {0,1,0,0},
  {1,1,1,0},
  {0,0,0,0},
  {0,0,0,0}
};
int pieza_Z[4][4] = {
  {1,1,0,0},
  {0,1,1,0},
  {0,0,0,0},
  {0,0,0,0}
};

int (*tetrominos[7])[4] = {
  pieza_I,
  pieza_J,
  pieza_L,
  pieza_O,
  pieza_S,
  pieza_T,
  pieza_Z
};

void mezclarBolsa(char* bolsa, int n)
{
    char aux;
    int i,j;
    for(i = n - 1; i > 0; i--)
    {
        j = rand() % i ;
        aux = *(bolsa+i);
        *(bolsa+i) = *(bolsa+j);
        *(bolsa+j) = aux;
    }
}
void mostrarBolsa(char* bolsa, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c ", bolsa[i]);
    }
    printf("\n");
}
void crearNuevaPieza(char* bolsa, int* indiceBolsa, PiezaActual *p)
{

    p->tipo=siguientePieza(bolsa, indiceBolsa);
    p->fila=0;
    p->columna=(CLASICO_COLUMNAS/2)-2;

}
char siguientePieza(char* bolsa, int* indiceBolsa)
{
    int pieza;
    if(*indiceBolsa == 0)
    {
        mezclarBolsa(bolsa, 7);
    }

    pieza = *(bolsa+(*indiceBolsa));
    (*indiceBolsa)++;

    if(*indiceBolsa == 7)
        *indiceBolsa = 0;

    return pieza;
}
int tipoAIndice(char tipo)
{
    switch(tipo)
    {
    case 'I':
        return 0;
    case 'J':
        return 1;
    case 'L':
        return 2;
    case 'O':
        return 3;
    case 'S':
        return 4;
    case 'T':
        return 5;
    case 'Z':
        return 6;
    }
    return -1;
}
void actualizarJuego(Tablero *tablero,char* bolsa, int* indiceBolsa,PiezaActual* p)
{
    if(puedeBajar(tablero, p))
    {
        p->fila++;
    }
    else
    {
        fijarPieza(tablero, p);
        crearNuevaPieza(bolsa,indiceBolsa,p);
    }
}

int puedeBajar(Tablero* t, PiezaActual *p)
{
    int i,j,nuevaFila,nuevaCol;
    int indice=tipoAIndice(p->tipo);
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(tetrominos[indice][i][j] == 1)
            {
                nuevaFila = (p->fila + i) + 1;
                nuevaCol  = (p->columna + j);

                // piso
                if(nuevaFila >= t->filasTotales)
                    return 0;

                // colisión con bloque fijo
                if(t->celdas[nuevaFila][nuevaCol] != '.')
                    return 0;
            }
        }
    }
    return 1;
}
void fijarPieza(Tablero *tablero, PiezaActual *p)
{
    int i,j,Fila,Col;
    int indice=tipoAIndice(p->tipo);
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(tetrominos[indice][i][j] == 1)
            {
                Fila = (p->fila + i);
                Col  = (p->columna + j);
                tablero->celdas[Fila][Col]='X';
            }
        }
    }
}
void render(Tablero *tablero, PiezaActual *p)
{
    int ini = tablero->filasOcultas;
    int fin = tablero->filasOcultas + tablero->filasVisibles;
    int i,j;
    for (i = ini; i < fin; i++)
    {
        for (j = 0; j < tablero->columnas; j++)
        {
            if(piezaOcupaCelda(p,i,j))
            {
                putchar('X');
                putchar(' ');
            }
            else
            {
                putchar(tablero->celdas[i][j]);
                putchar(' ');
            }
        }
        printf("%d", (i - (tablero->filasOcultas - 1))); // debug
        putchar('\n');
    }


}
int piezaOcupaCelda(PiezaActual *p, int filaActual, int columnaActual)
{
    int filaRelativa;
    int columnaRelativa;
    int idx;

    idx = tipoAIndice(p->tipo);

    // Verificar si la celda está dentro del área 4x4 de la pieza
    if(filaActual < p->fila || filaActual >= p->fila + 4)
        return 0;

    if(columnaActual < p->columna || columnaActual >= p->columna + 4)
        return 0;

    // Convertir coordenadas del tablero a coordenadas relativas
    filaRelativa = filaActual - p->fila;
    columnaRelativa = columnaActual - p->columna;

    // Verificar si la pieza tiene bloque en esa posición
    return tetrominos[idx][filaRelativa][columnaRelativa];
}
int puedeMover(PiezaActual *p, int tecla,Tablero* t)
{
    int nuevaCol, nuevaFila,i,j;
    int indice=tipoAIndice(p->tipo);
    if(tecla == 'a')
    {
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                if(tetrominos[indice][i][j] == 1)
                {
                    nuevaFila = (p->fila + i);
                    nuevaCol  = (p->columna + j)-1;

                    // se nos va
                    if(nuevaCol < 0)
                        return 0;

                    // colisión con bloque fijo
                    if(t->celdas[nuevaFila][nuevaCol] != '.')
                        return 0;
                }
            }
        }
    }
    else if(tecla == 'd')
    {
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                if(tetrominos[indice][i][j] == 1)
                {
                    nuevaFila = (p->fila + i);
                    nuevaCol  = (p->columna + j)+1;

                    // se nos va
                    if(nuevaCol > CLASICO_COLUMNAS)
                        return 0;

                    // colisión con bloque fijo
                    if(t->celdas[nuevaFila][nuevaCol] != '.')
                        return 0;
                }
            }
        }
    }
    else
    {
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                if(tetrominos[indice][i][j] == 1)
                {
                    nuevaFila = (p->fila + i)+1;
                    nuevaCol  = (p->columna + j);

                    // se nos va
                    if(nuevaFila > CLASICO_FILAS_VISIBLES)
                        return 0;

                    // colisión con bloque fijo
                    if(t->celdas[nuevaFila][nuevaCol] != '.')
                        return 0;
                }
            }
        }
    }

    return 1;
}
