#pragma once
#include "../pch.h"
#include "CEntity.h"
#include "CGlobalVars.h"
#include "offsets.h"

class CGame
{
private:
	struct
	{
		uintptr_t ClientDLL;
		uintptr_t MatchmakingDLL;
		uintptr_t EngineDLL;
		uintptr_t EntityList;
		uintptr_t Matrix;
		uintptr_t ViewAngle;
		uintptr_t EntityListEntry;
		uintptr_t LocalController;
		uintptr_t LocalPawn;
		uintptr_t ForceJump;
		uintptr_t GlobalVars;
		uintptr_t Base;
		uintptr_t GameRules;
	}Address;

public:
	CGame() = default;
	float sensitivity = 0;

	// Init game base addy and offsets
	bool InitAddress();

	std::vector<std::shared_ptr<CEntity>> PlayerList;
	ViewMatrix CurrentMatrix;
	uintptr_t GetClientDLLAddy() const;
	uintptr_t GetEntityListAddress() const;
	uintptr_t GetMatrixAddress() const;
	uintptr_t GetViewAngleAddress() const;
	uintptr_t GetLocalControllerAddress() const;
	uintptr_t GetLocalPawnAddress() const;
	uintptr_t GetGlobalVarsAddress() const;
	uintptr_t GetGameRulesAddress() const;
	int signOnState;
	int GetSignOnState();
	std::string mapName;
	std::string GetMapName();
	bool hasMatchStarted;
	bool GetMatchStarted();
	float GetSensitivity();
	Vector2 WorldToScreen(const Vector3& position);
	void RefreshViewMatrix();

	std::vector<std::shared_ptr<CEntity>>& GetPlayerList();
	void ClearPlayerList() { PlayerList.clear(); }
};

inline CGame gGame;