#include "cwrapper.h"

#include "core.hpp"

extern "C" {
    Core* NewCore() {
        return new Core();
    }

    void Core_Init(Core *c, const char *shaderPath, const char *imagePath) {
        c->Init(shaderPath, imagePath);
    }

    void Core_Run(Core *c) {
        c->Run();
    }

    void DeleteCore(Core *c) {
        delete c;
    }
}
