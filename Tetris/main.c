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
    char bolsa_actual[]={'I','J','L','O','S','T','Z'};
    PiezaActual p;
    p.tetromino = NULL;
    EstadoJuego estado = ESTADO_MENU; // Temporal en CORRIENDO hasta tener menu
    Pantalla pant;

    int indice=0;
    int puntaje=0;
    int gravedad=0;

    int res = 320;
    int escala = 3;

    for (int i = 1; i < argc - 1; i++){
        if (strcmp(argv[i], "--resolucion") == 0){
            res = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "--escala") == 0){
            escala = atoi(argv[i + 1]);
        }
    }

    graficosConfigurarResolucion(&pant, res, escala);

    Tablero *t = tablero_crear();
    if (!t){
        fprintf(stderr, "Error creando tablero\n");
        return 1;
    }

    if (graficosIniciar(&pant) != 0){
        tablero_destruir(t);
        return 1;
    }

    while (1){
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) break;

        switch (estado){
            case ESTADO_MENU:
                graficosDibujarMenu(&pant);

                if (gbt_tecla_presionada(GBTK_j)){
                    tablero_vaciar(t);
                    indice=0;
                    puntaje=0;
                    gravedad=0;

                    if (p.tetromino){
                        destruyeMatriz(p.tetromino, 4);
                        p.tetromino = NULL;
                    }

                    crearNuevaPieza(bolsa_actual, &indice, &p, t);

                    estado = ESTADO_CORRIENDO;
                }

                break;

            case ESTADO_CORRIENDO:
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

                if (gbt_tecla_presionada(GBTK_p)) estado = ESTADO_PAUSA;

                if (gravedad == 30){
                    if (actualizarJuego(t, bolsa_actual, &indice, &p, &puntaje)) estado = ESTADO_GAMEOVER;
                    gravedad = 0;
                }

                graficosDibujarJuego(&pant, t, &p, puntaje);

                gravedad++;
                gbt_esperar(50);
                break;

            case ESTADO_PAUSA:
                graficosDibujarPausa(&pant);

                if (gbt_tecla_presionada(GBTK_p))
                    estado = ESTADO_CORRIENDO;

                gbt_esperar(50);
                break;

            case ESTADO_GAMEOVER:
                graficosDibujarGameOver(&pant);

                if (gbt_tecla_presionada(GBTK_r)){
                    tablero_vaciar(t);
                    indice=0;
                    puntaje=0;
                    gravedad=0;
                    
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
