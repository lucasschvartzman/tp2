#ifndef LOG_H
#define LOG_H

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_RESET    "\x1b[0m"

#include <stdio.h>

/**
 * @brief Imprime un mensaje de información con color azul en stdout.
 */
#define logMessage(format,...) \
printf(ANSI_COLOR_BLUE format ANSI_COLOR_RESET, ##__VA_ARGS__)

/**
 * @brief Imprime un mensaje de error con color rojo en stderr.
 */
#define logError(format,...) \
fprintf(stderr, ANSI_COLOR_RED "[ERROR] " format ANSI_COLOR_RESET, ##__VA_ARGS__)

/**
 * @brief Imprime un mensaje de debug en color amarillo.
 *
 * @note Solo debe usarse para desarrollo, son detalles internos.
 */
#define logTrace(format,...) \
printf(ANSI_COLOR_YELLOW "[DESARROLLO] " format ANSI_COLOR_RESET, ##__VA_ARGS__)

// Flag que habilita o deshabilita los mensajes de desarrollo.
#define DESARROLLO 1

/**
 * @brief Muestra un mensaje de error si tmalloc() falla indicando dónde fue llamada.
 */
#define logMemoryError() \
if (DESARROLLO) logTrace("La funcion tmalloc() devolvió NULL cuando se ejecuto en: %s()\n",__func__)

/**
 * @brief Permite que la terminal muestre colores ANSI de forma correcta.
 *
 * En sistemas de tipo Windows, realiza algunas operaciones para lograrlo.
 *
 * En sistemas tipo UNIX no realiza ninguna acción (está pre-activado).
 */
void activarColoresTerminal();

#endif //LOG_H