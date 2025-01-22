#include "../pch.h"
#include "CEntity.h"

uintptr_t PlayerController::GetListEntry(uintptr_t entityList, int id)
{
    //printf("Entity List Address: 0x%zx\n", entityList);
    this->ListEntry = mem.RPM<uintptr_t>(entityList + (0x8 * (id & 0x7FFF) >> 9) + 0x10);
    return ListEntry;
}

uintptr_t PlayerController::GetController(int id)
{
    //printf("ListEntry Address: 0x%zx\n", ListEntry);
    this->Address = mem.RPM<uintptr_t>(ListEntry + 0x78 * (id & 0x1FF));
    //printf("Controller Address: 0x%zx\n", Address);
    return Address;
}

uintptr_t PlayerController::GetPawnAddress()
{
    return mem.RPM<uintptr_t>(Address + offsets::client_dll::CCSPlayerController::m_hPlayerPawn);
}

std::string PlayerController::GetPlayerName()
{
    uintptr_t nameAddr = mem.RPM<uintptr_t>(Address + offsets::client_dll::CCSPlayerController::m_sSanitizedPlayerName);
    if (nameAddr)
    {
        char buf[MAX_PATH] = {};
        mem.Read(nameAddr, buf, sizeof(buf));
        PlayerName = std::string(buf);
    }
    else
    {
        PlayerName = "N/A";
    }
    return PlayerName;
}

uintptr_t PlayerController::GetPlayerTeam()
{
    Team = mem.RPM<uintptr_t>(Address + offsets::client_dll::C_BaseEntity::m_iTeamNum);
    return Team;
}

uintptr_t PlayerPawn::GetListEntry(uintptr_t entityList)
{
    ListEntry = mem.RPM<uintptr_t>(entityList + 0x8 * ((Address & 0x7FFF) >> 9) + 0x10);
    return ListEntry;
}

uintptr_t PlayerPawn::GetPlayerPawn()
{
    playerPawn = mem.RPM<uintptr_t>(ListEntry + 0x78 * (Address & 0x1FF));
    return playerPawn;
}

Vector3 PlayerPawn::GetOrigin()
{
    Position = mem.RPM<Vector3>(playerPawn + offsets::client_dll::C_BasePlayerPawn::m_vOldOrigin);
    return Position;
}

Vector3 PlayerPawn::GetVelocity()
{
    Velocity = mem.RPM<Vector3>(playerPawn + offsets::client_dll::C_BaseEntity::m_vecAbsVelocity);
    return Velocity;
}

int PlayerPawn::GetPlayerHealth()
{
    Health = mem.RPM<int>(playerPawn + offsets::client_dll::C_BaseEntity::m_iHealth);
    return Health;
}

uintptr_t PlayerPawn::GetSceneNode()
{
    return mem.RPM<uintptr_t>(playerPawn + offsets::client_dll::C_BaseEntity::m_pGameSceneNode);
}

uintptr_t CGameSceneNode::GetBoneArray()
{
    boneArray = mem.RPM<uintptr_t>(address + offsets::client_dll::CSkeletonInstance::m_modelState + 0x80);
    return boneArray;
}

bool CEntity::UpdateController(uintptr_t ControllerAddress) {
    this->Controller.Address = ControllerAddress;
    this->Controller.PlayerName = Controller.GetPlayerName();
    this->Controller.Team = Controller.GetPlayerTeam();
    return this->Controller.Address != 0;
}

bool CEntity::UpdatePawn(uintptr_t PawnAddress) {
    return false;
}