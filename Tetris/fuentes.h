#ifndef FUENTES_H_INCLUDED
#define FUENTES_H_INCLUDED

#include <stdint.h>

#define GRANDE_W 12
#define GRANDE_H 12

#define CHICA_W 6
#define CHICA_H 8

typedef enum {
  FUENTE_GRANDE,
  FUENTE_CHICA
} TipoFuente;

void fuenteDibujarChar(TipoFuente tipo, char c, int x, int y, uint8_t color, int scale);
void fuenteDibujarTexto(TipoFuente tipo, const char *s, int x, int y, uint8_t color, int scale, int spacing);

#endif // FUENTES_H_INCLUDED
