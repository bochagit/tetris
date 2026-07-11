/*
Integrantes del equipo:

Apellido: Morales Pessacq, Bruno
DNI: 44834035
Usuario: BrunoMoralesP

Apellido: Cardozo, Gonzalo Daniel
DNI: 43777470
Usuario: bochagit
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
    VariablesJuego v;
    VariablesConfiguracion vc;

    bool activaAntiMateria = false;

    const char *archivoConfig = "config.dat";

    if(argc > 1)
    {
        archivoConfig = argv[1];
    }

    cargarConfiguracion(&vc, archivoConfig);

    const char alfabeto[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    int cursor = 0;
    int opcion = 0;

    int opcionMenu = 0;

    int configPaso = 0;
    v.modo=0;
    graficosConfigurarResolucion(&pant,vc.res,vc.escala);


    if (graficosIniciar(&pant, v.modo) != 0){
        return 1;
    }

    while (1){
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) break;

        switch (estado){
            case ESTADO_MENU:
                graficosSetModo(vc.paletaSel);
                graficosDibujarMenu(&pant,v.modo, opcionMenu);

                if (gbt_tecla_presionada(GBTK_ARRIBA) || gbt_tecla_presionada(GBTK_ABAJO)){
                    opcionMenu = 1 - opcionMenu;
                }

                if (gbt_tecla_presionada(GBTK_ENTER)){
                    if (opcionMenu == 0){
                        if (iniciarPartida(&b, &p, &t, &pant,&v, &vc) != 0) return -1;

                        estado = ESTADO_CORRIENDO;
                    } else {
                        configPaso = 0;
                        cursor = 0;
                        opcion = vc.user[cursor] - 'A';
                        estado = ESTADO_CONFIG;
                    }
                }
                break;

            case ESTADO_CONFIG:
                graficosDibujarConfig(&pant, vc.user, cursor, configPaso, vc.modoSel, vc.velSel, vc.paletaSel, vc.resSel);

                if (configPaso == 0){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA)){
                        if (cursor > 0){
                            cursor--;
                        } else {
                            cursor = 2;
                        }
                        opcion = vc.user[cursor] - 'A';
                    }

                    if (gbt_tecla_presionada(GBTK_DERECHA)){
                        if (cursor < 2){
                            cursor++;
                        } else {
                            cursor = 0;
                        }
                        opcion = vc.user[cursor] - 'A';
                    }

                    if (gbt_tecla_presionada(GBTK_ABAJO)){
                        if (opcion == 0){
                            opcion = 25;
                        } else {
                            opcion--;
                        }
                        vc.user[cursor] = alfabeto[opcion];
                    }

                    if (gbt_tecla_presionada(GBTK_ARRIBA)){
                        if (opcion == 25){
                            opcion = 0;
                        } else {
                            opcion++;
                        }
                        vc.user[cursor] = alfabeto[opcion];
                    }
                } else if (configPaso == 1){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA)) vc.modoSel = vc.modoSel == 0 ? 2 : vc.modoSel - 1;
                    if (gbt_tecla_presionada(GBTK_DERECHA)) vc.modoSel = vc.modoSel == 2 ? 0 : vc.modoSel + 1;
                } else if (configPaso == 2){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA)) vc.velSel = vc.velSel == 0 ? 2 : vc.velSel - 1;
                    if (gbt_tecla_presionada(GBTK_DERECHA)) vc.velSel = vc.velSel == 2 ? 0 : vc.velSel + 1;
                } else if (configPaso == 3){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_presionada(GBTK_DERECHA)) vc.paletaSel = 1 - vc.paletaSel;
                } else if (configPaso == 4){
                    if (gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_presionada(GBTK_DERECHA)) vc.resSel = 1 - vc.resSel;
                }

                if (gbt_tecla_presionada(GBTK_ENTER)){
                    if (configPaso < 4){
                        configPaso++;
                    } else {
                        vc.res = vc.resSel == 0 ? 320 : 640;
                        vc.escala = vc.resSel == 0 ? 4 : 2;
                        guardarConfiguracion(&vc, archivoConfig);
                        graficosConfigurarResolucion(&pant, vc.res, vc.escala);

                        if (iniciarPartida(&b, &p, &t, &pant, &v,&vc) != 0) return -1;

                        estado = ESTADO_CORRIENDO;
                    }
                }

                break;

            case ESTADO_CORRIENDO:
                if (v.animandoLinea){
                    graficosDibujarJuego(&pant, t, &p, v.puntaje, v.nivel, v.lineasCompletas, vc.user, b.siguienteTipo, v.modo);

                    v.framesAnimacion++;

                    if (v.framesAnimacion >= 5){
                        filasCompletasEliminar(t);
                        t->LineasCompletas = 0;
                        v.animandoLinea = 0;
                        v.framesAnimacion = 0;

                        if (p.tetromino) {
                            destruyeMatriz(p.tetromino, 4);
                            p.tetromino = NULL;
                        }

                        crearNuevaPieza(&b, &p, t, v.modo);
                    }

                    gbt_esperar(50);
                    break;
                }

                if (gbt_tecla_sostenida(GBTK_a) && v.delayIzq==0){
                    if (puedeMover(&p, -1, 0, t,v.modo)) p.columna--;
                    if(p.columna<-3)p.columna=t->columnas-4;

                    v.delayIzq=2;
                }

                if (gbt_tecla_sostenida(GBTK_d) && v.delayDer==0){
                    if (puedeMover(&p, 1, 0, t,v.modo)) p.columna++;
                    if(p.columna>(t->columnas-1))p.columna=0;

                    v.delayDer=2;
                }

                if (gbt_tecla_sostenida(GBTK_s) && !v.timeFreeze){
                    if (puedeMover(&p, 0, 1, t,v.modo)){
                        p.fila++;
                        actualizarPuntaje(&v.puntaje,0,v.nivel);
                    }
                }

                if (gbt_tecla_presionada(GBTK_q)){
                    rotar(&p, 0, t,v.modo); // Rotar izq
                }

                if (gbt_tecla_presionada(GBTK_e)){
                    rotar(&p, 1, t,v.modo); // Rotar der
                }

                if (gbt_tecla_presionada(GBTK_p)) estado = ESTADO_PAUSA;

                if (gbt_tecla_presionada(GBTK_f)) v.timeFreeze = !v.timeFreeze;

                if (gbt_tecla_presionada(GBTK_n)){
                    if (v.modo == 0){
                        activaAntiMateria = true;
                        graficosAplicarPaletaAntimateria(activaAntiMateria);
                    }
                }

                calcularGhost(&p,t,v.modo);

                if(gbt_tecla_presionada(GBTK_ESPACIO))
                {
                    v.puntaje+=(p.GhostFila-p.fila);
                    p.fila=p.GhostFila-1;
                }


                if(!v.timeFreeze)
                {
                    aplicarGravedad(t,&p,&(v.lockDelay),&(v.gravedad), v.velocidadCaida,v.modo);
                }

                if (gbt_tecla_presionada(GBTK_t)){
                    int gameOverCong = actualizarJuego(t, &b, &p, &v.puntaje, &v.lineasCompletas, &v.lockDelay, v.modo, v.nivel);

                    if (gameOverCong) {
                        estado = ESTADO_GAMEOVER;
                    } else if (t->LineasCompletas == 1) {
                        v.animandoLinea = 1;
                        v.framesAnimacion = 0;
                        v.contadorPiezas = 0;
                        v.gravedad = 0;
                        v.lockDelay = 0;
                        v.delayIzq = 0;
                        v.delayDer = 0;
                    } else {
                        v.gravedad = 0;
                        v.contadorPiezas++;
                    }
                }
                if(v.contadorPiezas==10)
                {
                    (v.velocidadCaida)*=(0.97);
                    v.contadorPiezas=0;
                    v.lockDelayMaximo=(v.velocidadCaida)/2;
                    v.nivel++;
                }

                if (v.lockDelay >= v.lockDelayMaximo) {
                    if (activaAntiMateria){
                        if (!antiMateria(t, &p)){
                            activaAntiMateria = false;
                            graficosAplicarPaletaAntimateria(activaAntiMateria);

                            int gameOver = actualizarJuego(t, &b, &p, &v.puntaje, &v.lineasCompletas, &v.lockDelay, v.modo, v.nivel);
                            if (gameOver) {
                                estado = ESTADO_GAMEOVER;
                            } else if (t->LineasCompletas == 1) {
                                v.animandoLinea = 1;
                                v.framesAnimacion = 0;
                                v.contadorPiezas = 0;
                                v.gravedad = 0;
                                v.lockDelay = 0;
                                v.delayIzq = 0;
                                v.delayDer = 0;
                            } else {
                                v.gravedad = 0;
                                v.contadorPiezas++;
                            }
                        }

                        v.gravedad = 0;
                        v.lockDelay = 0;
                        v.delayIzq = 0;
                        v.delayDer = 0;
                    } else {
                        int gameOver = actualizarJuego(t, &b, &p, &v.puntaje, &v.lineasCompletas, &v.lockDelay, v.modo, v.nivel);

                        if (gameOver) {
                            estado = ESTADO_GAMEOVER;
                        } else if (t->LineasCompletas == 1) {
                            v.animandoLinea = 1;
                            v.framesAnimacion = 0;
                            v.contadorPiezas = 0;
                            v.gravedad = 0;
                            v.lockDelay = 0;
                            v.delayIzq = 0;
                            v.delayDer = 0;
                        } else {
                            v.gravedad = 0;
                            v.contadorPiezas++;
                        }
                    }
                }
                if(v.contadorPiezas==10)
                {
                    (v.velocidadCaida)*=(0.97);
                    v.contadorPiezas=0;
                    v.lockDelayMaximo=(v.velocidadCaida)/2;
                    v.nivel++;
                }

                graficosDibujarJuego(&pant, t, &p, v.puntaje, v.nivel, v.lineasCompletas, vc.user, b.siguienteTipo, v.modo);

                if(!v.timeFreeze)
                {
                    v.gravedad++;
                }
                if(v.delayDer>0)
                    v.delayDer--;
                if(v.delayIzq>0)
                    v.delayIzq--;

                gbt_esperar(50);
                break;

        case ESTADO_PAUSA:

                graficosDibujarPausa(&pant);

                if (gbt_tecla_presionada(GBTK_p))
                    estado = ESTADO_CORRIENDO;

                gbt_esperar(50);
                break;

        case ESTADO_GAMEOVER:
            if(!v.scoreGuardado)
            {
                strcpy(nuevo.nombre, vc.user);
                nuevo.puntaje = v.puntaje;

                cargarLeaderboard(&lb);
                insertarOrdenado(&lb, nuevo);
                guardarLeaderboard(&lb);

                v.scoreGuardado=1;
            }
                graficosDibujarGameOver(&pant,&lb,v.puntaje);

                if (gbt_tecla_presionada(GBTK_r)){
                    if (iniciarPartida(&b, &p, &t, &pant, &v,&vc) != 0) return -1;

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
