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

}

