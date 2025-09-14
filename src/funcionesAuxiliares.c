#include "../include/main.h"

#include <stdio.h>
#include <string.h>

#include "../lib/include/log.h"

void procesarPuntoMostrar(const char letraPunto, const char *oracion, regex_t *er) {
    if (regexec(er, oracion, 0, NULL, 0) == 0) {
        logMessage("[PUNTO '%c']: %s\n\n", letraPunto, oracion);
    }
}

void procesarPuntoContar(const char *oracion, regex_t *er, const char *palabra,
                           int *cantidadOraciones, int *cantidadTotal) {
    if (regexec(er, oracion, 0, NULL, 0) == 0) {
        (*cantidadOraciones)++;
        const char *p = oracion;
        while ((p = strstr(p, palabra)) != NULL) {
            (*cantidadTotal)++;
            p += strlen(palabra);
        }
    }
}

int esFinDeOracion(const char caracterLeido, const char caracterSiguiente) {
    return caracterLeido == '.' &&
           (caracterSiguiente == ' ' || caracterSiguiente == '\n' || caracterSiguiente == '\r' || caracterSiguiente ==
            EOF);
}