#include "../../include/utils/expresionesRegulares.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../lib/include/log.h"

regex_t compilarER(const char *patron, int banderas) {
    regex_t er;
    if (regcomp(&er, patron, banderas) != 0) {
        logError("No se pudo compilar la ER: %s\n", patron);
        exit(1);
    }
    return er;
}
