#include "tetris.h"

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
    p->tetromino=crearMatriz(4,4);
    cargaPieza(p);

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
void cargaPieza(PiezaActual *p)
{
    char **aux=p->tetromino;
    char *auxFila;
    int i,j;
    int pieza_I[4][4] =
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    };
    int pieza_J[4][4] =
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    int pieza_L[4][4] =
    {
        {0,0,0,1},
        {0,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    };
    int pieza_O[4][4] =
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    int pieza_S[4][4] =
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    int pieza_T[4][4] =
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    int pieza_Z[4][4] =
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    switch(p->tipo)
    {
    case 'I':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_I[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='I';
                }
            }
            aux++;
        }
        break;
    case 'J':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_J[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='J';
                }
            }
            aux++;
        }
        break;
    case 'L':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_L[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='L';
                }
            }
            aux++;
        }
        break;
    case 'O':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_O[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='O';
                }
            }
            aux++;
        }
        break;
    case 'S':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_S[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='S';
                }
            }
            aux++;
        }
        break;
    case 'T':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_T[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='T';
                }
            }
            aux++;
        }
        break;
    case 'Z':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_Z[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='Z';
                }
            }
            aux++;
        }
        break;
    }
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
    char** aux=p->tetromino;
    char*auxFila;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            auxFila=(*aux)+j;
            if(*auxFila==p->tipo)
            {
                nuevaFila = (p->fila + i) + 1;
                nuevaCol  = (p->columna + j);

                // piso
                if(nuevaFila >= t->filasTotales)
                    return 0;

                // colisi�n con bloque fijo
                if(t->celdas[nuevaFila][nuevaCol] != '.')
                    return 0;
            }
        }
        aux++;
    }
    return 1;
}
void fijarPieza(Tablero *tablero, PiezaActual *p)
{
    int i,j,Fila,Col;
    char** aux=p->tetromino;
    char*auxFila;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            auxFila=(*aux)+j;
            if(*auxFila==p->tipo)
            {
                Fila = (p->fila + i);
                Col  = (p->columna + j);
                tablero->celdas[Fila][Col]= p->tipo;
            }
        }
        aux++;
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
            if(piezaOcupaCelda(p,i,j)==p->tipo)
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
char piezaOcupaCelda(PiezaActual *p, int filaActual, int columnaActual)
{
    int filaRelativa;
    int columnaRelativa;
    char** aux;
    char* auxFila;

    // Verificar si la celda est� dentro del �rea 4x4 de la pieza
    if(filaActual < p->fila || filaActual >= p->fila + 4)
        return 0;

    if(columnaActual < p->columna || columnaActual >= p->columna + 4)
        return 0;

    // Convertir coordenadas del tablero a coordenadas relativas
    filaRelativa = filaActual - p->fila;
    columnaRelativa = columnaActual - p->columna;

    // Verificar si la pieza tiene bloque en esa posici�n
    aux=(p->tetromino)+filaRelativa;
    auxFila=*(aux)+columnaRelativa;
    return (*auxFila);
}

int puedeMover(PiezaActual *p, int tecla,Tablero* t)
{
    int nuevaCol, nuevaFila,i,j;
    char** aux=p->tetromino;
    char*auxFila;
    if(tecla == 'a')
    {
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                auxFila=(*aux)+j;
                if(*auxFila==p->tipo)
                {
                    nuevaFila = (p->fila + i);
                    nuevaCol  = (p->columna + j)-1;

                    // se nos va
                    if(nuevaCol < 0)
                        return 0;

                    // colisi�n con bloque fijo
                    if(t->celdas[nuevaFila][nuevaCol] != '.')
                        return 0;
                }
            }
            aux++;
        }
    }
    else if(tecla == 'd')
    {
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                auxFila=(*aux)+j;
                if(*auxFila==p->tipo)
                {
                    nuevaFila = (p->fila + i);
                    nuevaCol  = (p->columna + j)+1;

                    // se nos va
                    if(nuevaCol > CLASICO_COLUMNAS)
                        return 0;

                    // colisi�n con bloque fijo
                    if(t->celdas[nuevaFila][nuevaCol] != '.')
                        return 0;
                }
            }
            aux++;
        }
    }
    else
    {
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                auxFila=(*aux)+j;
                if(*auxFila==p->tipo)
                {
                    nuevaFila = (p->fila + i)+1;
                    nuevaCol  = (p->columna + j);

                    // se nos va
                    if(nuevaFila > CLASICO_FILAS_VISIBLES)
                        return 0;

                    // colisi�n con bloque fijo
                    if(t->celdas[nuevaFila][nuevaCol] != '.')
                        return 0;
                }
            }
            aux++;
        }
    }

    return 1;
}
int puedeRotar(int nuevaFila, int nuevaCol, int fila, int col,Tablero *t)
{
    // se nos va
    if(nuevaFila > CLASICO_FILAS_VISIBLES)
        return 0;

    // colisi�n con bloque fijo
    if(t->celdas[nuevaFila][nuevaCol] != '.')
        return 0;

    return 1;
}
int rotar(PiezaActual *p, int tecla,Tablero* t)
{
    int nuevaCol, nuevaFila,i,j;
    char temp[4][4];
    char** aux=p->tetromino;
    char*auxFila;
    if(p->tipo=='O')
        return 0;
    if(tecla=='X')
    {
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                auxFila=(*aux)+j;
                if(*auxFila==p->tipo)
                {
                    nuevaFila = j;
                    nuevaCol = 3 - i;
                    temp[nuevaFila][nuevaCol]=p->tipo;

                    if(!puedeRotar(nuevaFila,nuevaCol,i,j,t))
                        return 0;
                }
                else
                {
                    temp[i][j]='.';
                }
            }
            aux++;
        }
        aux=p->tetromino;
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                auxFila=(*aux)+j;
                *auxFila=temp[i][j];
            }
            aux++;
        }
    }
    else
    {
       for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                auxFila=(*aux)+j;
                if(*auxFila==p->tipo)
                {
                    nuevaFila = j;
                    nuevaCol = 3 - i;
                    temp[nuevaFila][nuevaCol]=p->tipo;

                    if(!puedeRotar(nuevaFila,nuevaCol,i,j,t))
                        return 0;
                }
                else
                {
                    temp[i][j]='.';
                }
            }
            aux++;
        }
        aux=p->tetromino;
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                auxFila=(*aux)+j;
                *auxFila=temp[i][j];
            }
            aux++;
        }
    }

    return 1;

}
