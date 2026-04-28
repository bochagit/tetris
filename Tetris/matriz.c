#include "matriz.h"

char** crearMatriz( int cantFilas, int cantColumnas)
{
    char **mat;
    char **i;
    mat=malloc(cantFilas*sizeof(char*));
    if(!mat)
        return NULL;
    i=mat;
    while(i<(mat+cantFilas))
    {
        *i=malloc(cantColumnas*sizeof(char));
        if(!*i)
        {
            for(i-=1;i>mat;i--)
            {
                free(*i);
            }
            free(mat);
            return NULL;
        }
        i++;
    }
    return mat;
}

bool destruyeMatriz(char **mat, int cantFilas)
{
    if(mat == NULL)
        return false;
    char **i;
    for(i=(mat+(cantFilas-1)); i>mat; i--)
    {
        free(*i);
    }
    free(mat);

    return true;
}
bool cargaMatriz(char **mat, int cantFilas, int cantColumnas)
{
    // Validamos que la matriz exista antes de intentar cargarla
    if (mat == NULL) {
        return false;
    }

    char **i = mat;
    char *j;

    while(i != (mat + cantFilas))
    {
        for(j = (*i); j < (*i) + cantColumnas; j++)
        {
            *j = 'A'; // Pod�s cambiar 'A' por lo que quieras cargar
        }
        i++;
    }

    return true;
}
void mostrarMatriz(char **mat, int cantFilas, int cantColumnas)
{
    if (mat == NULL) {
        printf("La matriz no existe (NULL).\n");
        return;
    }

    char **i;
    char *j;

    printf("Contenido de la matriz:\n");

    // Recorremos las filas
    for(i = mat; i < (mat + cantFilas); i++)
    {
        // Recorremos las columnas de la fila actual (*i)
        for(j = *i; j < (*i + cantColumnas); j++)
        {
            // Imprimimos el caracter apuntado por j y un espacio
            printf("%c ", *j);
        }
        // Hacemos un salto de l�nea al terminar cada fila
        printf("\n");
    }
}
