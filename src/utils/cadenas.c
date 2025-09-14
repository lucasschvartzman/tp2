#include "../../include/utils/cadenas.h"

#include <ctype.h>

void eliminarEspaciosBlancosAlInicio(char *cadena) {
    const char *puntero = cadena;
    while (isspace((unsigned char) *puntero)) {
        puntero++;
    }
    if (puntero != cadena) {
        int i = 0;
        while (puntero[i]) {
            cadena[i] = puntero[i];
            i++;
        }
        cadena[i] = '\0';
    }
}