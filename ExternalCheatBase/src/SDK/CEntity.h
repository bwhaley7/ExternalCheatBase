#pragma once
#include "../pch.h"
#include "offsets.h"

class PlayerController
{
public:
	uintptr_t Address = 0;
	uintptr_t ListEntry = 0;
	std::string PlayerName;
	uintptr_t Team = 0;
	uintptr_t Pawn;
	uintptr_t GetListEntry(uintptr_t entityList, int id);
	uintptr_t GetController(int id);
	uintptr_t GetPawnAddress();
	uintptr_t GetPlayerTeam();
	std::string GetPlayerName();
};

class PlayerPawn
{
public:
	std::uint32_t Address = 0;
	uintptr_t ListEntry = 0;
	uintptr_t playerPawn = 0;
	Vector3 Position{};
	Vector3 Velocity{};
	int Health = 0;
	std::string WeaponName;
	Vector3 GetOrigin();
	Vector3 GetVelocity();
	uintptr_t GetListEntry(uintptr_t entityList);
	uintptr_t GetPlayerPawn();
	int GetPlayerHealth();
	std::string GetWeaponName();
	uintptr_t GetSceneNode();
};

class CGameSceneNode
{
public:
	uintptr_t address;
	uintptr_t boneArray;
	uintptr_t GetBoneArray();
};

class CEntity
{
public:
	PlayerController Controller;
	PlayerPawn Pawn;
	CGameSceneNode SceneNode;
	float distance = 0;
	bool UpdateController(uintptr_t ControllerAddress);
	bool UpdatePawn(uintptr_t PawnAddress);
	bool IsAlive();
	bool IsInScreen();
};