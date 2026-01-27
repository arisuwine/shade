#include "console.hpp"

#include <windows.h>
#include <cstdio>
#include <conio.h>

void utils::AttachConsole() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
}

void utils::DetachConsole() {
    std::printf("\nPress any key to exit...\n");
    
    while (_kbhit()) _getch();

    _getch();

    fclose(stdout);
    fclose(stderr);
    fclose(stdin);

    FreeConsole();
}