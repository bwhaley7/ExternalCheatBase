#include "pch.h"
#include "Logging/Logger.h"
#include "Features/CheatManager.h"
#include "Features/ESP.h"
#include "Features/Aimbot.h"
#include "Features/RCS.h"

std::string mapCache = "";

void InitVars()
{
    if (!gGame.InitAddress())
        Loggus.log(Loggus.CRITICAL, "Could not initialize game vars.");
    g_Globals.UpdateScreenDimensions();
    gGame.GetSensitivity();
}

int main(){
    
    try {
        Loggus.Initialize();

        HWND targetWindow = FindWindowA(nullptr, "Counter-Strike 2");
        if (!targetWindow) {
            Loggus.log(Loggus.CRITICAL, "Target window not found.");
            return -1;
        }

        if (!mem.attachToProcess(L"cs2.exe"))
        {
            Loggus.log(Loggus.CRITICAL, "Could not attach to process.");
            return -1;
        }

        if (!g_Renderer.Initialize(targetWindow, L"cs2.exe")) {
            Loggus.log(Loggus.CRITICAL, "Failed to initialize renderer.");
            return -1;
        }

        InitVars();

        cheatManager.addFeature(std::make_unique<ESP>());
        cheatManager.addFeature(std::make_unique<RCS>());
        cheatManager.addFeature(std::make_unique<Aimbot>());
        cheatManager.toggleFeature(0);
        cheatManager.toggleFeature(2);

        while (true) {
            gGame.RefreshViewMatrix();
            gGame.GetMatchStarted();
            gGame.GetMapName();

            if (GetAsyncKeyState(VK_INSERT) & 0x1) g_Renderer.ToggleMenu();

            if (GetAsyncKeyState(VK_END) & 0x8000) break;

            if (!gGame.mapName.empty()) {
                //Loggus.log(Loggus.INFO, "Current map: " + gGame.mapName + " | " + "Map cache: " + mapCache + "\n");
                if (mapCache != gGame.mapName) {
                    mapCache = gGame.mapName;
                    //ray.TestRayInitialization();
                }
                cheatManager.executeEnabled();
            }
            g_Renderer.RenderFrame(g_Globals.screenWidth, g_Globals.screenHeight);
            Sleep(5);
        }

        g_Renderer.Cleanup();
        return 0;
    }
    catch (const std::exception& e) {
        Loggus.log(Loggus.CRITICAL, "Unhandled exception occurred. Cleaning up resources.");
        printf("Exception: %s\n", e.what());
        g_Renderer.Cleanup();
        return 0;
    }
}