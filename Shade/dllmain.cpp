/*
The Giant Penis License (GPL)
Copyright (c) 2025

                ▄▄██▄██▄▄
              ▄█    █    █▄
             ▄█           █▄
             █             █
            █               █
            █               █
            █               █
            █               █
             █▄     █     ▄█
              █    ▄▄▄    █
              █           █
              █           █
              █           █
              █           █
              █           █
              █           █
              █           █
              █           █
              █           █
              █           █
              █           █
              █           █
        ▄████▄█           █▄████▄
      ▄█                         █▄
     █                             █
    █                               █
    █                               █
    █                               █
    █             ▄▄█▄▄             █
     █           █     █           █
      █▄       ▄█       █▄       ▄█
        █▄▄▄▄▄█           █▄▄▄▄▄█

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "hooks/game_overlay.hpp"
#include "hooks/hooks.hpp"

#include "sdk/sdk.hpp"

#include "menu/menu.hpp"

#include "utils/console.hpp"
#include "utils/debug.hpp"

bool g_Unload = FALSE;

BOOL WINAPI OnDllDetach() {
#ifdef _DEBUG
    utils::DetachConsole();
#endif

    hooks::Shutdown();

    return TRUE;
}

DWORD WINAPI OnDllAttach(LPVOID lpParam) {
#ifdef _DEBUG
    utils::AttachConsole();
#endif

    try {
        interfaces::Initialize();
        hooks::Initialize();

		while (!g_Unload) {
            if (GetAsyncKeyState(VK_DELETE) & 0x8000)
                g_Unload = TRUE;

			Sleep(100);
        }
    }
    catch (const std::exception& e) {
        LOG("An error occured during initialization:\n");
        LOG("%s\n", e.what());
        LOG("Press any key to exit.\n");

        FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);
    }

    OnDllDetach();
    FreeLibraryAndExitThread((HMODULE)lpParam, 0);

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
            DisableThreadLibraryCalls(hModule);
            CreateThread(nullptr, 0, OnDllAttach, hModule, 0, 0);
            return TRUE;
        default:
            return TRUE;
    }
}

