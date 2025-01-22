#pragma once
#include "../pch.h"

struct C_UTL_VECTOR
{
	uint64_t Count = 0;
	uint64_t Data = 0;
};

class LocalPlayer
{
public:
	int shotsFired = 0;
	C_UTL_VECTOR aimPunchCache;
	uintptr_t playerPawn = 0;
	uintptr_t myTeam = 0;
	Vector3 Position{};
	Vector3 CameraPos{};
	Vector3 ViewAngles{};
	Vector3 Velocity{};
	uintptr_t GetPlayerPawn(uintptr_t base);
	uintptr_t GetLocalTeam();
	Vector3 GetOrigin();
	Vector3 GetVelocity();
	Vector3 GetCameraPos();
	Vector3 GetViewAngles();
	C_UTL_VECTOR GetAimPunchCache();
	int GetShotsFired();
};

inline LocalPlayer gLocalPlayer;