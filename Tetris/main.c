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

int main()
{
    srand(time(NULL));
    char bolsa_actual[]={'I','J','L','O','S','T','Z'};
    PiezaActual p;
    p.tetromino = NULL;
    EstadoJuego estado = ESTADO_MENU; // Temporal en CORRIENDO hasta tener menu

    int indice=0;
    int puntaje=0;
    int gravedad=0;

    int animacion_filas[4];
    int animacion = 0;
    int animacion_cont = 0;
    int animacion_col = 0;
    int animacion_delay = 0;

    Tablero *t = tablero_crear();
    if (!t)
    {
        fprintf(stderr, "Error creando tablero\n");
        return 1;
    }

    if (graficosIniciar() != 0){
        tablero_destruir(t);
        return 1;
    }

    while (1){
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) break;

        switch (estado){
            case ESTADO_MENU:
                graficosDibujarMenu();

                if (gbt_tecla_presionada(GBTK_j)){
                    tablero_vaciar(t);
                    indice=0;
                    puntaje=0;
                    gravedad=0;
                    animacion = 0;
                    animacion_cont = 0;
                    animacion_col = 0;
                    animacion_delay = 0;
                    
                    if (p.tetromino){
                        destruyeMatriz(p.tetromino, 4);
                        p.tetromino = NULL;
                    }

                    crearNuevaPieza(bolsa_actual, &indice, &p, t);

                    estado = ESTADO_CORRIENDO;
                }

                break;

            case ESTADO_CORRIENDO:
            {
                if (!animacion){
                    if (gbt_tecla_sostenida(GBTK_a)){
                        if (puedeMover(&p, -1, 0, t)) p.columna--;
                    }

                    if (gbt_tecla_sostenida(GBTK_d)){
                        if (puedeMover(&p, 1, 0, t)) p.columna++;
                    }

                    if (gbt_tecla_sostenida(GBTK_s)){
                        if (puedeMover(&p, 0, 1, t)){
                            p.fila++;
                            puntaje++;
                        }
                    }

                    if (gbt_tecla_presionada(GBTK_q)){
                        rotar(&p, 0, t); // Rotar izq
                    }

                    if (gbt_tecla_presionada(GBTK_e)){
                        rotar(&p, 1, t); // Rotar der
                    }
                }

                if (animacion)
                {
                    animacion_delay++;
                    if (animacion_delay >= 1)   // 1=rapido, 2=medio, 3=lento
                    {
                        animacion_delay = 0;
                        for (int i = 0; i < animacion_cont; i++)
                        {
                            int filaAbs = animacion_filas[i];
                            if (filaAbs >= 0 && filaAbs < t->filasTotales && animacion_col < t->columnas)
                            {
                                t->celdas[filaAbs][animacion_col] = '#';
                            }
                        }
                        animacion_col++;
                    }

                    if (animacion_col >= t->columnas)
                    {
                        compactarFilas(t, animacion_filas, animacion_cont);

                        if (p.tetromino) {
                            destruyeMatriz(p.tetromino, 4);
                            p.tetromino = NULL;
                        }

                        if (crearNuevaPieza(bolsa_actual, &indice, &p, t)) estado = ESTADO_GAMEOVER;

                        animacion = 0;
                        animacion_cont = 0;
                        animacion_col = 0;
                        animacion_delay = 0;
                    }
                }

                if (!animacion && gravedad == 30)
                {
                    int terminoJuego = actualizarJuego(t, bolsa_actual, &indice, &p, &puntaje);

                    int filasDetectadas[4];
                    int nfilas = tetrominosObtieneUltimasFilas(filasDetectadas);
                    if (nfilas > 0)
                    {
                        animacion_cont = nfilas;
                        for (int i = 0; i < nfilas; i++) animacion_filas[i] = filasDetectadas[i];
                        animacion_col = 0;
                        animacion_delay = 0;
                        animacion = 1;
                    }

                    if (terminoJuego) estado = ESTADO_GAMEOVER;

                    gravedad = 0;
                }

                if (gbt_tecla_presionada(GBTK_p)) estado = ESTADO_PAUSA;

                if (animacion) gravedad = 0;

                graficosDibujarJuego(t, &p, puntaje);

                gravedad++;
                gbt_esperar(50);
                break;
            }

            case ESTADO_PAUSA:
                graficosDibujarPausa();

                if (gbt_tecla_presionada(GBTK_p))
                    estado = ESTADO_CORRIENDO;

                gbt_esperar(50);
                break;

            case ESTADO_GAMEOVER:
                graficosDibujarGameOver();

                if (gbt_tecla_presionada(GBTK_r)){
                    tablero_vaciar(t);
                    indice=0;
                    puntaje=0;
                    gravedad=0;
                    animacion = 0;
                    animacion_cont = 0;
                    animacion_col = 0;
                    animacion_delay = 0;
                    
                    if (p.tetromino){
                        destruyeMatriz(p.tetromino, 4);
                        p.tetromino = NULL;
                    }

                    crearNuevaPieza(bolsa_actual, &indice, &p, t);

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
