#include "include/main.h"

#include "stdio.h"
#include "lib/include/log.h"

#include "include/utils/cadenas.h"
#include "include/utils/expresionesRegulares.h"

int main() {
    // Abrimos el archivo a analizar (en "RUTA_ARCHIVO"):
    FILE *f = fopen(RUTA_ARCHIVO, "r");
    if (f == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Inicializamos las estadisticas (los contadores) que se quieren analizar.
    struct Estadisticas estadisticas = {0};

    // Variables para el análisis:
    char oracion[ORACION_MAX];
    char caracterLeido;
    int indiceLectura = 0;
    int cantidadNombresAbreviados = 0;

    // Compilación de ERs para las consignas
    regex_t erPuntoB = compilarER("independencia", REG_ICASE | REG_EXTENDED);
    regex_t erPuntoC = compilarER("^El.*\\.$", REG_EXTENDED | REG_NOSUB);
    regex_t erPuntoD = compilarER("Sarmiento", REG_EXTENDED);
    regex_t erPuntoE = compilarER("(Sarmiento.*escuela|escuela.*Sarmiento)", REG_EXTENDED);
    regex_t erPuntoF = compilarER("peronismo", REG_EXTENDED);
    regex_t erPuntoG = compilarER("radicalismo", REG_EXTENDED);
    regex_t erPuntoH = compilarER("(180[1-9]|18[1-9][0-9]|1900)", REG_EXTENDED);
    regex_t erPuntoI = compilarER("((195[0-9]|1960).*Frondizi|Frondizi.*(195[0-9]|1960))",REG_EXTENDED);
    regex_t erPuntoJ = compilarER("(185[0-2])", REG_EXTENDED);

    // Compilación de ERs auxiliares
    regex_t erNombreAbreviado = compilarER("[A-Z]\\.$", REG_EXTENDED);

    // Bucle de ejecución principal:
    while ((caracterLeido = fgetc(f)) != EOF) {

        oracion[indiceLectura] = caracterLeido;

        char caracterSiguiente = fgetc(f);
        if (caracterSiguiente != EOF) {
            ungetc(caracterSiguiente, f);
        }

        indiceLectura++;

        if (esFinDeOracion(caracterLeido, caracterSiguiente)) {

            estadisticas.cantidadOraciones++;

            oracion[indiceLectura] = '\0';
            eliminarEspaciosBlancosAlInicio(oracion);

            // Procesamos cada uno de los puntos, mostrando o actualizando contadores (según corresponda):
            procesarPuntoMostrar('B', oracion, &erPuntoB);
            procesarPuntoMostrar('C', oracion, &erPuntoC);
            procesarPuntoMostrar('D', oracion, &erPuntoD);
            procesarPuntoMostrar('E', oracion, &erPuntoE);
            procesarPuntoContar(oracion, &erPuntoF, "peronismo",
                                  &estadisticas.oracionesPeronismo, &estadisticas.totalPeronismo);
            procesarPuntoContar(oracion, &erPuntoG, "radicalismo",
                                  &estadisticas.oracionesRadicalismo, &estadisticas.totalRadicalismo);
            procesarPuntoMostrar('H', oracion, &erPuntoH);
            procesarPuntoMostrar('I', oracion, &erPuntoI);
            procesarPuntoMostrar('J', oracion, &erPuntoJ);

            // Verificamos si encontramos un nombre abreviado (relevante para la cuenta total de oraciones):
            if (regexec(&erNombreAbreviado, oracion, 0, NULL, 0) == 0) {
                cantidadNombresAbreviados++;
            }

            indiceLectura = 0;
        }
    }

    // Para más información acerca de este calculo, sugerimos leer el informe.
    const int cantidadOraciones = estadisticas.cantidadOraciones - cantidadNombresAbreviados;

    // Mostramos la información de los puntos restantes:
    logMessage("\n[PUNTO 'A'] La cantidad total de oraciones procesadas es: %d\n", cantidadOraciones);
    logMessage("[PUNTO 'F'] La palabra 'peronismo' aparece en %d oraciones.\n", estadisticas.oracionesPeronismo);
    logMessage("[PUNTO 'F'] La palabra 'peronismo' tiene %d ocurrencias en el texto.\n", estadisticas.totalPeronismo);
    logMessage("[PUNTO 'G'] La palabra 'radicalismo' aparece en %d oraciones.\n", estadisticas.oracionesRadicalismo);
    logMessage("[PUNTO 'G'] La palabra 'radicalismo' tiene %d ocurrencias en el texto.\n", estadisticas.totalRadicalismo);

    // Liberamos los recursos asignados al proceso
    regfree(&erPuntoB);
    regfree(&erPuntoC);
    regfree(&erPuntoD);
    regfree(&erPuntoE);
    regfree(&erPuntoF);
    regfree(&erPuntoG);
    regfree(&erPuntoH);
    regfree(&erPuntoI);
    regfree(&erPuntoJ);
    regfree(&erNombreAbreviado);
    fclose(f);

    return 0;
}
