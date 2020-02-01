#include <iostream>

#include "DllInjector/DllInjector.h"

int main() {
    DllInjector injector;
    injector.injectDll("RobloxPlayerBeta.exe", "C:\\Users\\Dylan DE SOUSA\\Desktop\\libRobloxExploit.dll");

    return 0;
}
