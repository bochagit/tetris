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
  {0x77, 0x77, 0x77}, // Ghost
  {0x11, 0x18, 0x27}, // Cyan oscuro - fondo estadisticas
  {0x0F, 0x5B, 0x7F}, // Azul acero oscuro - Animacion
  {0x1F, 0x29, 0x37}, // Gris acero oscuro - fondo tablero
  {0xEF, 0xEF, 0xEF}, // Gris claro - reflejos
  {0x47, 0x55, 0x69}, // Gris acero - bordes
  {0x0F, 0x17, 0x2A}, // Azul - fondo layout
  {0xF7, 0xBD, 0x00}, // Dorado
  {0xFF, 0x9F, 0x40}, // Naranja - X
  {0x40, 0xFF, 0xA0}, // Menta - C
  {0xFF, 0x40, 0x90}, // Rosa - P
  {0x80, 0x40, 0xFF}, // Azul-violeta - V
  {0xFF, 0xFF, 0xFF}  // Transparente (GBT)
};

tGBT_ColorRGB paleta_deluxe[CANT_COLORES] = {
  {0x04, 0x03, 0x01}, // Negro calido - celdas tablero
  {0x7D, 0xF9, 0xFF}, // Cyan hielo - I
  {0x4D, 0x7C, 0xFF}, // Azul zafiro - J
  {0xD9, 0x8C, 0x1F}, // Oro viejo - L
  {0xFF, 0xE0, 0x66}, // Oro brillante - O
  {0x66, 0xFF, 0xB3}, // Verde jade - S
  {0xB0, 0x5C, 0xFF}, // Violeta neón - T
  {0xFF, 0x5A, 0x6E}, // Rojo rubí - Z
  {0x66, 0x00, 0x00}, // Rojo vino oscuro - Game Over
  {0x8A, 0x8A, 0x8A}, // Ghost metálico
  {0x12, 0x10, 0x0B}, // Negro dorado - fondo estadísticas
  {0x8C, 0x6A, 0x1A}, // Oro oscuro - animación
  {0x1A, 0x16, 0x0F}, // Marrón-negro - fondo tablero
  {0xFF, 0xF4, 0xD6}, // Marfil - reflejos
  {0x8B, 0x73, 0x39}, // Dorado - bordes
  {0x0B, 0x0A, 0x07}, // Negro mas oscuro - fondo layout
  {0xFF, 0xD7, 0x00}, // Oro
  {0xFF, 0xB3, 0x47}, // Naranja - X
  {0x5E, 0xF2, 0xC2}, // Menta - C
  {0xFF, 0x5C, 0xB8}, // Rosa magenta - P
  {0x8A, 0x5C, 0xFF}, // Índigo - V
  {0xFF, 0xFF, 0xFF}  // Transparente (GBT)
};

int graficosIniciar(const Pantalla* pant, int modo){
  if (gbt_iniciar() != 0) return -1;

  if (gbt_crear_ventana("Tetris", pant->anchoVentana, pant->altoVentana, pant->escala) != 0){
    gbt_cerrar();
    return -1;
  }

  tGBT_ColorRGB *pal = modo == 1 ? paleta_deluxe : paleta;

  if (gbt_aplicar_paleta(pal, CANT_COLORES, GBT_FORMATO_888) != 0){
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
    pant->pixelesCelda = 8;
    pant->pxPadding = 1;
    pant->tableroOffsetX = (pant->anchoVentana / 2) - ((pant->pixelesCelda * CLASICO_COLUMNAS) / 2) - ((pant->pxPadding * CLASICO_COLUMNAS) / 2);
    pant->tableroOffsetY = 15;
  } else {
    pant->anchoVentana = 640;
    pant->altoVentana = 480;
    pant->escala = escala;
    pant->pixelesCelda = 20;
    pant->pxPadding = 1;
    pant->tableroOffsetX = (pant->anchoVentana / 2) - ((pant->pixelesCelda * CLASICO_COLUMNAS) / 2);
    pant->tableroOffsetY = 45;
  }
}

void graficosSetModo(int modo){
  tGBT_ColorRGB *pal = modo == 1 ? paleta_deluxe : paleta;
  gbt_aplicar_paleta(pal, CANT_COLORES, GBT_FORMATO_888);
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
    case 'G': return PAL_GHOST;
    case 'X': return PAL_X;
    case 'C': return PAL_C;
    case 'P': return PAL_P;
    case 'V': return PAL_V;
    default: return PAL_FONDO;
  }
};

void graficosDibujarCelda(const Pantalla* pant, int origenX, int origenY, uint8_t color, uint16_t oX, uint16_t oY){
  uint16_t offsetX = origenX + (oX * (pant->pixelesCelda + pant->pxPadding));
  uint16_t offsetY = origenY + (oY * (pant->pixelesCelda + pant->pxPadding));

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

void graficosDibujarTablero(const Pantalla* pant, const Tablero *tablero, const PiezaActual *pieza, int origenX, int origenY){
  if (!tablero || !tablero->celdas) return;

  int filaInicio = tablero->filasOcultas;
  int filaFin = filaInicio + tablero->filasVisibles;
  int diferencia = (pieza->GhostFila - pieza->fila)-1;

  //Dibujo el tablero y la pieza
  for (int fila = filaInicio; fila < filaFin; fila++){
    for (int col = 0; col < tablero->columnas; col++){
      uint8_t color = PAL_FONDO;

        if (tablero->celdas[fila][col] == '#')
        {
            color = obtenerColorCelda('#');
        }
        else if(pieza && piezaOcupaCelda(pieza, fila, col,tablero->columnas) == pieza->tipo)
        {
            color = obtenerColorCelda(pieza->tipo);
        }
        else if (pieza && piezaOcupaCelda(pieza, fila-diferencia, col,tablero->columnas) == pieza->tipo)
        {
            color = obtenerColorCelda('G');}
        else
        {
            color = obtenerColorCelda(tablero->celdas[fila][col]);
        }

      graficosDibujarCelda(pant, origenX, origenY, color, col, fila - filaInicio);
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

void graficosDibujarJuego(const Pantalla* pant, const Tablero *t, const PiezaActual *p, int puntaje, int nivel, int lineasCompletas, const char user[4], char siguienteTipo, int modo){
  graficosComenzarFrame(15);
  int tableroW = t->columnas * pant->pixelesCelda + (t->columnas - 1) * pant->pxPadding;
  int tableroH = t->filasVisibles * pant->pixelesCelda + (t->filasVisibles - 1) * pant->pxPadding;

  int margin = 10;
  int top = pant->anchoVentana == 320 ? 15 : 45;
  int gap = 10;

  int tableroX = t->columnas < 12 ? pant->tableroOffsetX : pant->anchoVentana - (t->columnas * pant->pixelesCelda) - ((t->columnas - 1) * pant->pxPadding) - margin;
  int tableroY = pant->tableroOffsetY;

  int panelIzqX = margin;
  int panelIzqY = top;
  int panelIzqW = tableroX - gap - panelIzqX;
  int panelIzqH = tableroH;

  int panelDerX = tableroX + tableroW + gap;
  int panelDerY = top;
  int panelDerW = pant->anchoVentana - panelDerX - margin;
  int panelDerH = tableroH;

  int escalaFuente, gapEstadisticas, gapTitulo, escalaCharTitulo;

  if (pant->anchoVentana == 320){
    escalaFuente = 1;
    gapTitulo = 15;
    gapEstadisticas = 33;
    escalaCharTitulo = 1;
  } else {
    escalaFuente = 2;
    gapTitulo = 20;
    gapEstadisticas = 80;
    escalaCharTitulo = 3;
  };

  if (t->columnas < 12){
    graficosDibujarPanelIzq(panelIzqX, panelIzqY, panelIzqW, panelIzqH, escalaFuente, escalaCharTitulo, gapEstadisticas, gapTitulo, puntaje, nivel, lineasCompletas, user);
    graficosDibujarPanelDerecho(panelDerX, panelDerY, panelDerW, panelDerH, siguienteTipo, pant);
  } else {
    graficosDibujarPanelIzqGrande(panelIzqX, panelIzqY, panelIzqW, panelIzqH, siguienteTipo, pant, puntaje, nivel, lineasCompletas);
  }

  graficosDibujarRect(tableroX - 4, tableroY - 4, tableroW + 8, tableroH + 8, 12);
  graficosDibujarBorde(tableroX - 4, tableroY - 4, tableroW + 8, tableroH + 8, 14, 1);

  graficosDibujarTablero(pant, t, p, tableroX, tableroY);

  // fuenteDibujarChar(FUENTE_GRANDE, 'T', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2), 2, PAL_T, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'E', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 13 * escalaCharTitulo, 2, PAL_O, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'T', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 26 * escalaCharTitulo, 2, PAL_T, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'R', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 39 * escalaCharTitulo, 2, PAL_J, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'I', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 52 * escalaCharTitulo, 2, PAL_I, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'S', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 65 * escalaCharTitulo, 2, PAL_S, escalaCharTitulo);

  const char *titulo = "TETRIS";
  int charW = 13 * escalaCharTitulo;
  int totalW = charW * strlen(titulo);
  int startX = tableroX + (tableroW / 2) - (totalW / 2);
  int colores[6] = { PAL_T, PAL_O, PAL_T, PAL_J, PAL_I, PAL_S };

  for (int i = 0; i < (int)strlen(titulo); i++) {
    if (modo == 0){
      fuenteDibujarChar(FUENTE_GRANDE, titulo[i], startX + i * charW, 2, colores[i], escalaCharTitulo);
    } else {
      fuenteDibujarChar(FUENTE_GRANDE, titulo[i], startX + i * charW, 2, 17, escalaCharTitulo);
    }
  }

  graficosPresentarFrame();
}

void graficosDibujarMenu(const Pantalla* pant, int modo, int opcionMenu){
  graficosComenzarFrame(15);

  int escalaTexto, escalaCharTitulo, botonH, botonJugarW, botonConfigW;

  if (pant->anchoVentana == 320){
    escalaTexto = 1;
    escalaCharTitulo = 2;
    botonJugarW = 90;
    botonConfigW = 210;
    botonH = 25;
  } else {
    escalaTexto = 2;
    escalaCharTitulo = 3;
    botonJugarW = 170;
    botonConfigW = 370;
    botonH = 50;
  }

  fuenteDibujarTexto(FUENTE_GRANDE, "MENU", pant->anchoVentana / 2 - ((13 * escalaTexto * strlen("MENU")) / 2), pant->altoVentana / 4, PAL_REFLEJO, escalaTexto, 1);

  // fuenteDibujarChar(FUENTE_GRANDE, 'T', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2), 20, PAL_T, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'E', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 13 * escalaCharTitulo, 20, PAL_O, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'T', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 26 * escalaCharTitulo, 20, PAL_T, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'R', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 39 * escalaCharTitulo, 20, PAL_J, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'I', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 52 * escalaCharTitulo, 20, PAL_I, escalaCharTitulo);
  // fuenteDibujarChar(FUENTE_GRANDE, 'S', pant->anchoVentana / 2 - ((13 * escalaCharTitulo * strlen("TETRIS")) / 2) + 65 * escalaCharTitulo, 20, PAL_S, escalaCharTitulo);

  const char *titulo = "TETRIS";
  int charW = 13 * escalaCharTitulo;
  int colores[6] = { PAL_T, PAL_O, PAL_T, PAL_J, PAL_I, PAL_S };

  for (int i = 0; i < (int)strlen(titulo); i++) {
    if (modo == 0){
      fuenteDibujarChar(FUENTE_GRANDE, titulo[i], ((pant->anchoVentana / 2) - ((charW * strlen("TETRIS")) / 2)) + i * charW, 10, colores[i], escalaCharTitulo);
    } else {
      fuenteDibujarChar(FUENTE_GRANDE, titulo[i], ((pant->anchoVentana / 2) - ((charW * strlen("TETRIS")) / 2)) + i * charW, 10, 17, escalaCharTitulo);
    }
  }

  int colorBordeJugar = opcionMenu == 0 ? 16 : 14;
  int colorBordeConfig = opcionMenu == 1 ? 16 : 14;

  graficosDibujarBorde(((pant->anchoVentana / 2) - (botonJugarW / 2)), pant->altoVentana / 2, botonJugarW, botonH, colorBordeJugar, 1);
  fuenteDibujarTexto(FUENTE_GRANDE, "JUGAR", ((pant->anchoVentana / 2) - ((12 * escalaTexto * strlen("JUGAR")) / 2)), pant->altoVentana / 2 + ((botonH / 2) - 6), PAL_REFLEJO, escalaTexto, 1);

  graficosDibujarBorde(((pant->anchoVentana / 2) - (botonConfigW / 2)), pant->altoVentana / 2 + (botonH + 10), botonConfigW, botonH, colorBordeConfig, 1);
  fuenteDibujarTexto(FUENTE_GRANDE, "CONFIGURACION", ((pant->anchoVentana / 2) - ((12 * escalaTexto * strlen("CONFIGURACION")) / 2)), pant->altoVentana / 2 + ((botonH / 2) - 6) + (botonH + 10), PAL_REFLEJO, escalaTexto, 1);

  graficosPresentarFrame();
}

void graficosDibujarPausa(const Pantalla* pant){
  graficosComenzarFrame(15);

  int escala = pant->anchoVentana == 320 ? 1 : 2;

  fuenteDibujarTexto(FUENTE_CHICA, "pausa", (pant->anchoVentana / 2) - ((6 * escala * strlen("pausa") / 2)), pant->altoVentana / 2, PAL_REFLEJO, escala, 1);
  fuenteDibujarTexto(FUENTE_CHICA, "pulsa -p- para continuar", (pant->anchoVentana / 2) - ((6 * escala * strlen("pulsa -p- para continuar") / 2)), (pant->altoVentana / 2) + 20, PAL_REFLEJO, escala, 1);

  graficosPresentarFrame();
}
/*
void graficosDibujarGameOver(const Pantalla* pant){
  graficosComenzarFrame(0);

  int escalaTexto, escalaChar, botonW, botonH, separacionBotones;

  if (pant->anchoVentana == 320){
    escalaTexto = 1;
    escalaChar = 1;
    botonW = 25;
    botonH = 25;
    separacionBotones = 10;
  } else {
    escalaTexto = 2;
    escalaChar = 3;
    botonW = 50;
    botonH = 50;
    separacionBotones = 30;
  }

  fuenteDibujarTexto(FUENTE_GRANDE, "- GAME OVER -", (pant->anchoVentana / 2) - ((13 * escalaTexto * strlen("- GAME OVER -") / 2)), pant->altoVentana / 4, 8, escalaTexto, 1);

  graficosDibujarRect(((pant->anchoVentana / 2) - (botonW / 2)), pant->altoVentana - (pant->altoVentana / 2) - 10, botonW, botonH, 12);
  graficosDibujarRect(((pant->anchoVentana / 2) - (botonW / 2)) + 2, (pant->altoVentana - (pant->altoVentana / 2)) - 8, botonW, botonH, 0);
  graficosDibujarBorde(((pant->anchoVentana / 2) - (botonW / 2)) + 2, (pant->altoVentana - (pant->altoVentana / 2)) - 8, botonW, botonH, 14, 1);
  fuenteDibujarChar(FUENTE_GRANDE, 'R', ((pant->anchoVentana / 2) - ((13 * escalaChar) / 2)), ((pant->altoVentana - (pant->altoVentana / 2)) - 8) + ((botonH - (12 * escalaChar)) / 2), PAL_REFLEJO, escalaChar);

  fuenteDibujarTexto(FUENTE_CHICA, "volver a jugar", (pant->anchoVentana / 2) - ((6 * escalaTexto * strlen("volver a jugar")) / 2), (pant->altoVentana - (pant->altoVentana / 2) - (botonH / 2)) - 10, PAL_REFLEJO, escalaTexto, 1);

  graficosDibujarRect(((pant->anchoVentana / 2) - (botonW / 2)), pant->altoVentana - (pant->altoVentana / 2) + botonH + separacionBotones, botonW, botonH, 12);
  graficosDibujarRect(((pant->anchoVentana / 2) - (botonW / 2)) + 2, (pant->altoVentana - (pant->altoVentana / 2)) + botonH + separacionBotones + 2, botonW, botonH, 0);
  graficosDibujarBorde(((pant->anchoVentana / 2) - (botonW / 2)) + 2, (pant->altoVentana - (pant->altoVentana / 2)) + botonH + separacionBotones + 2, botonW, botonH, 14, 1);
  fuenteDibujarChar(FUENTE_GRANDE, 'M', ((pant->anchoVentana / 2) - ((13 * escalaChar) / 2)), ((pant->altoVentana - (pant->altoVentana / 2))) + ((botonH - (12 * escalaChar)) / 2) + botonH + separacionBotones + 2, PAL_REFLEJO, escalaChar);

  fuenteDibujarTexto(FUENTE_CHICA, "volver al menu", (pant->anchoVentana / 2) - ((6 * escalaTexto * strlen("volver al menu")) / 2), (pant->altoVentana - (pant->altoVentana / 2) - (botonH / 2)) + botonH + separacionBotones + 2, PAL_REFLEJO, escalaTexto, 1);


  graficosPresentarFrame();
}
*/
void graficosDibujarGameOver(const Pantalla* pant,Leaderboard *lb,int puntaje)
{
    graficosComenzarFrame(0);

    int escalaTexto, escalaChar;
    int botonW, botonH;

    if (pant->anchoVentana == 320)
    {
        escalaTexto = 1;
        escalaChar = 1;
        botonW = 25;
        botonH = 25;
    }
    else
    {
        escalaTexto = 2;
        escalaChar = 3;
        botonW = 50;
        botonH = 50;
    }


    fuenteDibujarTexto(FUENTE_GRANDE,"- GAME OVER -",(pant->anchoVentana / 2)- ((13 * escalaTexto * strlen("- GAME OVER -")) / 2),20,8,escalaTexto,1);


    int botonY = pant->altoVentana - botonH - 20;

    int menuX = 40;

    graficosDibujarRect(menuX, botonY, botonW, botonH, 12);
    graficosDibujarRect(menuX + 2, botonY + 2, botonW, botonH, 0);
    graficosDibujarBorde(menuX + 2, botonY + 2, botonW, botonH, 14, 1);

    fuenteDibujarChar(FUENTE_GRANDE,'M',menuX + ((botonW - (12 * escalaChar)) / 2),botonY + ((botonH - (12 * escalaChar)) / 2),PAL_REFLEJO,escalaChar);

    fuenteDibujarTexto(FUENTE_CHICA,"MENU",menuX - 5,botonY - 18,PAL_REFLEJO,escalaTexto,1);


    int retryX = pant->anchoVentana - botonW - 40;

    graficosDibujarRect(retryX, botonY, botonW, botonH, 12);
    graficosDibujarRect(retryX + 2, botonY + 2, botonW, botonH, 0);
    graficosDibujarBorde(retryX + 2, botonY + 2, botonW, botonH, 14, 1);

    fuenteDibujarChar(FUENTE_GRANDE,'R',retryX + ((botonW - (12 * escalaChar)) / 2),botonY + ((botonH - (12 * escalaChar)) / 2),PAL_REFLEJO,escalaChar);

    fuenteDibujarTexto(FUENTE_CHICA,"RETRY",retryX - 2,botonY - 18,PAL_REFLEJO,escalaTexto,1);

    graficosPresentarFrame();
}

void graficosDibujarConfig(const Pantalla* pant, const char user[4], int cursor, int configPaso, int modoSel, int velSel, int paletaSel){
  graficosComenzarFrame(15);

  int escalaChar, escalaTexto, anchoBoton, altoBoton, siguienteBloque;

  if (pant->anchoVentana == 320){
    escalaChar = 1;
    escalaTexto = 1;
    anchoBoton = 70;
    altoBoton = 20;
    siguienteBloque = 30;
  } else {
    escalaChar = 3;
    escalaTexto = 2;
    anchoBoton = 320;
    altoBoton = 80;
    siguienteBloque = 100;
  }

  int startX = (pant->anchoVentana / 2);
  int startY = pant->altoVentana / 4;

  for (int i = 0; i < 3; i++){
    int x = (startX - ((12 * escalaChar * 3) / 2)) + i * (12 * escalaChar + 5);
    int color;
    if (cursor == i && configPaso == 0){
      color = 16;
    } else {
      color = 11;
    }
    fuenteDibujarChar(FUENTE_GRANDE, user[i], x, startY, color, escalaChar);
  }

  int bx = (startX - ((12 * escalaChar * 3) / 2)) + cursor * (12 * escalaChar + 5);
  int by = startY - (13 * escalaChar);
  uint8_t colorFlecha = configPaso == 0 ? PAL_REFLEJO : 22;
  fuenteDibujarTexto(FUENTE_CHICA, "jugador", startX - ((7 * escalaTexto * strlen("jugador")) / 2), startY - (12 * escalaChar * 2), PAL_REFLEJO, escalaTexto, 2);
  fuenteDibujarChar(FUENTE_GRANDE, '<', bx, by, colorFlecha, escalaChar);
  fuenteDibujarChar(FUENTE_GRANDE, '>', bx, by + (12 * escalaChar * 2), colorFlecha, escalaChar);

  uint8_t colorModoClasico = modoSel == 0 ? 16 : 14;
  uint8_t colorModoFacil = modoSel == 1 ? 16 : 14;
  uint8_t colorModoDificil = modoSel == 2 ? 16 : 14;

  fuenteDibujarTexto(FUENTE_CHICA, "modo", startX - ((7 * escalaTexto * strlen("modo")) / 2), startY + siguienteBloque, PAL_REFLEJO, escalaTexto, 2);

  fuenteDibujarTexto(FUENTE_NOMONO, "CLASICO", (startX - (anchoBoton * 2)) + (anchoBoton - (4 * escalaTexto * strlen("CLASICO"))) / 2, startY + siguienteBloque + (altoBoton / 2) + (5 * escalaTexto), PAL_REFLEJO, escalaTexto, 1);
  graficosDibujarBorde(startX - (anchoBoton * 2), startY + siguienteBloque + (altoBoton / 2), anchoBoton, altoBoton, colorModoClasico, 1);

  fuenteDibujarTexto(FUENTE_NOMONO, "DX FACIL", (startX - (anchoBoton / 2)) + (anchoBoton - (4 * escalaTexto * strlen("CLASICO"))) / 2, startY + siguienteBloque + (altoBoton / 2) + (5 * escalaTexto), PAL_REFLEJO, escalaTexto, 1);
  graficosDibujarBorde(startX - (anchoBoton / 2), startY + siguienteBloque + (altoBoton / 2), anchoBoton, altoBoton, colorModoFacil, 1);

  fuenteDibujarTexto(FUENTE_NOMONO, "DX DIFICIL", (startX + anchoBoton) + (anchoBoton - (4 * escalaTexto * strlen("CLASICO"))) / 2, startY + siguienteBloque + (altoBoton / 2) + (5 * escalaTexto), PAL_REFLEJO, escalaTexto, 1);
  graficosDibujarBorde(startX + anchoBoton, startY + siguienteBloque + (altoBoton / 2), anchoBoton, altoBoton, colorModoDificil, 1);

  uint8_t colorVel1 = velSel == 0 ? 16 : 14;
  uint8_t colorVel2 = velSel == 1 ? 16 : 14;
  uint8_t colorVel3 = velSel == 2 ? 16 : 14;
  
  fuenteDibujarTexto(FUENTE_CHICA, "velocidad", startX - ((7 * escalaTexto * strlen("velocidad")) / 2), startY + (siguienteBloque * 2) + 5, PAL_REFLEJO, escalaTexto, 2);
  
  fuenteDibujarChar(FUENTE_CHICA, '1', startX - (anchoBoton * 2) + (anchoBoton - (7 * escalaTexto)) / 2, startY + (siguienteBloque * 2) + (altoBoton / 2) + 5 + ((8 * escalaTexto) / 2), PAL_REFLEJO, escalaTexto);
  graficosDibujarBorde(startX - (anchoBoton * 2), startY + (siguienteBloque * 2) + (altoBoton / 2) + 5, anchoBoton, altoBoton, colorVel1, 1);

  fuenteDibujarChar(FUENTE_CHICA, '2', startX - (anchoBoton / 2) + (anchoBoton - (7 * escalaTexto)) / 2, startY + (siguienteBloque * 2) + (altoBoton / 2) + 5 + ((8 * escalaTexto) / 2), PAL_REFLEJO, escalaTexto);
  graficosDibujarBorde(startX - (anchoBoton / 2), startY + (siguienteBloque * 2) + (altoBoton / 2) + 5, anchoBoton, altoBoton, colorVel2, 1);

  fuenteDibujarChar(FUENTE_CHICA, '3', startX + anchoBoton + (anchoBoton - (7 * escalaTexto)) / 2, startY + (siguienteBloque * 2) + (altoBoton / 2) + 5 + ((8 * escalaTexto) / 2), PAL_REFLEJO, escalaTexto);
  graficosDibujarBorde(startX + anchoBoton, startY + (siguienteBloque * 2) + (altoBoton / 2) + 5, anchoBoton, altoBoton, colorVel3, 1);

  
  uint8_t colorPal1 = paletaSel == 0 ? 16 : 14;
  uint8_t colorPal2 = paletaSel == 1 ? 16 : 14;
  
  fuenteDibujarTexto(FUENTE_CHICA, "paleta", startX - ((7 * escalaTexto * strlen("paleta")) / 2), startY + (siguienteBloque * 3) + 10, PAL_REFLEJO, escalaTexto, 2);

  fuenteDibujarTexto(FUENTE_NOMONO, "CLASICA", (startX - anchoBoton - 5) + (anchoBoton - (4 * escalaTexto * strlen("CLASICO"))) / 2, startY + (siguienteBloque * 3) + (altoBoton / 2) + (5 * escalaTexto) + 10, PAL_REFLEJO, escalaTexto, 1);
  graficosDibujarBorde(startX - anchoBoton - 5, startY + (siguienteBloque * 3) + (altoBoton / 2) + 10, anchoBoton, altoBoton, colorPal1, 1);

  fuenteDibujarTexto(FUENTE_NOMONO, "DELUXE", (startX + 5) + (anchoBoton - (4 * escalaTexto * strlen("CLASICO"))) / 2, startY + (siguienteBloque * 3) + (altoBoton / 2) + (5 * escalaTexto) + 10, PAL_REFLEJO, escalaTexto, 1);
  graficosDibujarBorde(startX + 5, startY + (siguienteBloque * 3) + (altoBoton / 2) + 10, anchoBoton, altoBoton, colorPal2, 1);

  graficosPresentarFrame();
}

void graficosDibujarPreview(char tipo, int cx, int cy, int block, int pad, uint8_t color){
  if (!tipo) return;

  PiezaActual temp = {0};
  temp.tetromino = crearMatriz(4, 4);
  if (!temp.tetromino) return;

  cargaMatriz(temp.tetromino, 4, 4, '.');
  temp.tipo = tipo;
  cargaPieza(&temp);

  int minCol = 4, maxCol = -1;
  int minFila = 4, maxFila = -1;

  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      if (temp.tetromino[i][j] != tipo) continue;

      if (j < minCol) minCol = j;
      if (j > maxCol) maxCol = j;
      if (i < minFila) minFila = i;
      if (i > maxFila) maxFila = i;
    }
  }

  if (maxCol < 0 || maxFila < 0){
    destruyeMatriz(temp.tetromino, 4);
    return;
  }

  int anchoReal = (maxCol - minCol + 1) * block + (maxCol - minCol) * pad;
  int altoReal  = (maxFila - minFila + 1) * block + (maxFila - minFila) * pad;

  int sx = cx - (anchoReal / 2);
  int sy = cy - (altoReal / 2);

  for (int i = minFila; i <= maxFila; i++){
    for (int j = minCol; j <= maxCol; j++){
      if (temp.tetromino[i][j] != tipo) continue;

      int x = sx + (j - minCol) * (block + pad);
      int y = sy + (i - minFila) * (block + pad);

      graficosDibujarRect(x, y, block, block, color);

      if (block > 2){
        graficosDibujarRect(x, y, block - 1, 1, PAL_REFLEJO);
        graficosDibujarRect(x, y, 1, block - 1, PAL_REFLEJO);
      }
    }
  }

  destruyeMatriz(temp.tetromino, 4);
}

void graficosDibujarPanelIzq(int panelIzqX, int panelIzqY, int panelIzqW, int panelIzqH, int escalaFuente, int escalaCharTitulo, int gapEstadisticas, int gapTitulo, int puntaje, int nivel, int lineasCompletas, const char user[]){
  graficosDibujarRect(panelIzqX, panelIzqY, panelIzqW, panelIzqH, 10);
  graficosDibujarBorde(panelIzqX, panelIzqY, panelIzqW, panelIzqH, 14, 1);

  fuenteDibujarTexto(FUENTE_CHICA, "estadisticas", panelIzqX + ((panelIzqW - (7 * escalaFuente * strlen("estadisticas"))) / 2), panelIzqY + 5, PAL_REFLEJO, escalaFuente, 1);

  graficosDibujarRect(panelIzqX, panelIzqY + gapTitulo, panelIzqW, 1, 14);

  // PANEL IZQ - PUNTAJE
  char scoreText[16];
  sprintf(scoreText, "%d", puntaje);
  fuenteDibujarChar(FUENTE_GRANDE, '?', panelIzqX + (panelIzqW / 10), panelIzqY + gapTitulo + (gapEstadisticas / 2) - ((12 * escalaFuente) / 2), 16, escalaFuente);
  fuenteDibujarTexto(FUENTE_CHICA, "puntos:", panelIzqX + (panelIzqW / 3), panelIzqY + gapTitulo + (gapEstadisticas / 4) - ((8 * escalaFuente) / 2), PAL_REFLEJO, escalaFuente, 1);
  fuenteDibujarTexto(FUENTE_CHICA, scoreText, panelIzqX + (panelIzqW / 2), panelIzqY + gapTitulo + (gapEstadisticas / 2), 16, escalaFuente, 1);

  graficosDibujarRect(panelIzqX, panelIzqY + gapTitulo + gapEstadisticas, panelIzqW, 1, 14);

  // PANEL IZQ - NIVEL
  char nivelText[5];
  sprintf(nivelText, "%d", nivel);
  fuenteDibujarChar(FUENTE_GRANDE, '!', panelIzqX + (panelIzqW / 10), panelIzqY + gapTitulo + gapEstadisticas + (gapEstadisticas / 2) - ((12 * escalaFuente) / 2), PAL_I, escalaFuente);
  fuenteDibujarTexto(FUENTE_CHICA, "nivel:", panelIzqX + (panelIzqW / 3), panelIzqY + gapTitulo + gapEstadisticas + (gapEstadisticas / 4) - ((8 * escalaFuente) / 2), PAL_REFLEJO, escalaFuente, 1);
  fuenteDibujarTexto(FUENTE_CHICA, nivelText, panelIzqX + (panelIzqW / 2), panelIzqY + gapTitulo + gapEstadisticas + (gapEstadisticas / 2), PAL_I, escalaFuente, 1);

  graficosDibujarRect(panelIzqX, panelIzqY + gapTitulo + (gapEstadisticas * 2), panelIzqW, 1, 14);

  // PANEL IZQ - LINEAS COMPLETAS
  char lineasText[10];
  sprintf(lineasText, "%d", lineasCompletas);
  fuenteDibujarChar(FUENTE_GRANDE, ']', panelIzqX + (panelIzqW / 10), panelIzqY + gapTitulo + (gapEstadisticas * 2) + (gapEstadisticas / 2) - ((12 * escalaFuente) / 2), PAL_S, escalaFuente);
  fuenteDibujarTexto(FUENTE_CHICA, "lineas:", panelIzqX + (panelIzqW / 3), panelIzqY + gapTitulo + (gapEstadisticas * 2) + (gapEstadisticas / 4) - ((8 * escalaFuente) / 2), PAL_REFLEJO, escalaFuente, 1);
  fuenteDibujarTexto(FUENTE_CHICA, lineasText, panelIzqX + (panelIzqW / 2), panelIzqY + gapTitulo + (gapEstadisticas * 2) + (gapEstadisticas / 2), PAL_S, escalaFuente, 1);

  graficosDibujarRect(panelIzqX, panelIzqY + gapTitulo + (gapEstadisticas * 3), panelIzqW, 1, 14);

  // PANEL IZQ - RECORD
  char recordText[16];
  sprintf(recordText, "%d", 0);
  fuenteDibujarChar(FUENTE_GRANDE, '}', panelIzqX + (panelIzqW / 10), panelIzqY + gapTitulo + (gapEstadisticas * 3) + (gapEstadisticas / 2) - ((12 * escalaFuente) / 2), 16, escalaFuente);
  fuenteDibujarTexto(FUENTE_CHICA, "record:", panelIzqX + (panelIzqW / 3), panelIzqY + gapTitulo + (gapEstadisticas * 3) + (gapEstadisticas / 4) - ((8 * escalaFuente) / 2), PAL_REFLEJO, escalaFuente, 1);
  fuenteDibujarTexto(FUENTE_CHICA, recordText, panelIzqX + (panelIzqW / 2), panelIzqY + gapTitulo + (gapEstadisticas * 3) + (gapEstadisticas / 2), 16, escalaFuente, 1);

  graficosDibujarRect(panelIzqX, panelIzqY + gapTitulo + (gapEstadisticas * 4), panelIzqW, 1, 14);

  // PANEL IZQ - USUARIO
  fuenteDibujarChar(FUENTE_GRANDE, user[0], panelIzqX + (panelIzqW / 4) - ((12 * escalaCharTitulo) / 2), panelIzqY + gapTitulo + (gapEstadisticas * 4) + (gapEstadisticas / 2) - ((12 * escalaCharTitulo) / 2), 2, escalaCharTitulo);
  fuenteDibujarChar(FUENTE_GRANDE, user[1], panelIzqX + (panelIzqW / 2) - ((12 * escalaCharTitulo) / 2), panelIzqY + gapTitulo + (gapEstadisticas * 4) + (gapEstadisticas / 2) - ((12 * escalaCharTitulo) / 2), 2, escalaCharTitulo);
  fuenteDibujarChar(FUENTE_GRANDE, user[2], panelIzqX + (panelIzqW - (panelIzqW / 4)) - ((12 * escalaCharTitulo) / 2), panelIzqY + gapTitulo + (gapEstadisticas * 4) + (gapEstadisticas / 2) - ((12 * escalaCharTitulo) / 2), 2, escalaCharTitulo);
}

void graficosDibujarPanelDerecho(int panelDerX, int panelDerY, int panelDerW, int panelDerH, char siguienteTipo, const Pantalla* pant){
  // PANEL DER ARRIBA - PROX PIEZA
    graficosDibujarRect(panelDerX, panelDerY - 1, panelDerW, (panelDerH / 2), 10);
    graficosDibujarBorde(panelDerX, panelDerY - 1, panelDerW, (panelDerH / 2), 14, 1);

    int escalaTexto = pant->anchoVentana == 320 ? 1 : 2;

    fuenteDibujarTexto(FUENTE_CHICA, "siguiente\npieza:", panelDerX + 10, panelDerY + 10, PAL_REFLEJO, escalaTexto, 1);
    graficosDibujarBorde(panelDerX + 5, panelDerY + (panelDerH / 5), panelDerW - 10, panelDerH / 4, 14, 1);

    uint8_t colorPreview = obtenerColorCelda(siguienteTipo);
    int previewBlock = pant->anchoVentana == 320 ? 12 : 24;
    int boxX = panelDerX + 5;
    int boxY = panelDerY + (panelDerH / 5);
    int boxW = panelDerW - 10;
    int boxH = panelDerH / 4;

    graficosDibujarPreview(siguienteTipo, boxX + (boxW / 2), boxY + (boxH / 2), previewBlock, 2, colorPreview);

    // PANEL DER ABAJO - COMO JUGAR
    graficosDibujarRect(panelDerX, panelDerY + (panelDerH / 2) + 1, panelDerW, (panelDerH / 2), 10);
    graficosDibujarBorde(panelDerX, panelDerY + (panelDerH / 2) + 1, panelDerW, (panelDerH / 2), 14, 1);

    int siguienteBorde = 0;
    int bordeW, bordeH, spacingX, spacingY, escalaChar;

    if (pant->anchoVentana == 320){
      bordeW = 16;
      bordeH = 16;
      spacingX = 2;
      spacingY = 1;
      escalaChar = 1;
    } else {
      bordeW = 30;
      bordeH = 30;
      spacingX = 5;
      spacingY = 10;
      escalaChar = 2;
    }

    for (int i = 0; i < 4; i++){
      graficosDibujarBorde(panelDerX + (spacingX * 2), (panelDerY + (panelDerH / 2) + 2) + siguienteBorde + spacingY, bordeW, bordeH, PAL_REFLEJO, 1);
      siguienteBorde += bordeH + spacingY;
    }

    siguienteBorde = 0;
    const char controles[9] = {"ASDFQEP)"};
    const char *labels[] = {
      "MOVER\nIZQ",
      "ABAJO",
      "MOVER\nDER",
      "FREEZE",
      "ROTAR\nIZQ",
      "ROTAR\nDER",
      "PAUSA",
      "SALIR"
    };

    for (int i = 0; i < 4; i++){
      fuenteDibujarChar(FUENTE_GRANDE, controles[i], panelDerX + (spacingX * 2) + ((bordeW - (12 * escalaChar)) / 2), (panelDerY + (panelDerH / 2) + 1) + siguienteBorde + spacingY + ((bordeH - (12 * escalaChar)) / 2), 11, escalaChar);
      fuenteDibujarTexto(FUENTE_NOMONO, labels[i], panelDerX + bordeW + (spacingX * 2 + 2), (panelDerY + (panelDerH / 2) + 1) + siguienteBorde + spacingY + 2, PAL_REFLEJO, escalaChar, 1);
      siguienteBorde += bordeH + spacingY;
    }

    siguienteBorde = 0;

    for (int i = 0; i < 4; i++){
      graficosDibujarBorde(panelDerX + (panelDerW / 2) + (spacingX * 2), (panelDerY + (panelDerH / 2) + 2) + siguienteBorde + spacingY, bordeW, bordeH, PAL_REFLEJO, 1);
      siguienteBorde += bordeH + spacingY;
    }

    siguienteBorde = 0;

    for (int i = 4; i < 8; i++){
      fuenteDibujarChar(FUENTE_GRANDE, controles[i], panelDerX + (panelDerW / 2) + (spacingX * 2) + ((bordeW - (12 * escalaChar)) / 2), (panelDerY + (panelDerH / 2) + 1) + siguienteBorde + spacingY + ((bordeH - (12 * escalaChar)) / 2), 11, escalaChar);
      fuenteDibujarTexto(FUENTE_NOMONO, labels[i], panelDerX + (panelDerW / 2) + bordeW + (spacingX * 2 + 2), (panelDerY + (panelDerH / 2) + 1) + siguienteBorde + spacingY + 2, PAL_REFLEJO, escalaChar, 1);
      siguienteBorde += bordeH + spacingY;
    }

    graficosDibujarBorde(panelDerX + (spacingX * 2), (panelDerY + (panelDerH / 2) + 2) + siguienteBorde + spacingY, bordeW * 3, bordeH, PAL_REFLEJO, 1);
    fuenteDibujarTexto(FUENTE_CHICA, "space", panelDerX + (spacingX) + (((bordeW * 3) - (6 * escalaChar * strlen("space"))) / 2), (panelDerY + (panelDerH / 2) + 1) + siguienteBorde + spacingY + (bordeH / 2), 11, escalaChar, 1);
    fuenteDibujarTexto(FUENTE_NOMONO, "HARD\nDROP", panelDerX + (bordeW * 3) + (spacingX * 2 + 2), (panelDerY + (panelDerH / 2) + 1) + siguienteBorde + spacingY + 2, PAL_REFLEJO, escalaChar, 1);
}

void graficosDibujarPanelIzqGrande(int panelGrandeX, int panelGrandeY, int panelGrandeW, int panelGrandeH, char siguienteTipo, const Pantalla* pant, int puntaje, int nivel, int filasCompletas){
  graficosDibujarRect(panelGrandeX, panelGrandeY - 1, panelGrandeW, (panelGrandeH / 2), 10);
  graficosDibujarBorde(panelGrandeX, panelGrandeY - 1, panelGrandeW, (panelGrandeH / 2), 14, 1);

  int escalaTexto = pant->anchoVentana == 320 ? 1 : 2;

  fuenteDibujarTexto(FUENTE_CHICA, "siguiente pieza:", panelGrandeX + 10, panelGrandeY + 10, PAL_REFLEJO, escalaTexto, 1);
  graficosDibujarBorde(panelGrandeX + 5, panelGrandeY + (panelGrandeH / 5), panelGrandeW - 10, panelGrandeH / 4, 14, 1);

  uint8_t colorPreview = obtenerColorCelda(siguienteTipo);
  int previewBlock = pant->anchoVentana == 320 ? 12 : 24;
  int boxX = panelGrandeX + 5;
  int boxY = panelGrandeY + (panelGrandeH / 5);
  int boxW = panelGrandeW - 10;
  int boxH = panelGrandeH / 4;

  graficosDibujarPreview(siguienteTipo, boxX + (boxW / 2), boxY + (boxH / 2), previewBlock, 2, colorPreview);

  graficosDibujarRect(panelGrandeX, panelGrandeY + (panelGrandeH / 2) + 1, panelGrandeW, (panelGrandeH / 2), 10);
  graficosDibujarBorde(panelGrandeX, panelGrandeY + (panelGrandeH / 2) + 1, panelGrandeW, (panelGrandeH / 2), 14, 1);

  int abajoY = panelGrandeY + (panelGrandeH / 2) + 1;
  int abajoH = panelGrandeH / 2;
  int celdaW = panelGrandeW / 2;
  int celdaH = abajoH / 2;
  int pad = 6;

  const char* valor;

  char scoreText[16];
  sprintf(scoreText, "%d", puntaje);

  char nivelText[5];
  sprintf(nivelText, "%d", nivel);

  char lineasText[10];
  sprintf(lineasText, "%d", filasCompletas);
  
  char recordText[16];
  sprintf(recordText, "%d", 0);

  const char *labels[4] = { "PUNTOS", "NIVEL", "LINEAS", "RECORD" };

  for (int i = 0; i < 4; i++){
    int col = i % 2;
    int fila = i / 2;
    int cx = panelGrandeX + col * celdaW;
    int cy = abajoY + fila * celdaH;

    switch (i){
      case 0: valor = scoreText; break;
      case 1: valor = nivelText; break;
      case 2: valor = lineasText; break;
      default: valor = recordText; break;
    }

    graficosDibujarRect(cx + 2, cy + 2, celdaW - 4, celdaH - 4, 10);
    graficosDibujarBorde(cx + 2, cy + 2, celdaW - 4, celdaH - 4, 14, 1);

    fuenteDibujarTexto(FUENTE_NOMONO, labels[i], cx + pad + 2, cy + 6, PAL_REFLEJO, escalaTexto, 1);

    fuenteDibujarTexto(FUENTE_CHICA, valor, cx + (celdaW / 2) - (6 * 4), cy + (celdaH / 2), 16, escalaTexto, 1);
  }

  graficosDibujarRect(panelGrandeX + (panelGrandeW / 2), abajoY + 2, 1, abajoH - 4, 14);
  graficosDibujarRect(panelGrandeX + 2, abajoY + (abajoH / 2), panelGrandeW - 4, 1, 14);
}