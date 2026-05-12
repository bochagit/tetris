#ifndef FUENTES_H_INCLUDED
#define FUENTES_H_INCLUDED

#include <stdint.h>

#define FONT_WIDTH 12
#define FONT_HEIGHT 12

void fuenteDibujarChar(char c, int x, int y, uint8_t color, int scale);
void fuenteDibujarTexto(const char *s, int x, int y, uint8_t color, int scale, int spacing);

#endif // FUENTES_H_INCLUDED
