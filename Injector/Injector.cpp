#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <tlhelp32.h>

int main()
{
    std::cout << "Simple Injector.\n";

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cout << "[-] Failed to snapshot processes. Last error: " << GetLastError() << std::endl;
        std::getchar();
        return 0;
    }

    std::cout << "[+] Created processes snapshot." << std::endl;

    BOOL bResult = Process32First(hSnapshot, &entry) == TRUE;
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    while (bResult) {
        if (_wcsicmp(entry.szExeFile, L"cs2.exe") == 0) {
            hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, TRUE, entry.th32ProcessID);
            break;
        }

        bResult = Process32Next(hSnapshot, &entry);
    }

    CloseHandle(hSnapshot);

    if (hProcess == INVALID_HANDLE_VALUE) {
        std::cout << "[-] Target process not found or OpenProcess failed. Last error: " << GetLastError() << std::endl;
        std::getchar();
        return 0;
    }

    std::cout << "[+] Found target process." << std::endl;

    const wchar_t* sDllPath = L"C:\\Users\\Administrator\\source\\repos\\Shade\\x64\\Debug\\Shade.dll";
    size_t nPathLength = (wcslen(sDllPath) + 1) * sizeof(wchar_t);

    void* pRemoteMemory = VirtualAllocEx(
        hProcess,
        nullptr,
        nPathLength,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );

    if (pRemoteMemory == NULL) {
        std::cout << "[-] Failed to allocate memory in the process. Last error: " << GetLastError() << std::endl;
        std::getchar();
        return 0;
    }

    std::cout << "[+] Allocated memory at " << std::hex << pRemoteMemory << std::dec << std::endl;

    if (!WriteProcessMemory(hProcess, pRemoteMemory, sDllPath, nPathLength, nullptr)) {
        std::cout << "[-] Failed to write memory at " << std::hex << pRemoteMemory << std::dec << ". Last error: " << GetLastError() << std::endl;
        std::getchar();
        return 0;
    }

    std::cout << "[+] Successfully wroted memory at " << std::hex << pRemoteMemory << std::dec << std::endl;

    HMODULE hKernel = GetModuleHandleA("kernel32.dll");
    std::cout << "[+] Found kernel32.dll." << std::endl;

    void* pLoadLibrary = (void*)GetProcAddress(hKernel, "LoadLibraryW");
    std::cout << "[+] Found LoadLibraryW at " << std::hex << pLoadLibrary << std::dec << std::endl;

    HANDLE hTread = CreateRemoteThread(
        hProcess,
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)pLoadLibrary,
        pRemoteMemory,
        0,
        nullptr
    );

    if (hTread == NULL) {
        std::cout << "[-] Failed to create thread in the process. Last error: " << GetLastError() << std::endl;
        return 0;
    }

    WaitForSingleObject(hTread, INFINITE);
    std::cout << "[+] Created thread." << std::endl;

    VirtualFreeEx(hProcess, pRemoteMemory, 0, MEM_RELEASE);
    std::cout << "[+] Memory released." << std::endl;

    CloseHandle(hProcess);
    std::cout << "[+] Closed handle." << std::endl;

    return 0;
}
