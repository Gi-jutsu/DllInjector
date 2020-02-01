//
// Created by Dylan DE SOUSA on 01/02/2020.
//

#ifndef DLLINJECTOR_DLLINJECTOR_H
#define DLLINJECTOR_DLLINJECTOR_H

#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>

class DllInjector {
    public:
        bool injectDll(const std::string &processName, const std::string &dllPath);
    private:
        int getProcessId(const std::string &name);
};


#endif //DLLINJECTOR_DLLINJECTOR_H
