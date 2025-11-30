#include "hooks/game_overlay.hpp"
#include "sdk/sdk.hpp"

#include "menu/menu.hpp"

#include "utils/console.hpp"

DWORD WINAPI on_dll_attach(LPVOID lpParam) {
#ifdef _DEBUG
    utils::attach_console();
#endif

    try {
        interfaces::initialize();
        interfaces::dump();

        game_overlay::initialize();
    }
    catch (const std::exception& e) {
        LOG("An error occured during initialization:\n");
        LOG("%s\n", e.what());
        LOG("Press any key to exit.\n");

        FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);
    }

    return TRUE;
}

BOOL WINAPI on_dll_detach() {
#ifdef _DEBUG
    utils::detach_console();
    game_overlay::shutdown();
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

