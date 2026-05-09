#include "graficos.h"

tGBT_ColorRGB paleta[CANT_COLORES] = {
  {0x00, 0x00, 0x00}, // Negro
  {0x55, 0xFF, 0xFF}, // Cyan
  {0x55, 0x55, 0xFF}, // Azul
  {0xAA, 0x55, 0x00}, // Marron
  {0xFF, 0xFF, 0x55}, // Amarillo
  {0x55, 0xFF, 0x55}, // Verde
  {0xAA, 0x00, 0xAA}, // Violeta
  {0xFF, 0x55, 0x55}, // Rojo
  {0x00, 0x00, 0xAA}, // Azul oscuro
  {0x00, 0xAA, 0x00}, // Verde oscuro
  {0x00, 0xAA, 0xAA}, // Cyan oscuro
  {0xAA, 0x00, 0x00}, // Rojo oscuro
  {0x11, 0x11, 0x11}, // Gris oscuro
  {0xCC, 0xCC, 0xCC}, // Gris claro
  {0xFF, 0x55, 0xFF}, // Rosa
  {0xFF, 0xFF, 0xFF}, // Transparente (GBT)
};

int graficosIniciar(void){
  if (gbt_iniciar() != 0) return -1;

  if (gbt_crear_ventana("Tetris", ANCHO_VENTANA, ALTO_VENTANA, ESCALA_VENTANA) != 0){
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

void graficosComenzarFrame(void){
  gbt_borrar_backbuffer(12);
}

void graficosPresentarFrame(void){
  gbt_volcar_backbuffer();
}

static uint8_t obtenerColorCelda(char celda){
  switch (celda){
    case '.': return PAL_FONDO;
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

static void dibujarCelda(uint8_t color, uint16_t oX, uint16_t oY){
  uint16_t offsetX = TABLERO_OFFSET_X + (oX * (PIXELES_CELDA + PX_PADDING));
  uint16_t offsetY = TABLERO_OFFSET_Y + (oY * (PIXELES_CELDA + PX_PADDING));

  for (uint16_t y = 0; y < PIXELES_CELDA; y++){
    for (uint16_t x = 0; x < PIXELES_CELDA; x++){
      gbt_dibujar_pixel(offsetX + x, offsetY + y, color);
    }
  }

  if (color != PAL_FONDO){
    for (uint16_t x = 0; x < PIXELES_CELDA - 1; x++){
      gbt_dibujar_pixel(offsetX + x, offsetY, PAL_REFLEJO);
    }

    for (uint16_t y = 0; y < PIXELES_CELDA - 1; y++){
      gbt_dibujar_pixel(offsetX, offsetY + y, PAL_REFLEJO);
    }
  }
}

void graficosDibujarTablero(const Tablero *tablero, const PiezaActual *pieza){
  if (!tablero || !tablero->celdas) return;

  int filaInicio = tablero->filasOcultas;
  int filaFin = filaInicio + tablero->filasVisibles;

  //Dibujo el tablero y la pieza
  for (int fila = filaInicio; fila < filaFin; fila++){
    for (int col = 0; col < tablero->columnas; col++){
      uint8_t color = PAL_FONDO;

      if (pieza && piezaOcupaCelda(pieza, fila, col) == pieza->tipo){
        color = obtenerColorCelda(pieza->tipo);
      } else {
        color = obtenerColorCelda(tablero->celdas[fila][col]);
      }

      int oX = col;
      int oY = fila - filaInicio;

      dibujarCelda(color, (uint16_t)oX, (uint16_t)oY);
    }
  }
}