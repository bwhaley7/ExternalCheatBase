#include "../pch.h"
#include "CGame.h"
#include "../Logging/Logger.h"


bool CGame::InitAddress()
{
	this->Address.ClientDLL = mem.GetModuleBaseAddress("client.dll");
	this->Address.MatchmakingDLL = mem.GetModuleBaseAddress("matchmaking.dll");
	this->Address.EngineDLL = mem.GetModuleBaseAddress("engine2.dll");
	if (this->Address.ClientDLL == 0 || this->Address.MatchmakingDLL == 0 || this->Address.EngineDLL == 0)
		return false;
	this->Address.EntityList = mem.RPM<uintptr_t>(this->Address.ClientDLL + offsets::client_dll::dwEntityList);
	this->Address.Matrix = this->Address.ClientDLL + offsets::client_dll::dwViewMatrix;
	this->Address.ViewAngle = this->Address.ClientDLL + offsets::client_dll::dwViewAngles;
	this->Address.LocalController = this->Address.ClientDLL + offsets::client_dll::dwLocalPlayerController;
	this->Address.LocalPawn = this->Address.ClientDLL + offsets::client_dll::dwLocalPlayerPawn;
	this->Address.GlobalVars = mem.RPM<uintptr_t>(this->Address.ClientDLL + offsets::client_dll::dwGlobalVars);
	this->Address.GameRules = mem.RPM<uintptr_t>(this->Address.ClientDLL + offsets::client_dll::dwGameRules);

	return true;
}

std::string CGame::GetMapName() {
	auto mapNamePtr = mem.RPM<uintptr_t>(this->Address.GlobalVars + 0x180);

	if (mapNamePtr == 0 || mapNamePtr > 0x7FFFFFFFFFFF) {
		return "Invalid Pointer";
	}
	char mapN[32];
	mem.Read(mapNamePtr, &mapN, sizeof(mapN));
	mapName = mapN;
	return mapN;
}

int CGame::GetSignOnState() {
	uintptr_t networkGameClient = mem.RPM<uintptr_t>(this->Address.EngineDLL + offsets::engine2_dll::dwNetworkGameClient);
	signOnState = mem.RPM<int>(networkGameClient + offsets::engine2_dll::dwNetworkGameClient_signOnState);
	return signOnState;
}

uintptr_t CGame::GetClientDLLAddy() const
{
	return this->Address.ClientDLL;
}

uintptr_t CGame::GetEntityListAddress() const
{
	return this->Address.EntityList;
}

uintptr_t CGame::GetMatrixAddress() const
{
	return this->Address.Matrix;
}
uintptr_t CGame::GetViewAngleAddress() const
{
	return this->Address.ViewAngle;
}

uintptr_t CGame::GetLocalControllerAddress() const
{
	return this->Address.LocalController;
}

uintptr_t CGame::GetLocalPawnAddress() const
{
	return this->Address.LocalPawn;
}

uintptr_t CGame::GetGlobalVarsAddress() const
{
	return this->Address.GlobalVars;
}

uintptr_t CGame::GetGameRulesAddress() const
{
	return this->Address.GameRules;
}

Vector2 CGame::WorldToScreen(const Vector3& position)
{
    float _x = CurrentMatrix.matrix[0][0] * position.x + CurrentMatrix.matrix[0][1] * position.y + CurrentMatrix.matrix[0][2] * position.z + CurrentMatrix.matrix[0][3];
    float _y = CurrentMatrix.matrix[1][0] * position.x + CurrentMatrix.matrix[1][1] * position.y + CurrentMatrix.matrix[1][2] * position.z + CurrentMatrix.matrix[1][3];
    float w = CurrentMatrix.matrix[3][0] * position.x + CurrentMatrix.matrix[3][1] * position.y + CurrentMatrix.matrix[3][2] * position.z + CurrentMatrix.matrix[3][3];

    if (w < 0.01f)
        return Vector2(0, 0);

    float inv_w = 1.f / w;
    _x *= inv_w;
    _y *= inv_w;

    float screen_x = GetSystemMetrics(SM_CXSCREEN) * 0.5f;
    float screen_y = GetSystemMetrics(SM_CYSCREEN) * 0.5f;

    screen_x += 0.5f * _x * GetSystemMetrics(SM_CXSCREEN) + 0.5f;
    screen_y -= 0.5f * _y * GetSystemMetrics(SM_CYSCREEN) + 0.5f;

    return Vector2(screen_x, screen_y);


}

bool CGame::GetMatchStarted() {
	hasMatchStarted = mem.RPM<bool>(gGame.GetGameRulesAddress() + offsets::client_dll::C_CSGameRules::m_bHasMatchStarted);
	return hasMatchStarted;
}

void CGame::RefreshViewMatrix()
{
	CurrentMatrix = mem.RPM<ViewMatrix>(gGame.GetMatrixAddress());

	if (CurrentMatrix.matrix[0][0] == 0.0f && CurrentMatrix.matrix[1][1] == 0.0f)
	{
		Loggus.log(Loggus.CRITICAL, "Failed to refresh view matrix. Matrix may be invalid.");
		return;
	}
}

float CGame::GetSensitivity()
{
	auto dwSens = mem.RPM<uintptr_t>(this->Address.ClientDLL + offsets::client_dll::dwSensitivity);
	sensitivity = mem.RPM<float>(dwSens + offsets::client_dll::dwSensitivity_sensitivity);
	return sensitivity;
}

std::vector<std::shared_ptr<CEntity>>& CGame::GetPlayerList()
{
	return PlayerList;
}