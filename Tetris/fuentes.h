#ifndef FUENTES_H_INCLUDED
#define FUENTES_H_INCLUDED

#include <stdint.h>
#include <string.h>

#define GRANDE_W 12
#define GRANDE_H 12

#define CHICA_W 6
#define CHICA_H 8

#define NOMONO_W 4
#define NOMONO_H 5

#define CANT_LETRAS_GRANDES 46
#define CANT_LETRAS_CHICAS 39
#define CANT_LETRAS_NOMONO 27

typedef enum {
  FUENTE_GRANDE,
  FUENTE_CHICA,
  FUENTE_NOMONO,
} TipoFuente;

typedef struct {
  char c;
  int ancho;
  int alto;
  int avance;
  const char** dibujo;
} Letra;

void fuenteDibujarChar(TipoFuente tipo, char c, int x, int y, uint8_t color, int scale);
void fuenteDibujarTexto(TipoFuente tipo, const char *s, int x, int y, uint8_t color, int scale, int spacing);

#endif // FUENTES_H_INCLUDED
