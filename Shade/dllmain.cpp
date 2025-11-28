#include "utils/console.hpp"
#include "hooks/game_overlay.hpp"
#include "sdk/interfaces/CGameEntitySystem.hpp"
#include "sdk/sdk.hpp"
#include "menu/menu.hpp"

#ifdef _DEBUG
#include <conio.h>
#endif

DWORD WINAPI on_dll_attach(LPVOID lpParam) {
#ifdef _DEBUG
    utils::attach_console();
#endif

    try {
        interfaces::initialize();
        interfaces::dump();

        menu::setup_styles();

        game_overlay::init_hooks();

        //FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);
    }
    catch (const std::exception& e) {
        LOG("An error occured during initialization:\n");
        LOG("%s\n", e.what());
        LOG("Press any key to exit.\n");
#ifdef _DEBUG
        int ch = _getch();
#endif
        FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);
    }

    return TRUE;
}

BOOL WINAPI on_dll_detach() {
#ifdef _DEBUG
    utils::detach_console();
    game_overlay::unhook();
#endif

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

