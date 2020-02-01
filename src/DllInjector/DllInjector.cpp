#include "DllInjector.h"

int DllInjector::getProcessId(const std::string &name) {
    DWORD pid = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 process;

        ZeroMemory(&process, sizeof(process));
        process.dwSize = sizeof(process);

        if (Process32First(snapshot, &process)) {
            do {
                if (!strcmp(process.szExeFile, name.c_str())) {
                    pid = process.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &process));
        }
    }

    CloseHandle(snapshot);
    return pid;
}

bool DllInjector::injectDll(const std::string &processName, const std::string &dllPath) {
    DWORD pid = this->getProcessId(processName);

    if (pid == 0) {
        std::cout << "[ERROR] No process found with name: " << processName << std::endl;
        return false;
    }

    long dllSize = dllPath.length() + 1;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    std::cout << "[INFO] Opening target process ..." << std::endl;
    if (hProcess == NULL) {
        std::cout << "[ERROR] Fail to open target process !" << std::endl;
        return false;
    }

    LPVOID pDllPath = VirtualAllocEx(hProcess, NULL, dllSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    std::cout << "[INFO] Allocating memory in target process." << std::endl;
    if (pDllPath == NULL) {
        std::cout << "[ERROR] Fail to allocate memory in target process." << std::endl;
        return false;
    }

    std::cout << "[INFO] Writing dllPath size in target process memory." << std::endl;

    int isWriteSuccess = WriteProcessMemory(hProcess, pDllPath, dllPath.c_str(), dllSize, 0);
    if (isWriteSuccess == 0) {
        std::cout << "[ERROR] Fail to allocate memory in target process." << std::endl;
        return false;
    }

    std::cout << "[INFO] Creating remote thread in target process" << std::endl;

    LPTHREAD_START_ROUTINE pThreadStartRoutine = (LPTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA");
    HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, pThreadStartRoutine, pDllPath, 0, 0);

    if (hThread == NULL) {
        std::cout << "[ERROR] Fail to create remote thread in target process." << std::endl;
        return false;
    }

    std::cout << "[INFO] DLL Successfully Injected." << std::endl;
    std::cout << "[INFO] Executing DLL in target process." << std::endl;

    WaitForSingleObject(hThread, INFINITE);

    return true;
}