#include "../pch.h"

class GlobalVars {
public:
    float realTime;
    int frameCount;
    float absoluteFrameTime;
    float absoluteFrameStartTimeStdDev;
    int maxClients;
    float intervalPerTick;
private:
    std::byte pad1[0x14];
public:
    float currentTime;
    float currentTime2;
private:
    std::byte pad2[0xC];
public:
    std::int32_t tickCount;
    float intervalPerTick2;
private:
    std::byte pad3[0x138];
public:
    std::uint64_t currentMap;
    std::uint64_t currentMapName;
};

GlobalVars globalVars;