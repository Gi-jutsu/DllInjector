#include <iostream>

#include "DllInjector/DllInjector.h"

int main() {
    DllInjector injector;
    injector.injectDll("RobloxPlayerBeta.exe", "C:\\Users\\Dylan DE SOUSA\\Desktop\\EasyExploitsDLL.dll");

    return 0;
}
