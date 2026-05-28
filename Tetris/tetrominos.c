#include "tetris.h"
#include "graficos.h"

void inicializarBolsa(Bolsa* b,int modo){

    char* base;

    base=malloc(b->tam);
    cargarBolsa(base,modo);

    mezclarBolsa(base, b->tam);
    copiarBolsa(b->actual, base, b->tam );
    mezclarBolsa(base, b->tam);
    copiarBolsa(b->aux, base, b->tam);
    b->indice = 0;
    b->siguienteTipo = siguientePieza(b,modo);
    free(base);
}
void cargarBolsa(char *bolsa, int modo)
{
    if(modo == 0)
    {
        bolsa[0] = 'I';
        bolsa[1] = 'J';
        bolsa[2] = 'L';
        bolsa[3] = 'O';
        bolsa[4] = 'S';
        bolsa[5] = 'T';
        bolsa[6] = 'Z';
    }
    else
    {
        bolsa[0] = 'I';
        bolsa[1] = 'J';
        bolsa[2] = 'L';
        bolsa[3] = 'O';
        bolsa[4] = 'S';
        bolsa[5] = 'T';
        bolsa[6] = 'Z';
        bolsa[7] = 'X';
        bolsa[8] = 'C';
        bolsa[9] = 'P';
        bolsa[10] = 'V';
    }
}

void copiarBolsa(char* destino, const char* origen, int n){
    for (int i = 0; i < n; i++) destino[i] = origen[i];
}

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
int crearNuevaPieza(Bolsa* b, PiezaActual *p, Tablero * t, int modo)
{
    p->tipo = b->siguienteTipo;
    b->siguienteTipo = siguientePieza(b,modo);

    p->fila = 0;
    p->columna = (CLASICO_COLUMNAS / 2) - 2;

    if (p->tetromino) destruyeMatriz(p->tetromino, 4);
    p->tetromino = crearMatriz(4, 4);
    cargaMatriz(p->tetromino, 4, 4, '.');
    cargaPieza(p);

    return puedeMover(p, 0, CLASICO_FILAS_OCULTAS - 2, t, modo) ? 0 : 1;
}

char siguientePieza(Bolsa* b,int modo)
{
    char pieza = b->actual[b->indice];
    b->indice++;


    if(modo==0)
    {
        if (b->indice == 7)
        {
            char temp[7];

            copiarBolsa(temp, b->actual, 7);
            copiarBolsa(b->actual, b->aux, 7);
            copiarBolsa(b->aux, temp, 7);
            mezclarBolsa(b->aux, 7);
            b->indice = 0;
        }
    }
    else
    {
        if(b->indice == 7)
        {
            char base[11]= {'I', 'J', 'L', 'O', 'S', 'T', 'Z','X','C','P','V'};
            copiarBolsa(b->actual, b->aux, b->tam);
            mezclarBolsa(base, b->tam);
            copiarBolsa(b->aux, base, b->tam);
            b->indice = 0;
        }

    }

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
    int pieza_X[4][4] =
    {
        {0,0,0,0},
        {0,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    int pieza_C[4][4] =
    {
        {0,1,1,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    int pieza_P[4][4] =
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    };
    int pieza_V[4][4] =
    {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,1},
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
    case 'X':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_X[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='X';
                }
            }
            aux++;
        }
        break;
    case 'C':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_C[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='C';
                }
            }
            aux++;
        }
        break;
    case 'P':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_P[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='P';
                }
            }
            aux++;
        }
        break;
    case 'V':
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(pieza_V[i][j]==1)
                {
                    auxFila=(*aux)+j;
                    *(auxFila)='V';
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

            if (nuevaFila < 0) continue;

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
bool puedeRotar(PiezaActual* p, char temp[4][4], Tablero* t,int modo,int wallkick){
    int i, j, nuevaFila, nuevaCol, colReal;

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(temp[i][j] != p->tipo) continue;

            if(wallkick==0)
            {
                nuevaFila = p->fila + i;
                nuevaCol = p->columna + j;
            }
            else
            {
                nuevaFila = p->fila + i;
                nuevaCol = p->columna + j + wallkick;
            }

            // piso
            if(nuevaFila >= t->filasTotales) return false;

            if(modo==0)
            {
                // bordes
                if (nuevaCol < 0 || nuevaCol >= t->columnas)
                {

                    return false;
                }

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

int rotar(PiezaActual *p, int dir, Tablero* t,int modo)
{
    int i, j,aux=0;
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

    if(modo==0 && !puedeRotar(p, temp, t,modo,0))
    {
        if(dir==0)
        {
            do
            {
                aux++;
            }
            while(aux < 4 && !puedeRotar(p,temp,t,modo,aux));

            if(aux==4)
                return 0;

            p->columna+=aux;

        }
        if(dir==1)
        {
            do
            {
                aux--;
            }
            while(aux > -4 &&!puedeRotar(p,temp,t,modo,aux));

            if(aux==-4)
                return 0;

            p->columna+=aux;
        }

    }
    else if(modo==1 && !puedeRotar(p, temp, t,modo,0))
        return 0;


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

static int esMinoValido(char c){
    return c == 'I' || c == 'J' || c == 'L' || c == 'O' || c == 'S' || c == 'T' || c == 'Z' ||  c == 'X' || c == 'C' || c == 'P' || c == 'V' || c == '#';
}

int analizaLinea(char* fila, int columnas)
{
    int i;

    for(i = 0; i < columnas; i++)
    {
        // if(*(fila + i) == '.')
        //     return 0;
        if (!esMinoValido(fila[i])) return 0;
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
void actualizarPuntaje(int * puntaje,int lineas, int nivel)
{
    int aux;
    switch(lineas)
    {
    case 1:
        aux=100;
        break;

    case 2:
        aux=300;
        break;

    case 3:
        aux=500;
        break;

    case 4:
        aux=700;
        break;

    default:
        aux=1;
        break;

    }
    aux*=nivel;
    *puntaje+=aux;
}
int actualizarJuego(Tablero *tablero, Bolsa* b,PiezaActual* p, int * puntaje, int* lineasCompletas, int* lockDelay, int modo, int nivel)
{
    int lineas,gameOver=0;
    char** filasCompletas=malloc(sizeof(char*)*tablero->filasTotales);
    if(!filasCompletas)
        return -1;

    fijarPieza(tablero, p,modo);
    lineas=evaluarFilas(tablero,filasCompletas);
    if(lineas>0 && tablero->LineasCompletas==0)
    {
        pintarFilasCompletas(tablero,filasCompletas,lineas);
        actualizarPuntaje(puntaje,lineas,nivel);
        tablero->LineasCompletas=1;
        *lineasCompletas += lineas;
        free(filasCompletas);
        return 0;
    }

    gameOver=crearNuevaPieza(b,p,tablero, modo);

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
    char** filasCompletas=malloc(sizeof(char*)*tablero->filasTotales);
    if(!filasCompletas)
        return ;

    int cantCompletas=0;
    int i;
    for(i=tablero->filasTotales-1;i>=0;i--)
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
    free(filasCompletas);
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

int iniciarPartida(Bolsa *b, PiezaActual *p, Tablero **t, Pantalla *pant, VariablesJuego *v, VariablesConfiguracion *vc){
    if (vc->resSel == 0){
        vc->res = 320;
        vc->escala = 4;
    } else {
        vc->res = 640;
        vc->escala = 2;
    }
    graficosConfigurarResolucion(pant, vc->res, vc->escala);
    
    if (vc->modoSel == 0){
        v->modo = 0;
        vc->columnas = CLASICO_COLUMNAS;
        b->tam = 7;
    } else if (vc->modoSel == 1){
        v->modo = 1;
        vc->columnas = DELUXE_COLUMNAS_FACIL;
        b->tam = 11;
    } else {
        v->modo = 1;
        vc->columnas = DELUXE_COLUMNAS_DIFICIL;
        b->tam = 11;
    }

    if (vc->velSel == 0){
        v->velocidadCaida = 20;
    } else if (vc->velSel == 1){
        v->velocidadCaida = 15;
    } else {
        v->velocidadCaida = 10;
    }

    v->lockDelayMaximo = v->velocidadCaida / 2;
    graficosSetModo(vc->paletaSel);

    if (*t){
        tablero_destruir(*t);
        *t = NULL;
    }

    if (b->actual){
        free(b->actual);
        b->actual = NULL;
    }

    if (b->aux){
        free(b->aux);
        b->aux = NULL;
    }

    *t = tablero_crear(vc->columnas);
    if (!*t) return -1;

    tablero_vaciar(*t);

    v->puntaje = 0;
    v->nivel = 1;
    v->lineasCompletas = 0;
    v->gravedad = 0;
    v->lockDelay = 0;
    v->contadorPiezas = 0;
    v->animandoLinea = 0;
    v->framesAnimacion = 0;
    v->timeFreeze = 0;
    v->delayIzq = 0;
    v->delayDer = 0;
    v->scoreGuardado=0;

    b->actual = malloc(b->tam);
    b->aux = malloc(b->tam);
    if (!b->actual || !b->aux) return -1;

    inicializarBolsa(b, (v->modo));

    if (p->tetromino){
        destruyeMatriz(p->tetromino, 4);
        p->tetromino = NULL;
    }

    if (crearNuevaPieza(b, p, *t, (v->modo))) return -1;

    return 0;
}
int cargarLeaderboard(Leaderboard *lb)
{
    FILE *pf;

    pf = fopen("leaderboard.dat", "rb");

    if(!pf)
    {
        lb->cantidad = 0;
        return 0;
    }

    fread(&(lb->cantidad), sizeof(int), 1, pf);

    fread(lb->vec,sizeof(Registro),lb->cantidad,pf);

    fclose(pf);

    return 1;
}
void insertarOrdenado(Leaderboard *lb, Registro nuevo)
{
    int i;

    if(lb->cantidad >= MAX_TOPS)
        lb->cantidad = MAX_TOPS - 1;

    i = lb->cantidad - 1;

    while(i >= 0 && nuevo.puntaje > lb->vec[i].puntaje)
    {
        lb->vec[i + 1] = lb->vec[i];
        i--;
    }

    lb->vec[i + 1] = nuevo;

    lb->cantidad++;
}
int guardarLeaderboard(Leaderboard *lb)
{
    FILE *pf;

    pf = fopen("leaderboard.dat", "wb");
    if(!pf)
        return 0;

    fwrite(&(lb->cantidad),sizeof(int),1,pf);

    fwrite(lb->vec,sizeof(Registro),lb->cantidad,pf);

    fclose(pf);

    return 1;
}
int guardarConfiguracion(VariablesConfiguracion *vc,const char *archivo)
{
    FILE *pf;

    pf = fopen(archivo, "wb");

    if(!pf)
        return 0;

    fwrite(vc, sizeof(VariablesConfiguracion), 1, pf);

    fclose(pf);

    return 1;
}
int cargarConfiguracion(VariablesConfiguracion *vc,const char *archivo)
{
    FILE *pf;

    pf = fopen(archivo, "rb");

    if(!pf)
    {

        vc->resSel = 1;
        vc->res = 320;
        vc->escala = 4;

        strcpy(vc->user, "AAA");

        vc->columnas = 10;

        vc->modoSel = 0;
        vc->velSel = 0;
        vc->paletaSel = 0;

        guardarConfiguracion(vc, archivo);

        return 0;
    }

    fread(vc, sizeof(VariablesConfiguracion), 1, pf);

    fclose(pf);

    return 1;
}
