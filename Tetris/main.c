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
    int indice=0;
    int puntaje=0;
    int gameOver=0;
    int pausa=0;
    int gravedad=0;
    int animacion = 0;
    int animacion_filas[4];
    int animacion_cont = 0;
    int animacion_col = 0;
    int animacion_delay = 0;

    Tablero *t = tablero_crear();
    if (!t)
    {
        fprintf(stderr, "Error creando tablero\n");
        return 1;
    }
    PiezaActual p;
    p.tetromino = NULL;
    crearNuevaPieza(bolsa_actual,&indice,&p,t);

    if (graficosIniciar() != 0){
        tablero_destruir(t);
        return 1;
    }

    while (!gameOver)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) break;

        if (gbt_tecla_presionada(GBTK_p)) pausa = !pausa;


        if(!pausa)
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

                    gameOver = crearNuevaPieza(bolsa_actual, &indice, &p, t);
                    animacion = 0;
                    animacion_cont = 0;
                    animacion_col = 0;
                    animacion_delay = 0;
                }
            }

            if (!animacion && gravedad == 30)
            {
                gameOver = actualizarJuego(t, bolsa_actual, &indice, &p, &puntaje);

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

                gravedad = 0;
            }

            if (animacion) gravedad = 0;

            graficosComenzarFrame();
            graficosDibujarLayout(t);
            graficosDibujarTablero(t, &p);

            fuenteDibujarChar(FUENTE_GRANDE, 'T', 125, 2, PAL_T, 1);
            fuenteDibujarChar(FUENTE_GRANDE, 'E', 138, 2, PAL_O, 1);
            fuenteDibujarChar(FUENTE_GRANDE, 'T', 151, 2, PAL_T, 1);
            fuenteDibujarChar(FUENTE_GRANDE, 'R', 164, 2, PAL_J, 1);
            fuenteDibujarChar(FUENTE_GRANDE, 'I', 177, 2, PAL_I, 1);
            fuenteDibujarChar(FUENTE_GRANDE, 'S', 190, 2, PAL_S, 1);

            char scoreText[16];
            sprintf(scoreText, "puntos: %d", puntaje);
            fuenteDibujarTexto(FUENTE_CHICA, scoreText, 10, 8, PAL_REFLEJO, 1, 1);
            graficosPresentarFrame();

        }
        gravedad++;
        gbt_esperar(50);
    }

    graficosCerrar();
    tablero_destruir(t);
    return 0;
}
