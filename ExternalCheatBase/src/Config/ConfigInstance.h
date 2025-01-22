#pragma once
#include "../pch.h"
#include "ESPConfig.h"
#include "AimbotConfig.h"

class ConfigInstance {
public:
    ESPConfig ESP = ESPConfig("ESP");
    AimbotConfig Aimbot = AimbotConfig("Aimbot");

    json ToJson()
    {
        json jsoned;
        jsoned.merge_patch(ESP.ToJson());
        jsoned.merge_patch(Aimbot.ToJson());
        return jsoned;
    }

    void FromJson(const json& jsoned)
    {
        ESP.FromJson(jsoned);
        Aimbot.FromJson(jsoned);
    }
};

inline ConfigInstance ConfigInstances;