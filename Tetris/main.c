/*
Integrantes del equipo:

Apellido: Morales Pessacq, Bruno
DNI: 44834035
Usuario: BrunoMoralesP
Entrega: Sí

Apellido: Cardozo, Gonzalo Daniel
DNI: 43777470
Usuario: bochagit
Entrega: Sí
*/

#include <stdio.h>
#include <stdbool.h>
#include "tablero.h"
#include "graficos.h"
#include "fuentes.h"

int main(int argc, char *argv[]){
    srand(time(NULL));
    Bolsa b = {0};
    PiezaActual p;
    p.tetromino = NULL;
    EstadoJuego estado = ESTADO_MENU;
    Pantalla pant;
    Tablero *t = NULL;
    Leaderboard lb;
    Registro nuevo;


    int puntaje=0;
    int nivel = 1;
    int lineasCompletas = 0;
    int gravedad=0;
    int lockDelay=0;
    int velocidadCaida=20;
    int contadorPiezas=0;
    int timeFreeze=0;
    int lockDelayMaximo=velocidadCaida/2;
    int delayIzq=0;
    int delayDer=0;
    int modo=0;
    int columnas = 0;
    int scoreGuardado=0;

    int res = 320;
    int escala = 3;

    char user[4] = {'A', 'A', 'A', '\0'};
    const char alfabeto[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    int cursor = 0;
    int opcion = 0;

    int opcionMenu = 0;

    int configPaso = 0;
    int modoSel = 0;
    int velSel = 0;
    int paletaSel = 0;

    for (int i = 1; i < argc - 1; i++){
        if (strcmp(argv[i], "--resolucion") == 0){
            res = atoi(argv[i + 1]);
            if (res != 320 && res != 640) res = 320;
        }
        if (strcmp(argv[i], "--escala") == 0){
            escala = atoi(argv[i + 1]);
            if (escala <= 0) escala = 1;
        }
    }

    graficosConfigurarResolucion(&pant, res, escala);


    if (graficosIniciar(&pant, modo) != 0){
        return 1;
    }

    while (1){
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) break;

        switch (estado){
            case ESTADO_MENU:
                graficosSetModo(paletaSel);
                graficosDibujarMenu(&pant, modo, opcionMenu);

                if (gbt_tecla_presionada(GBTK_ARRIBA) || gbt_tecla_presionada(GBTK_ABAJO)){
                    opcionMenu = 1 - opcionMenu;
                }

                if (gbt_tecla_presionada(GBTK_ENTER)){
                    if (opcionMenu == 0){
                        t=tablero_crear(CLASICO_COLUMNAS);
                        if(!t) return -1;

                        tablero_vaciar(t);
                        puntaje=0;
                        gravedad=0;
                        nivel = 1;
                        lineasCompletas = 0;
                        scoreGuardado=0;
                        b.tam=7;
                        b.actual=malloc(b.tam);
                        b.aux=malloc(b.tam);

                        inicializarBolsa(&b,modo);

                        if (p.tetromino){
                            destruyeMatriz(p.tetromino, 4);
                            p.tetromino = NULL;
                        }

                        crearNuevaPieza(&b, &p, t,modo);
                        estado = ESTADO_CORRIENDO;
                    } else {
                        configPaso = 0;
                        cursor = 0;
                        opcion = user[cursor] - 'A';
                        estado = ESTADO_CONFIG;
                    }
                }

                // if (gbt_tecla_presionada(GBTK_d)){
                //     t=tablero_crear(DELUXE_COLUMNAS_DIFICIL);
                //     if(!t)
                //        return -1;
                //     tablero_vaciar(t);
                //     puntaje=0;
                //     gravedad=0;
                //     nivel = 1;
                //     lineasCompletas = 0;
                //     modo=1;
                //     b.tam=11;
                //     b.actual=malloc(b.tam);
                //     b.aux=malloc(b.tam);

                //     graficosSetModo(paletaSel);

                //     inicializarBolsa(&b,modo);

                //     if (p.tetromino){
                //         destruyeMatriz(p.tetromino, 4);
                //         p.tetromino = NULL;
                //     }

                //     crearNuevaPieza(&b, &p, t,modo);

                //     estado = ESTADO_USER;
                // }

                // if (gbt_tecla_presionada(GBTK_f)){
                //     t=tablero_crear(DELUXE_COLUMNAS_FACIL);
                //     if(!t)
                //        return -1;
                //     tablero_vaciar(t);
                //     puntaje=0;
                //     gravedad=0;
                //     nivel = 1;
                //     lineasCompletas = 0;
                //     modo=1;
                //     b.tam=11;
                //     b.actual=malloc(b.tam);
                //     b.aux=malloc(b.tam);

                //     graficosSetModo(paletaSel);

                //     inicializarBolsa(&b,modo);

                //     if (p.tetromino){
                //         destruyeMatriz(p.tetromino, 4);
                //         p.tetromino = NULL;
                //     }

                //     crearNuevaPieza(&b, &p, t,modo);

                //     estado = ESTADO_USER;
                // }

                break;

            case ESTADO_CONFIG:
                graficosDibujarConfig(&pant, user, cursor, configPaso, modoSel, velSel, paletaSel);

                if (configPaso == 0){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA)){
                        if (cursor > 0){
                            cursor--;
                        } else {
                            cursor = 2;
                        }
                        opcion = user[cursor] - 'A';
                    }

                    if (gbt_tecla_presionada(GBTK_DERECHA)){
                        if (cursor < 2){
                            cursor++;
                        } else {
                            cursor = 0;
                        }
                        opcion = user[cursor] - 'A';
                    }

                    if (gbt_tecla_presionada(GBTK_ABAJO)){
                        if (opcion == 0){
                            opcion = 25;
                        } else {
                            opcion--;
                        }
                        user[cursor] = alfabeto[opcion];
                    }

                    if (gbt_tecla_presionada(GBTK_ARRIBA)){
                        if (opcion == 25){
                            opcion = 0;
                        } else {
                            opcion++;
                        }
                        user[cursor] = alfabeto[opcion];
                    }
                } else if (configPaso == 1){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA)) modoSel = modoSel == 0 ? 2 : modoSel - 1;
                    if (gbt_tecla_presionada(GBTK_DERECHA)) modoSel = modoSel == 2 ? 0 : modoSel + 1;
                } else if (configPaso == 2){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA)) velSel = velSel == 0 ? 2 : velSel - 1;
                    if (gbt_tecla_presionada(GBTK_DERECHA)) velSel = velSel == 2 ? 0 : velSel + 1;
                } else if (configPaso == 3){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_presionada(GBTK_DERECHA)) paletaSel = 1 - paletaSel;
                }

                if (gbt_tecla_presionada(GBTK_ENTER)){
                    if (configPaso < 3){
                        configPaso++;
                    } else {
                        if (modoSel == 0){
                            modo = 0;
                            columnas = CLASICO_COLUMNAS;
                            b.tam = 7;
                        } else if (modoSel == 1){
                            modo = 1;
                            columnas = DELUXE_COLUMNAS_FACIL;
                            b.tam = 11;
                        } else {
                            modo = 1;
                            columnas = DELUXE_COLUMNAS_DIFICIL;
                            b.tam = 11;
                        }

                        // Logica velocidad

                        graficosSetModo(paletaSel);

                        if (t){
                            tablero_destruir(t);
                            t = NULL;
                        }
                        
                        if (b.actual){
                            free(b.actual);
                            b.actual = NULL;
                        }

                        if (b.aux){
                            free(b.aux);
                            b.aux = NULL;
                        }

                        t = tablero_crear(columnas);
                        if (!t) return -1;

                        tablero_vaciar(t);

                        puntaje = 0;
                        gravedad = 0;
                        nivel = 1;
                        lineasCompletas = 0;
                        contadorPiezas = 0;
                        timeFreeze = 0;
                        delayIzq = 0;
                        delayDer = 0;
                        lockDelay = 0;

                        b.actual = malloc(b.tam);
                        b.aux = malloc(b.tam);
                        if (!b.actual || !b.aux) return - 1;

                        inicializarBolsa(&b, modo);

                        if (p.tetromino){
                            destruyeMatriz(p.tetromino, 4);
                            p.tetromino = NULL;
                        }

                        crearNuevaPieza(&b, &p, t, modo);
                        estado = ESTADO_CORRIENDO;
                    }
                }

                break;

            case ESTADO_CORRIENDO:
                if (gbt_tecla_sostenida(GBTK_a) && delayIzq==0){
                    if (puedeMover(&p, -1, 0, t,modo)) p.columna--;
                    if(p.columna<-3)p.columna=t->columnas-4;

                    delayIzq=2;
                }

                if (gbt_tecla_sostenida(GBTK_d) && delayDer==0){
                    if (puedeMover(&p, 1, 0, t,modo)) p.columna++;
                    if(p.columna>(t->columnas-1))p.columna=0;

                    delayDer=2;
                }

                if (gbt_tecla_sostenida(GBTK_s) && !timeFreeze){
                    if (puedeMover(&p, 0, 1, t,modo)){
                        p.fila++;
                        actualizarPuntaje(&puntaje,0,nivel);
                    }
                }

                if (gbt_tecla_presionada(GBTK_q)){
                    rotar(&p, 0, t,modo); // Rotar izq
                }

                if (gbt_tecla_presionada(GBTK_e)){
                    rotar(&p, 1, t,modo); // Rotar der
                }

                if (gbt_tecla_presionada(GBTK_p)) estado = ESTADO_PAUSA;

                if (gbt_tecla_presionada(GBTK_f)) timeFreeze = !timeFreeze;

                calcularGhost(&p,t,modo);

                if(gbt_tecla_presionada(GBTK_ESPACIO))
                {
                    puntaje+=(p.GhostFila-p.fila);
                    p.fila=p.GhostFila-1;
                }


                if(!timeFreeze)
                {
                    aplicarGravedad(t,&p,&lockDelay,&gravedad, velocidadCaida,modo);
                }

                if(lockDelay >= lockDelayMaximo)
                {
                    if(actualizarJuego(t,&b,&p,&puntaje,&lineasCompletas,&lockDelay, modo,nivel)) estado = ESTADO_GAMEOVER;
                    gravedad=0;
                    contadorPiezas++;

                }
                if(contadorPiezas==10)
                {
                    velocidadCaida*=(0.97);
                    contadorPiezas=0;
                    lockDelayMaximo=velocidadCaida/2;
                    nivel++;
                }

                graficosDibujarJuego(&pant, t, &p, puntaje, nivel, lineasCompletas, user, b.siguienteTipo, modo);
                if(t->LineasCompletas==1 && gravedad>=5)
                {
                    filasCompletasEliminar(t);
                    t->LineasCompletas=0;
                }

                if(!timeFreeze)
                {
                    gravedad++;
                }
                if(delayDer>0)
                    delayDer--;
                if(delayIzq>0)
                    delayIzq--;
                gbt_esperar(50);
                break;

        case ESTADO_PAUSA:

                graficosDibujarPausa(&pant);

                if (gbt_tecla_presionada(GBTK_p))
                    estado = ESTADO_CORRIENDO;

                gbt_esperar(50);
                break;

        case ESTADO_GAMEOVER:
            if(!scoreGuardado)
            {
                strcpy(nuevo.nombre, user);
                nuevo.puntaje = puntaje;

                cargarLeaderboard(&lb);
                insertarOrdenado(&lb, nuevo);
                guardarLeaderboard(&lb);

                scoreGuardado=1;
            }
                graficosDibujarGameOver(&pant,&lb,puntaje);

                if (gbt_tecla_presionada(GBTK_r)){
                    tablero_vaciar(t);
                    puntaje=0;
                    gravedad=0;
                    nivel = 1;
                    lineasCompletas = 0;
                    scoreGuardado=0;

                    inicializarBolsa(&b, modo);

                    if (p.tetromino){
                        destruyeMatriz(p.tetromino, 4);
                        p.tetromino = NULL;
                    }

                    crearNuevaPieza(&b, &p, t, modo);

                    estado = ESTADO_CORRIENDO;
                }

                if (gbt_tecla_presionada(GBTK_m)) estado = ESTADO_MENU;

                break;
        }
    }

    if (p.tetromino) destruyeMatriz(p.tetromino, 4);

    graficosCerrar();
    tablero_destruir(t);
    return 0;
}
