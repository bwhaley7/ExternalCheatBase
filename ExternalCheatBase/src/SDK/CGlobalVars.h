#include "../pch.h"

class CGlobalVarsBase
{
public:
    float m_flRealTime;
    int m_iFrameCount;
    float m_flAbsoluteFrameTime;
    float m_flAbsoluteFrameStartTimeStdDev;
    int m_nMaxClients;
private:
    std::byte pad1[0x1C];
public:
    float m_flIntervalPerTick;
    float m_flCurrentTime;
    float m_flCurrentTime2;
private:
    std::byte pad2[0x14];
public:
    std::int32_t m_nTickCount;
    float m_flIntervalPerTick2;
private:
    std::byte pad3[0x158];
public:
    std::uint64_t m_uCurrentMap;
    std::uint64_t m_uCurrentMapName;
};