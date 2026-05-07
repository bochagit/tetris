#include "graficos.h"

tGBT_ColorRGB paleta[CANT_COLORES] = {
  {0x00, 0x00, 0x00}, // 0: Negro
  {0x00, 0x00, 0xAA}, // 1: Azul
  {0x00, 0xAA, 0x00}, // 2: Verde
  {0x00, 0xAA, 0xAA}, // 3: Cian
  {0xAA, 0x00, 0x00}, // 4: Rojo
  {0xAA, 0x00, 0xAA}, // 5: Magenta
  {0xAA, 0x55, 0x00}, // 6: Marron
  {0xFF, 0xFF, 0x00}  // 7: Amarillo
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
  gbt_borrar_backbuffer(PAL_FONDO);
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
}

static void dibujarCelda(uint8_t color, uint16_t oX, uint16_t oY){
  uint16_t offsetX = oX * (PIXELES_CELDA + PX_PADDING);
  uint16_t offsetY = oY * (PIXELES_CELDA + PX_PADDING);

  for (uint16_t y = 0; y < PIXELES_CELDA; y++){
    for (uint16_t x = 0; x < PIXELES_CELDA; x++){
      gbt_dibujar_pixel(offsetX + x, offsetY + y, color);
    }
  }
}

// --- Probar y analizar lo de abajo --- !!!!!!!

void graficosDibujarTablero(const Tablero *tablero, const PiezaActual *pieza)
{
  if (!tablero || !tablero->celdas) return;

  int filaInicio = tablero->filasOcultas;
  int filaFin = filaInicio + tablero->filasVisibles;

  // Dibujar tablero fijo
  for (int fila = filaInicio; fila < filaFin; fila++) {
    for (int col = 0; col < tablero->columnas; col++) {
      char celda = tablero->celdas[fila][col];
      uint8_t color = obtenerColorCelda(celda);

      // Offset visual para centrar
      int oX = col + 2;
      int oY = (fila - filaInicio) + 2;

      dibujarCelda(color, oX, oY);
    }
  }

  // Dibujar pieza actual
  if (pieza) {
    int indice = tipoAIndice(pieza->tipo);
    uint8_t colorPieza = obtenerColorCelda(pieza->tipo);

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (tetrominos[indice][i][j] == 1) {
          int filaActual = pieza->fila + i;
          int colActual = pieza->columna + j;

          if (filaActual >= filaInicio && filaActual < filaFin) {
            int oX = colActual + 2;
            int oY = (filaActual - filaInicio) + 2;
            dibujarCelda(colorPieza, oX, oY);
          }
        }
      }
    }
  }
}