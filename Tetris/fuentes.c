#include "fuentes.h"
#include "graficos.h"

static const char font_E[FONT_HEIGHT][FONT_WIDTH + 1] = {
  "############",
  "############",
  "############",
  "###.........",
  "#######.....",
  "#######.....",
  "#######.....",
  "###.........",
  "############",
  "############",
  "############",
  "............"
};

static const char font_I[FONT_HEIGHT][FONT_WIDTH + 1] = {
  "############",
  "############",
  "############",
  "....####....",
  "....####....",
  "....####....",
  "....####....",
  "....####....",
  "############",
  "############",
  "############",
  "............"
};

static const char font_R[FONT_HEIGHT][FONT_WIDTH + 1] = {
  "##########..",
  "###########.",
  "###....#####",
  "###....#####",
  "###########.",
  "##########..",
  "#########...",
  "###.#####...",
  "###..#####..",
  "###...#####.",
  "###....#####",
  "............"
};

static const char font_S[FONT_HEIGHT][FONT_WIDTH + 1] = {
  "############",
  "############",
  "############",
  "###.........",
  "############",
  "############",
  "############",
  ".........###",
  "############",
  "############",
  "############",
  "............"
};

static const char font_T[FONT_HEIGHT][FONT_WIDTH + 1] = {
  "############",
  "############",
  "############",
  "....####....",
  "....####....",
  "....####....",
  "....####....",
  "....####....",
  "....####....",
  "....####....",
  "....####....",
  "............"
};

static const char font_BLANK[FONT_HEIGHT][FONT_WIDTH + 1] = {
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............"
};

static const char (*getCaracter(char c))[FONT_WIDTH + 1]{
  if (c == 'E') return font_E;
  if (c == 'I') return font_I;
  if (c == 'R') return font_R;
  if (c == 'S') return font_S;
  if (c == 'T') return font_T;
  return font_BLANK;
}

static void dibujarBloque(int x, int y, uint8_t color, int scale)
{
  for (int sy = 0; sy < scale; sy++) {
    for (int sx = 0; sx < scale; sx++) {
      gbt_dibujar_pixel(x + sx, y + sy, color);
    }
  }
}

void fuenteDibujarChar(char c, int x, int y, uint8_t color, int scale){
  if (scale < 1) scale = 1;
  const char (*f)[FONT_WIDTH + 1] = getCaracter(c);

  for (int fila = 0; fila < FONT_HEIGHT; fila++){
    for (int col = 0; col < FONT_WIDTH; col++){
      if (f[fila][col] != '#') continue;

      int px = x + col * scale;
      int py = y + fila * scale;

      dibujarBloque(px, py, color, scale);
      
      if (fila == 0 || col == 0){
        dibujarBloque(px, py, PAL_REFLEJO, 1);
      }
    }
  }
}

void fuenteDibujarTexto(const char *s, int x, int y, uint8_t color, int scale, int spacing){
  if (!s) return;
  int cx = x;
  int cy = y;
  int step = FONT_WIDTH * scale + spacing;

  const char *aux = s;

  while (*aux != '\0'){
    if (*aux == '\n'){
      cx = x;
      cy += FONT_HEIGHT * scale + spacing;
    } else {
      fuenteDibujarChar(*aux, cx, cy, color, scale);
      cx += step;
    }
    aux++;
  }
}
