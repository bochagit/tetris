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
int crearNuevaPieza(char* bolsa, int* indiceBolsa, PiezaActual *p, Tablero * t)
{
    p->tipo = siguientePieza(bolsa, indiceBolsa);
    p->fila = 0;
    p->columna = (CLASICO_COLUMNAS / 2) - 2;
    if (p->tetromino) destruyeMatriz(p->tetromino, 4);
    p->tetromino = crearMatriz(4, 4);
    cargaMatriz(p->tetromino, 4, 4, '.');
    cargaPieza(p);
    if(puedeMover(p,0,1,t))
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

int actualizarJuego(Tablero *tablero,char* bolsa, int* indiceBolsa,PiezaActual* p, int * puntaje)
{
    int lineas,gameOver=0;
    if(puedeMover(p, 0, 1, tablero))
    {
        p->fila++;
    }
    else
    {
        fijarPieza(tablero, p);
        lineas=evaluarFilas(tablero);
        actualizarPuntaje(puntaje,lineas);

        if (lineas == 0){
            gameOver=crearNuevaPieza(bolsa,indiceBolsa,p,tablero);
        } else {
            gameOver = 0;
        }
    }
    
    return gameOver;
}

bool puedeMover(PiezaActual *p, int dx, int dy, Tablero* t){
    int i, j, nuevaFila, nuevaCol;

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if (p->tetromino[i][j] != p->tipo) continue;

            nuevaFila = p->fila + i + dy;
            nuevaCol  = p->columna + j + dx;

            // piso
            if(nuevaFila >= t->filasTotales) return false;

            // bordes
            if (nuevaCol < 0 || nuevaCol >= t->columnas) return false;

            // colision con bloque fijo
            if(t->celdas[nuevaFila][nuevaCol] != '.') return false;
        }
    }

    return true;
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
char piezaOcupaCelda(const PiezaActual *p, int filaActual, int columnaActual)
{
    int filaRelativa;
    int columnaRelativa;
    char** aux;
    char* auxFila;

    // Verificar si la celda esta dentro del area 4x4 de la pieza
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

static int ultimas_filas[4];
static int ultimas_cant = 0;

int evaluarFilas(Tablero *tablero){
    int contador = 0;
    for (int i = tablero->filasTotales - 1; i >= tablero->filasOcultas; i--){
        if (analizaLinea(tablero->celdas[i], tablero->columnas)){
            if (contador < 4) ultimas_filas[contador] = i;
            contador++;
            if (contador == 4) break;
        }
    }

    if (contador > 4) contador = 4;
    ultimas_cant = contador;

    return contador;
}

int tetrominosObtieneUltimasFilas(int *ult){
    if (!ult) return 0;
    for (int i = 0; i < ultimas_cant; i++) ult[i] = ultimas_filas[i];
    return ultimas_cant;
}

// int evaluarFilas(Tablero *tablero)
// {
//     char** lectura=(tablero->celdas)+(tablero->filasTotales)-1;
//     char** escritura=(tablero->celdas)+(tablero->filasTotales)-1;
//     char** aux;
//     char** filasCompletas=malloc(sizeof(char*)*4);
//     if(!filasCompletas)
//         return -1;

//     int cantCompletas=0;
//     int i;
//     for(i=tablero->filasTotales-1;i>=tablero->filasOcultas;i--)
//     {
//         if(analizaLinea(*lectura,tablero->columnas))
//         {
//             aux=filasCompletas+cantCompletas;
//             *aux=*lectura;
//             cantCompletas++;
//         }
//         else
//         {
//             (*escritura)=(*lectura);
//             escritura--;
//         }
//         lectura--;
//     }
//     aux=filasCompletas;
//     for(i = 0; i < cantCompletas; i++)
//     {
//         limpiaLinea(*aux,tablero->columnas);
//         *escritura=*aux;
//         aux++;
//         escritura--;
//     }


//     return cantCompletas;
// }

void compactarFilas(Tablero *tablero, const int *filas, int cant){
    if (!tablero || !tablero->celdas || !filas || cant <= 0) return;

    int total = tablero->filasTotales;
    if (cant > 4) cant = 4;

    int *marcadas = calloc(total, sizeof(int));
    char **filasCompletas = malloc(sizeof(char*) * cant);

    if (!marcadas || !filasCompletas){
        free(marcadas);
        free(filasCompletas);
        return;
    }

    for (int i = 0; i < cant; i++){
        if (filas[i] >= 0 && filas[i] < total){
            marcadas[filas[i]] = 1;
        }
    }

    int cantGuardadas = 0;
    int escritura = total - 1;

    for (int lectura = total - 1; lectura >= tablero->filasOcultas; lectura--){
        if (marcadas[lectura]){
            filasCompletas[cantGuardadas] = tablero->celdas[lectura];
            cantGuardadas++;
        } else {
            if (escritura != lectura){
                tablero->celdas[escritura] = tablero->celdas[lectura];
            }
            escritura--;
        }
    }

    for (int i = 0; i < cantGuardadas; i++){
        limpiaLinea(filasCompletas[i], tablero->columnas);
        tablero->celdas[escritura] = filasCompletas[i];
        escritura--;
    }

    free(marcadas);
    free(filasCompletas);
    ultimas_cant = 0;
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
void limpiaLinea(char* fila, int columnas)
{
    int i;

    for(i = 0; i < columnas; i++)
    {
        *(fila + i) = '.';
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
