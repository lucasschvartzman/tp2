#ifndef MAIN_H
#define MAIN_H

#define RUTA_ARCHIVO "breve_historia.txt"
#define ORACION_MAX 1024

#include <regex.h>

struct Estadisticas {
    int cantidadOraciones;
    int oracionesPeronismo;
    int totalPeronismo;
    int oracionesRadicalismo;
    int totalRadicalismo;
};

/**
 * @brief Procesa una oración a partir de una expresión regular.
 *
 * En caso de que se cumpla, se muestra por consola el resultado.
 *
 * @param letraPunto La letra del punto correspondiente
 * @param oracion La oración a procesar
 * @param er La expresión regular
 */
void procesarPuntoMostrar(char letraPunto, const char *oracion, regex_t *er);

/**
 * @brief Procesa una oración a partir de una expresión regular.
 *
 * En caso de que se cumpla, se rellenan los contadores respectivamente.
 *
 * @param oracion La oración a procesar
 * @param er La expresión regular
 * @param palabra La palabra que se quiere contar
 *
 * @param cantidadOraciones Almacena la cantidad total de oraciones que tienen esa palabra
 * @param cantidadTotal Almacena la cantidad total de veces que aparece esa palabra
 */
void procesarPuntoContar(const char *oracion, regex_t *er, const char *palabra, int *cantidadOraciones, int *cantidadTotal);

/**
 * @brief Indica si se delimitó una oración o no
 *
 * @param caracterLeido El carácter leído actualmente
 * @param caracterSiguiente El siguiente carácter a leer
 *
 * @note Se verifica para ambos tipos de codificación (sistemas UNIX y no UNIX). Recomendamos ver el informe para más información.
 */
static int esFinDeOracion(char caracterLeido, char caracterSiguiente);

#endif //MAIN_H
