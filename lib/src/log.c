#include "../include/log.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void activarColoresWindows() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    DWORD modoActual = 0;
    // Habilitamos los colores para la stdout
    HANDLE handleStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleMode(handleStdout,&modoActual)) {
        SetConsoleMode(handleStdout, modoActual | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
    // Habilitamos los colores para la stderr
    HANDLE handleStderr = GetStdHandle(STD_ERROR_HANDLE);
    if (GetConsoleMode(handleStderr, &modoActual)) {
        SetConsoleMode(handleStderr, modoActual | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#endif
}

void activarColoresTerminal() {
#ifdef _WIN32
    activarColoresWindows();
#else
    return; // Los sistemas tipo UNIX ya tienen habilitados los colores.
#endif
}