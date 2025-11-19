#include "console.hpp"

void utils::attach_console() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
}

void utils::detach_console() {
    FreeConsole();
}