#ifndef EXPRESIONESREGULARES_H
#define EXPRESIONESREGULARES_H

#include <regex.h>

/**
 * @brief Compila una expresión regular utilizando "regex.h"
 *
 * @param patron El patrón de la expresión regular.
 * @param banderas Las banderas de compilación.
 * @return La expresión regular o aborta el proceso si falla.
 */
regex_t compilarER(const char *patron, int banderas);

#endif //EXPRESIONESREGULARES_H
