#include "graficos.h"
#include "fuentes.h"

tGBT_ColorRGB paleta[CANT_COLORES] = {
  {0x02, 0x06, 0x17}, // Azul muy oscuro - celdas tablero
  {0x55, 0xFF, 0xFF}, // Cyan - I
  {0x55, 0x55, 0xFF}, // Azul - J
  {0xAA, 0x55, 0x00}, // Marron - L
  {0xFF, 0xFF, 0x55}, // Amarillo - O
  {0x55, 0xFF, 0x55}, // Verde - S
  {0xAA, 0x00, 0xAA}, // Violeta - T
  {0xFF, 0x55, 0x55}, // Rojo - Z
  {0xBB, 0x00, 0x00}, // Rojo oscuro - Game Over
  {0x00, 0xAA, 0x00}, // Verde oscuro
  {0x11, 0x18, 0x27}, // Cyan oscuro
  {0x0F, 0x5B, 0x7F}, // Azul acero oscuro - Animacion
  {0x1F, 0x29, 0x37}, // Gris acero oscuro - fondo tablero
  {0xEF, 0xEF, 0xEF}, // Gris claro - reflejos
  {0x47, 0x55, 0x69}, // Gris acero - bordes
  {0x0F, 0x17, 0x2A}, // Azul - fondo layout
  {0xFF, 0xFF, 0xFF}  // Transparente (GBT)
};

int graficosIniciar(const Pantalla* pant){
  if (gbt_iniciar() != 0) return -1;

  if (gbt_crear_ventana("Tetris", pant->anchoVentana, pant->altoVentana, pant->escala) != 0){
    gbt_cerrar();
    return -1;
  }

  if (gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888) != 0){
    gbt_cerrar();
    return -1;
  }

  return 0;
}

void graficosCerrar(void){
  gbt_destruir_ventana();
  gbt_cerrar();
}

void graficosComenzarFrame(uint8_t color){
  gbt_borrar_backbuffer(color);
}

void graficosPresentarFrame(void){
  gbt_volcar_backbuffer();
}

void graficosConfigurarResolucion(Pantalla* pant, int res, int escala){
  if (res == 320){
    pant->anchoVentana = 320;
    pant->altoVentana = 200;
    pant->escala = escala;
    pant->tableroOffsetX = 120;
    pant->tableroOffsetY = 15;
    pant->pixelesCelda = 8;
    pant->pxPadding = 1;
  } else {
    pant->anchoVentana = 640;
    pant->altoVentana = 480;
    pant->escala = escala;
    pant->tableroOffsetX = 240;
    pant->tableroOffsetY = 30;
    pant->pixelesCelda = 16;
    pant->pxPadding = 2;
  }
}

static uint8_t obtenerColorCelda(char celda){
  switch (celda){
    case '.': return PAL_FONDO;
    case '#': return 11; // Animacion
    case 'I': return PAL_I;
    case 'J': return PAL_J;
    case 'L': return PAL_L;
    case 'O': return PAL_O;
    case 'S': return PAL_S;
    case 'T': return PAL_T;
    case 'Z': return PAL_Z;
    default: return PAL_FONDO;
  }
};

void graficosDibujarCelda(const Pantalla* pant, uint8_t color, uint16_t oX, uint16_t oY){
  uint16_t offsetX = pant->tableroOffsetX + (oX * (pant->pixelesCelda + pant->pxPadding));
  uint16_t offsetY = pant->tableroOffsetY + (oY * (pant->pixelesCelda + pant->pxPadding));

  for (uint16_t y = 0; y < pant->pixelesCelda; y++){
    for (uint16_t x = 0; x < pant->pixelesCelda; x++){
      gbt_dibujar_pixel(offsetX + x, offsetY + y, color);
    }
  }

  if (color != PAL_FONDO){
    for (uint16_t x = 0; x < pant->pixelesCelda - 1; x++){
      gbt_dibujar_pixel(offsetX + x, offsetY, PAL_REFLEJO);
    }

    for (uint16_t y = 0; y < pant->pixelesCelda - 1; y++){
      gbt_dibujar_pixel(offsetX, offsetY + y, PAL_REFLEJO);
    }
  }
}

void graficosDibujarTablero(const Pantalla* pant, const Tablero *tablero, const PiezaActual *pieza){
  if (!tablero || !tablero->celdas) return;

  int filaInicio = tablero->filasOcultas;
  int filaFin = filaInicio + tablero->filasVisibles;

  //Dibujo el tablero y la pieza
  for (int fila = filaInicio; fila < filaFin; fila++){
    for (int col = 0; col < tablero->columnas; col++){
      uint8_t color = PAL_FONDO;

      if (tablero->celdas[fila][col] == '#'){
        color = obtenerColorCelda('#');
      }
      else if (pieza && piezaOcupaCelda(pieza, fila, col) == pieza->tipo){
        color = obtenerColorCelda(pieza->tipo);
      } else {
        color = obtenerColorCelda(tablero->celdas[fila][col]);
      }

      int oX = col;
      int oY = fila - filaInicio;

      graficosDibujarCelda(pant, color, (uint16_t)oX, (uint16_t)oY);
    }
  }
}

void graficosDibujarRect(int x, int y, int w, int h, uint8_t color){
  for (int py = y; py < y + h; py++){
    for (int px = x; px < x + w; px++){
      gbt_dibujar_pixel(px, py, color);
    }
  }
}

void graficosDibujarBorde(int x, int y, int w, int h, uint8_t color, int grosor){
  graficosDibujarRect(x, y, w, grosor, color); // borde superior
  graficosDibujarRect(x, y + h - grosor, w, grosor, color); // borde inferior
  graficosDibujarRect(x, y, grosor, h, color); // borde izq
  graficosDibujarRect(x + w - grosor, y, grosor, h, color); // borde der
}

void graficosDibujarLayout(const Tablero *t, const Pantalla* pant){
  int tableroW = t->columnas * pant->pixelesCelda + (t->columnas - 1) * pant->pxPadding;
  int tableroH = t->filasVisibles * pant->pixelesCelda + (t->filasVisibles - 1) * pant->pxPadding;

  int margin = 10;
  int top = 18;
  int gap = 15;

  int tableroX = pant->tableroOffsetX;
  int tableroY = pant->tableroOffsetY;

  int panelIzqX = margin;
  int panelIzqY = top;
  int panelIzqW = tableroX - gap - panelIzqX;
  int panelIzqH = tableroH;

  int panelDerX = tableroX + tableroW + gap;
  int panelDerY = top;
  int panelDerW = pant->anchoVentana - panelDerX - margin;
  int panelDerH = tableroH;

  graficosDibujarRect(panelIzqX, panelIzqY, panelIzqW, panelIzqH, 10);
  graficosDibujarBorde(panelIzqX, panelIzqY, panelIzqW, panelIzqH, 14, 1);

  graficosDibujarRect(panelDerX, panelDerY - 1, panelDerW, (panelDerH / 2), 10);
  graficosDibujarBorde(panelDerX, panelDerY - 1, panelDerW, (panelDerH / 2), 14, 1);

  graficosDibujarRect(panelDerX, panelDerY + (panelDerH / 2) + 1, panelDerW, (panelDerH / 2), 10);
  graficosDibujarBorde(panelDerX, panelDerY + (panelDerH / 2) + 1, panelDerW, (panelDerH / 2), 14, 1);

  graficosDibujarRect(tableroX - 4, tableroY - 4, tableroW + 8, tableroH + 8, 12);
  graficosDibujarBorde(tableroX - 4, tableroY - 4, tableroW + 8, tableroH + 8, 14, 1);
}

void graficosDibujarMenu(const Pantalla* pant){
  graficosComenzarFrame(15);

  fuenteDibujarTexto(FUENTE_GRANDE, "MENU", pant->anchoVentana / 2 - ((13 * strlen("MENU")) / 2), pant->altoVentana / 4, PAL_REFLEJO, 1, 1);

  fuenteDibujarChar(FUENTE_GRANDE, 'T', pant->anchoVentana / 2 - ((26 * strlen("TETRIS")) / 2), 5, PAL_T, 2);
  fuenteDibujarChar(FUENTE_GRANDE, 'E', pant->anchoVentana / 2 - ((26 * strlen("TETRIS")) / 2) + 26, 5, PAL_O, 2);
  fuenteDibujarChar(FUENTE_GRANDE, 'T', pant->anchoVentana / 2 - ((26 * strlen("TETRIS")) / 2) + 52, 5, PAL_T, 2);
  fuenteDibujarChar(FUENTE_GRANDE, 'R', pant->anchoVentana / 2 - ((26 * strlen("TETRIS")) / 2) + 78, 5, PAL_J, 2);
  fuenteDibujarChar(FUENTE_GRANDE, 'I', pant->anchoVentana / 2 - ((26 * strlen("TETRIS")) / 2) + 104, 5, PAL_I, 2);
  fuenteDibujarChar(FUENTE_GRANDE, 'S', pant->anchoVentana / 2 - ((26 * strlen("TETRIS")) / 2) + 130, 5, PAL_S, 2);

  graficosDibujarRect(10, pant->altoVentana - (pant->altoVentana / 3) - 10, 25, 25, 12);
  graficosDibujarRect(10 + 2, (pant->altoVentana - (pant->altoVentana / 3)) - 8, 25, 25, 0);
  graficosDibujarBorde(10 + 2, (pant->altoVentana - (pant->altoVentana / 3)) - 8, 25, 25, 14, 1);
  fuenteDibujarChar(FUENTE_GRANDE, 'J', (10 + 2) + ((25 - 13) / 2), ((pant->altoVentana - (pant->altoVentana / 3)) - 8) + ((25 - 13) / 2), PAL_REFLEJO, 1);

  fuenteDibujarTexto(FUENTE_CHICA, "jugar", 10 + 30, (pant->altoVentana - (pant->altoVentana / 3)), PAL_REFLEJO, 1, 1);
  
  graficosPresentarFrame();
}

void graficosDibujarJuego(const Pantalla* pant, const Tablero *t, const PiezaActual *p, int puntaje){
  graficosComenzarFrame(15);
  graficosDibujarLayout(t, pant);
  graficosDibujarTablero(pant, t, p);

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

void graficosDibujarPausa(const Pantalla* pant){
  graficosComenzarFrame(15);

  fuenteDibujarTexto(FUENTE_CHICA, "pausa", (pant->anchoVentana / 2) - ((7 * strlen("pausa") / 2)), 90, PAL_REFLEJO, 1, 1);
  fuenteDibujarTexto(FUENTE_CHICA, "pulsa -p- para continuar", (pant->anchoVentana / 2) - ((7 * strlen("pulsa -p- para continuar") / 2)), 110, PAL_REFLEJO, 1, 1);

  graficosPresentarFrame();
}

void graficosDibujarGameOver(const Pantalla* pant){
  graficosComenzarFrame(0);

  fuenteDibujarTexto(FUENTE_GRANDE, "- GAME OVER -", (pant->anchoVentana / 2) - ((13 * strlen("- GAME OVER -") / 2)), 90, 8, 1, 1);

  graficosDibujarRect(10, pant->altoVentana - (pant->altoVentana / 3) - 10, 25, 25, 12);
  graficosDibujarRect(10 + 2, (pant->altoVentana - (pant->altoVentana / 3)) - 8, 25, 25, 0);
  graficosDibujarBorde(10 + 2, (pant->altoVentana - (pant->altoVentana / 3)) - 8, 25, 25, 14, 1);
  fuenteDibujarChar(FUENTE_GRANDE, 'R', (10 + 2) + ((25 - 13) / 2), ((pant->altoVentana - (pant->altoVentana / 3)) - 8) + ((25 - 13) / 2), PAL_REFLEJO, 1);

  fuenteDibujarTexto(FUENTE_CHICA, "volver a jugar", 10 + 30, (pant->altoVentana - (pant->altoVentana / 3)), PAL_REFLEJO, 1, 1);

  graficosDibujarRect(10, pant->altoVentana - (pant->altoVentana / 3) + 20, 25, 25, 12);
  graficosDibujarRect(10 + 2, (pant->altoVentana - (pant->altoVentana / 3)) + 22, 25, 25, 0);
  graficosDibujarBorde(10 + 2, (pant->altoVentana - (pant->altoVentana / 3)) + 22, 25, 25, 14, 1);
  fuenteDibujarChar(FUENTE_GRANDE, 'M', (10 + 2) + ((25 - 13) / 2), ((pant->altoVentana - (pant->altoVentana / 3)) + 22) + ((25 - 13) / 2), PAL_REFLEJO, 1);

  fuenteDibujarTexto(FUENTE_CHICA, "volver al menu", 10 + 30, (pant->altoVentana - (pant->altoVentana / 3)) + 30, PAL_REFLEJO, 1, 1);

  
  graficosPresentarFrame();
}
