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
int crearNuevaPieza(char* bolsa, int* indiceBolsa, PiezaActual *p, Tablero * t,int modo)
{
    p->tipo = siguientePieza(bolsa, indiceBolsa);
    p->fila = 0;
    p->columna = (CLASICO_COLUMNAS / 2) - 2;
    if (p->tetromino) destruyeMatriz(p->tetromino, 4);
    p->tetromino = crearMatriz(4, 4);
    cargaMatriz(p->tetromino, 4, 4, '.');
    cargaPieza(p);
    if(puedeMover(p,0,CLASICO_FILAS_OCULTAS - 2,t,modo))
        return 0;
    else
        return 1;

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

void aplicarGravedad(Tablero *tablero,PiezaActual* p, int* lockDelay,int *gravedad, int velocidadCaida,int modo)
{
    int puedeBajar=puedeMover(p, 0, 1, tablero,modo);
    if((*gravedad)>=velocidadCaida && puedeBajar)
    {
        p->fila++;
        (*lockDelay)=0;
        (*gravedad)=0;
    }
    else if(!puedeBajar)
    {
        (*lockDelay)++;
    }


    return;
}

bool puedeMover(PiezaActual *p, int dx, int dy, Tablero* t,int modo){
    int i, j, nuevaFila, nuevaCol,colReal;

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if (p->tetromino[i][j] != p->tipo) continue;

            nuevaFila = p->fila + i + dy;
            nuevaCol  = p->columna + j + dx;

            // piso
            if(nuevaFila >= t->filasTotales) return false;


            if(modo==0)
            {
                // bordes
                if (nuevaCol < 0 || nuevaCol >= t->columnas) return false;

                // colision con bloque fijo
                if(t->celdas[nuevaFila][nuevaCol] != '.') return false;
            }


            //if(t->celdas[nuevaFila][nuevaCol] != '.' && modo == 0) return false;

            if(modo==1)
            {
                if(nuevaCol<0 || nuevaCol>(t->columnas-1))
                {
                    colReal = (nuevaCol + t->columnas) % t->columnas;
                    if(t->celdas[nuevaFila][colReal] != '.')
                    return false;
                }
                else if(t->celdas[nuevaFila][nuevaCol] != '.')
                {
                    return false;
                }

            }
        }
    }

    return true;
}
void fijarPieza(Tablero *tablero, PiezaActual *p, int modo)
{
    int i,j,Fila,Col,colReal;
    char** aux=p->tetromino;
    char*auxFila;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            auxFila=(*aux)+j;
            if(modo==0 && *auxFila==p->tipo)
            {
                Fila = (p->fila + i);
                Col  = (p->columna + j);
                tablero->celdas[Fila][Col]= p->tipo;
            }
            else if(modo==1 && *auxFila==p->tipo)
            {
                Col  = (p->columna + j);
                if(Col<0 || Col>(tablero->columnas-4))
                {
                    colReal = (p->columna + j + tablero->columnas) % tablero->columnas;
                    Fila = (p->fila + i);
                    tablero->celdas[Fila][colReal]= p->tipo;
                }
                else
                {
                    Fila = (p->fila + i);
                    Col  = (p->columna + j);
                    tablero->celdas[Fila][Col]= p->tipo;
                }
            }
        }
        aux++;
    }
}
bool puedeRotar(PiezaActual* p, char temp[4][4], Tablero* t){
    int i, j, nuevaFila, nuevaCol;

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(temp[i][j] != p->tipo) continue;

            nuevaFila = p->fila + i;
            nuevaCol = p->columna + j;

            // piso
            if(nuevaFila >= t->filasTotales) return false;

            // bordes
            if(nuevaCol < 0 || nuevaCol >= t->columnas) return false;

            // colisión con bloque fijo
            if(t->celdas[nuevaFila][nuevaCol] != '.') return false;
        }
    }

    return true;
}

int rotar(PiezaActual *p, int dir, Tablero* t)
{
    int i, j;
    char temp[4][4];

    if(!p || !p->tetromino || p->tipo=='O') return 0;

    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            temp[i][j] = '.';
        }
    }

    if (dir == 0){
        for (i = 0; i < 4; i++){
            for (j = 0; j < 4; j++){
                if (p->tetromino[j][3 - i] == p->tipo){
                    temp[i][j] = p->tipo;
                }
            }
        }
    } else if (dir == 1){
        for (i = 0; i < 4; i++){
            for (j = 0; j < 4; j++){
                if (p->tetromino[3 - j][i] == p->tipo){
                    temp[i][j] = p->tipo;
                }
            }
        }
    }

    if (!puedeRotar(p, temp, t)) return 0;

    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            p->tetromino[i][j] = temp[i][j];
        }
    }

    return 1;
}

int evaluarFilas(Tablero *tablero, char** filasCompletas)
{
    char** lectura=(tablero->celdas)+(tablero->filasTotales)-1;
    char** aux;

    int cantCompletas=0;
    int i;
    for(i=tablero->filasTotales-1;i>=tablero->filasOcultas;i--)
    {
        if(analizaLinea(*lectura,tablero->columnas))
        {
            aux=filasCompletas+cantCompletas;
            *aux=*lectura;
            cantCompletas++;
        }
        lectura--;
    }


    return cantCompletas;
}

int analizaLinea(char* fila, int columnas)
{
    int i;

    for(i = 0; i < columnas; i++)
    {
        if(*(fila + i) == '.')
            return 0;
    }

    return 1;
}
void limpiaLinea(char* fila, int columnas, char relleno)
{
    int i;

    for(i = 0; i < columnas; i++)
    {
        *(fila + i) = relleno;
    }
}
void actualizarPuntaje(int * puntaje,int lineas)
{
    switch(lineas)
    {
    case 1:
        *puntaje+=100;
        break;

    case 2:
        *puntaje+=300;
        break;

    case 3:
        *puntaje+=500;
        break;

    case 4:
        *puntaje+=700;
        break;

    default:
        break;

    }
}
int actualizarJuego(Tablero *tablero,char* bolsa, int* indiceBolsa,PiezaActual* p, int * puntaje, int* lineasCompletas, int* lockDelay,int modo)
{
    int lineas,gameOver=0;
    char** filasCompletas=malloc(sizeof(char*)*4);
    if(!filasCompletas)
        return -1;

    fijarPieza(tablero, p,modo);
    lineas=evaluarFilas(tablero,filasCompletas);
    if(lineas>0 && tablero->LineasCompletas==0)
    {
        pintarFilasCompletas(tablero,filasCompletas,lineas);
        actualizarPuntaje(puntaje,lineas);
        tablero->LineasCompletas=1;
        *lineasCompletas += lineas;
    }
    gameOver=crearNuevaPieza(bolsa,indiceBolsa,p,tablero,modo);
    (*lockDelay)=0;


    return gameOver;
}
void calcularGhost(PiezaActual *p,Tablero *t,int modo)
{
    int dy=0;
    while(puedeMover(p,0,dy,t,modo))
    {
        dy++;
    }
    p->GhostFila=dy+p->fila;
}
void pintarFilasCompletas(Tablero *tablero, char **filasCompletas,int cantidadCompletas)
{
    char *aux;
    for(int i=0;i<cantidadCompletas;i++)
    {
        aux=*(filasCompletas+i);
        limpiaLinea(aux,tablero->columnas,'#');
    }
}
void filasCompletasEliminar(Tablero *tablero)
{
    char** lectura=(tablero->celdas)+(tablero->filasTotales)-1;
    char** escritura=(tablero->celdas)+(tablero->filasTotales)-1;
    char** aux;
    char** filasCompletas=malloc(sizeof(char*)*4);
    if(!filasCompletas)
        return ;

    int cantCompletas=0;
    int i;
    for(i=tablero->filasTotales-1;i>=tablero->filasOcultas;i--)
    {
        if(analizaLinea(*lectura,tablero->columnas))
        {
            aux=filasCompletas+cantCompletas;
            *aux=*lectura;
            cantCompletas++;
        }
        else
        {
            (*escritura)=(*lectura);
            escritura--;
        }
        lectura--;
    }
    aux=filasCompletas;
    for(i = 0; i < cantCompletas; i++)
    {
        limpiaLinea(*aux,tablero->columnas,'.');
        *escritura=*aux;
        aux++;
        escritura--;
    }

}
char piezaOcupaCelda(const PiezaActual *p,int filaTablero,int colTablero,int columnas)
{
    int i, j;
    int filaReal;
    int colReal;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(p->tetromino[i][j] !=p->tipo)
                continue;

            filaReal = p->fila+i;

            colReal =(p->columna+j+columnas) % columnas;

            if(filaReal==filaTablero && colReal==colTablero)
            {
                return p->tipo;
            }
        }
    }

    return '.';
}
