#include "pch.h"
#include "Render/Renderer.h"
#ifndef GLOBAL_H
#define GLOBAL_H

class Globals {
public:
    int screenWidth = 0;
    int screenHeight = 0;
    int centerX = 0;
    int centerY = 0;
    Vector2 screenCenter{};
    Vector2 screen{};

    void UpdateScreenDimensions() {
        screenWidth = GetSystemMetrics(SM_CXSCREEN);
        screenHeight = GetSystemMetrics(SM_CYSCREEN);
        centerX = screenWidth / 2;
        centerY = screenHeight / 2;
        screen = { static_cast<float>(screenWidth), static_cast<float>(screenHeight) };
        screenCenter = { static_cast<float>(centerX), static_cast<float>(centerY) };
    }

    std::mutex globalsMutex;
};

inline Globals g_Globals;
inline Renderer g_Renderer;

#endif

