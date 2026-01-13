#include "console.hpp"

#include <windows.h>
#include <cstdio>

void utils::AttachConsole() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
}

void utils::DetachConsole() {
    FreeConsole();
}