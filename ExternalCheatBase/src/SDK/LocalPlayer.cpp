#include "../pch.h"
#include "LocalPlayer.h"
#include "offsets.h"

uintptr_t LocalPlayer::GetPlayerPawn(uintptr_t base)
{
    playerPawn = mem.RPM<uintptr_t>(base + offsets::client_dll::dwLocalPlayerPawn);
    return playerPawn;
}

uintptr_t LocalPlayer::GetLocalTeam()
{
    myTeam = mem.RPM<uintptr_t>(playerPawn + offsets::client_dll::C_BaseEntity::m_iTeamNum);
    return myTeam;
}

Vector3 LocalPlayer::GetOrigin()
{
    Position = mem.RPM<Vector3>(playerPawn + offsets::client_dll::C_BasePlayerPawn::m_vOldOrigin);
    return Position;
}

Vector3 LocalPlayer::GetVelocity()
{
    Velocity = mem.RPM<Vector3>(playerPawn + offsets::client_dll::C_BaseEntity::m_vecAbsVelocity);
    return Velocity;
}

Vector3 LocalPlayer::GetCameraPos()
{
    CameraPos = mem.RPM<Vector3>(playerPawn + offsets::client_dll::C_CSPlayerPawnBase::m_vecLastClipCameraPos);
    return CameraPos;
}

Vector3 LocalPlayer::GetViewAngles()
{
    ViewAngles = mem.RPM<Vector3>(playerPawn + offsets::client_dll::C_BasePlayerPawn::v_angle);
    return ViewAngles;
}

int LocalPlayer::GetShotsFired()
{
    shotsFired = mem.RPM<int>(playerPawn + offsets::client_dll::C_CSPlayerPawn::m_iShotsFired);
    return shotsFired;
}

C_UTL_VECTOR LocalPlayer::GetAimPunchCache()
{
    aimPunchCache = mem.RPM<C_UTL_VECTOR>(playerPawn + offsets::client_dll::C_CSPlayerPawn::m_aimPunchCache);
    return aimPunchCache;
}