#include "utils/console.hpp"
#include "hooks/game_overlay.hpp"
#include "sdk/interfaces/CGameEntitySystem.hpp"

game_overlay overlay_init;

DWORD WINAPI on_dll_attach(LPVOID lpParam) {
    utils::attach_console();
    overlay_init.init_hooks();
    return TRUE;
}

BOOL WINAPI on_dll_detach() {
    utils::detach_console();
    return TRUE;
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch(ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, on_dll_attach, hModule, 0, 0);
            return TRUE;
        case DLL_PROCESS_DETACH:
            if (lpReserved == nullptr)
                return on_dll_detach();
            return TRUE;
        default:
            return TRUE;
    }
}

