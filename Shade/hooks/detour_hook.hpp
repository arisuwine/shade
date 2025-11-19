#pragma once
#include <windows.h>
#include <detours.h>
#include <psapi.h>
#include <fstream>
#include <string>
#pragma comment(lib, "C:\\Program Files\\Microsoft Research\\Detours\\lib.X64\\detours.lib")

#define PS_LOGGING

#ifdef PS_LOGGING
#include <stdio.h>
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

using Type = __int64 __fastcall(__int64, __int64);

extern __int64 (__fastcall *prob_ViewMatrixSetupOrig)(__int64 a1, __int64 a2);
__int64 __fastcall prob_ViewMatrixSetup(__int64 a1, __int64 a2);

extern std::ofstream log_addr;
extern uintptr_t view_matrix_addr;

void hook();