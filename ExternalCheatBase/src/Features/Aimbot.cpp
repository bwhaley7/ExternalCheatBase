#include "../pch.h"
#include "Aimbot.h"
#include "../SDK/CEntity.h"
#include "../SDK/LocalPlayer.h"
#include "../Misc/Util.h"
#include "../Config/ConfigInstance.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

FastNoiseLite noise;
int steps = 0;
Vector2 startPoint, controlPoint, endPoint;

Aimbot::Aimbot()
    : lastAimTime(std::chrono::high_resolution_clock::now()), bezierProgress(0.0f) {
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.03f);
    steps = 0;
}

Vector2 Aimbot::BezierCurve(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t)
{
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;

    // Apply noise to control and end points
    float noiseX = noise.GetNoise(p1.x, p1.y) * ConfigInstances.Aimbot.noiseFactor;
    float noiseY = noise.GetNoise(p2.x, p2.y) * ConfigInstances.Aimbot.noiseFactor;

    Vector2 noisyControl = {
        p1.x + noiseX,
        p1.y + noiseY
    };

    float x = (uu * p0.x) + (2 * u * t * noisyControl.x) + (tt * p2.x);
    float y = (uu * p0.y) + (2 * u * t * noisyControl.y) + (tt * p2.y);

    return { x, y };
}

Vector2 ClampDelta(Vector2 delta) {
    float maxDelta = 5.0f; // Add a configurable max value
    if (std::abs(delta.x) > maxDelta) delta.x = (delta.x > 0 ? maxDelta : -maxDelta);
    if (std::abs(delta.y) > maxDelta) delta.y = (delta.y > 0 ? maxDelta : -maxDelta);
    return delta;
}

Vector3 CalculateAngle(const Vector3& source, const Vector3& target, const Vector3& viewAngles)
{
    Vector3 delta = target - source;
    float hypotenuse = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    Vector3 angles;
    angles.x = -std::atan2(delta.z, hypotenuse) * (180.0f / static_cast<float>(M_PI));
    angles.y = std::atan2(delta.y, delta.x) * (180.0f / static_cast<float>(M_PI));
    angles.z = 0.0f; // Roll is not used in aiming

    angles = angles - viewAngles;
    Util.ClampAngles(angles);

    return angles;
}

Vector3 CalculateViewAngleDelta(const Vector3& source, const Vector3& target, const Vector3& currentViewAngles)
{
    // Calculate the angle required to aim at the target
    Vector3 desiredAngles = CalculateAngle(source, target, currentViewAngles);

    // Compute the difference between the desired angles and the current view angles
    Vector3 delta = desiredAngles - currentViewAngles;

    // Normalize the delta to ensure it's within valid angle ranges
    Util.ClampAngles(delta);

    return delta;
}

void Aimbot::RecoilSystem()
{
    gLocalPlayer.GetAimPunchCache();
    gLocalPlayer.GetViewAngles();

    static Vector3 oldPunch;
    Vector3 aimPunchAngle = mem.RPM<Vector3>(gLocalPlayer.aimPunchCache.Data + (gLocalPlayer.aimPunchCache.Count - 1) * sizeof(Vector3));

    if (gLocalPlayer.GetShotsFired() > 1) {

        Vector3 recoilVector = {
            gLocalPlayer.ViewAngles.x + oldPunch.x - aimPunchAngle.x,
            gLocalPlayer.ViewAngles.y + oldPunch.y - aimPunchAngle.y,
            0.0f
        };
        Util.ClampAngles(recoilVector);

        mem.WPM<Vector3>(gGame.GetViewAngleAddress(), recoilVector);
    }
    oldPunch.x = aimPunchAngle.x;
    oldPunch.y = aimPunchAngle.y;
}

void Aimbot::RunAimbot()
{
    static std::shared_ptr<CEntity> lockedEntity = nullptr;
    gLocalPlayer.GetCameraPos();
    gLocalPlayer.GetViewAngles();
    //Vector3 bestTarget = FindBestTarget(lockedEntity);
    Vector3 aimBone{};
    
    /*if (bestTarget == Vector3{0, 0, 0}) {
        return;
    }*/
    if (!lockedEntity || lockedEntity->Pawn.Health <= 0 || lockedEntity->Controller.Team == gLocalPlayer.GetLocalTeam()) {
        lockedEntity = nullptr;
        lockedEntity = FindBestTarget();
    }
    if (lockedEntity != nullptr) {
        lockedEntity->Pawn.GetPlayerHealth();
        if (ConfigInstances.Aimbot.bones[ConfigInstances.Aimbot.boneSelect] == "Closest") {
            aimBone = FindClosestBone(lockedEntity);
        }
        else {
            int selectedBone = ConfigInstances.Aimbot.boneMap[ConfigInstances.Aimbot.bones[ConfigInstances.Aimbot.boneSelect]];
            aimBone = mem.RPM<Vector3>(lockedEntity->SceneNode.boneArray + selectedBone * 32);
        }

        if (aimBone == Vector3{ 0, 0, 0 }) {
            return;
        }


        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            Vector3 targetDelta = CalculateAngle(gLocalPlayer.CameraPos, aimBone, gLocalPlayer.ViewAngles);

            gLocalPlayer.GetAimPunchCache();
            Vector3 aimPunchAngle = mem.RPM<Vector3>(gLocalPlayer.aimPunchCache.Data + (gLocalPlayer.aimPunchCache.Count - 1) * sizeof(Vector3));

            if (gLocalPlayer.GetShotsFired() >= 1) {
                targetDelta.x -= aimPunchAngle.x * 2.f;
                targetDelta.y -= aimPunchAngle.y * 2.f;
            }

            targetDelta.x /= ConfigInstances.Aimbot.smoothing;
            targetDelta.y /= ConfigInstances.Aimbot.smoothing;

            Vector3 newViewAngles = {
                gLocalPlayer.ViewAngles.x + targetDelta.x,
                gLocalPlayer.ViewAngles.y + targetDelta.y,
                0.0f
            };

            Util.ClampAngles(newViewAngles);

            mem.WPM<Vector3>(gGame.GetViewAngleAddress(), newViewAngles);
        }
        else {
            lockedEntity = nullptr;
        }
    }
}

void Aimbot::MoveMouse(const Vector2& delta) {
    mouse_event(MOUSEEVENTF_MOVE, static_cast<int>(delta.x), static_cast<int>(delta.y), 0, 0);
}

void Aimbot::MoveMouse(int x, int y) {
    mouse_event(MOUSEEVENTF_MOVE, x, y, 0, 0);
}

bool Aimbot::IsTargetWithinFOV(const Vector3& target, const Vector3& headPos) {
    gLocalPlayer.GetCameraPos();
    gLocalPlayer.GetViewAngles();
    // Calculate the midpoint of the bounding box (roughly the torso or center of mass)
    Vector3 boundingBoxCenter = (target + headPos) * 0.5f;

    // Calculate deltas for both base and head positions
    Vector3 deltaToBase = target - gLocalPlayer.CameraPos;
    Vector3 deltaToHead = headPos - gLocalPlayer.CameraPos;
    Vector3 deltaToCenter = boundingBoxCenter - gLocalPlayer.CameraPos;

    // Helper to compute FOV distance
    auto computeFOVDistance = [&](const Vector3& delta) {
        float distance2D = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        float yaw = std::atan2(delta.y, delta.x) * 57.295779513f;
        float pitch = -std::atan2(delta.z, distance2D) * 57.295779513f;

        float deltaYaw = yaw - gLocalPlayer.ViewAngles.y;
        float deltaPitch = pitch - gLocalPlayer.ViewAngles.x;

        deltaYaw = std::fmod(deltaYaw + 540.0f, 360.0f) - 180.0f;
        deltaPitch = std::fmod(deltaPitch + 540.0f, 360.0f) - 180.0f;

        return std::sqrt(deltaYaw * deltaYaw + deltaPitch * deltaPitch);
        };

    float fovToBase = computeFOVDistance(deltaToBase);
    float fovToHead = computeFOVDistance(deltaToHead);
    float fovToCenter = computeFOVDistance(deltaToCenter);

    // Check if any point of interest is within the FOV limit
    float fovLimit = ConfigInstances.Aimbot.fov;
    return (fovToBase <= fovLimit || fovToHead <= fovLimit || fovToCenter <= fovLimit);
}

Vector2 Aimbot::CalculateMouseDelta(const Vector3& target) {
    Vector2 screenPos = gGame.WorldToScreen(target);
    Vector2 delta = {
        (screenPos.x - g_Globals.screenCenter.x) / ConfigInstances.Aimbot.smoothing,
        (screenPos.y - g_Globals.screenCenter.y) / ConfigInstances.Aimbot.smoothing
    };

    delta.x *= gGame.sensitivity;
    delta.y *= gGame.sensitivity;

    return delta;
}

Vector3 Aimbot::FindClosestBone(const std::shared_ptr<CEntity>& entity) {
    Vector3 closestBone = { 0, 0, 0 };
    float minBoneDistance = FLT_MAX;

    for (int boneIndex : Util.closestBoneIndices) {
        Vector3 bonePos = mem.RPM<Vector3>(entity->SceneNode.boneArray + boneIndex * 32);

        if (bonePos == Vector3{ 0, 0, 0 }) {
            continue;
        }

        Vector2 screenPos = gGame.WorldToScreen(bonePos);

        if (screenPos.x <= 0 || screenPos.y <= 0) {
            continue;
        }

        float distanceToCrosshair = Util.getDistance(screenPos, g_Globals.screenCenter);

        if (distanceToCrosshair < minBoneDistance) {
            minBoneDistance = distanceToCrosshair;
            closestBone = bonePos;
        }
    }

    return closestBone;
}

std::shared_ptr<CEntity> Aimbot::FindBestTarget()
{
    float minScreenDistance = FLT_MAX;
    float minPlayerDistance = FLT_MAX;
    Vector3 bestBone = { 0, 0, 0 };
    std::shared_ptr<CEntity> tempEnt = nullptr;

    for (const auto& entity : gGame.GetPlayerList()) {
        if (entity->Pawn.Health <= 0 || entity->Controller.Team == gLocalPlayer.GetLocalTeam()) {
            continue;
        }
        static Vector3 bonePos;

        Vector2 screenPos = gGame.WorldToScreen(entity->Pawn.Position);

        if (screenPos.x > 0 && screenPos.y > 0) {
            Vector3 head = mem.RPM<Vector3>(entity->SceneNode.boneArray + 6 * 32);
            float distance = Util.getDistance(screenPos, g_Globals.screenCenter);
            float playerDistance = Util.getDistance(gLocalPlayer.GetOrigin(), entity->Pawn.Position);
            if (playerDistance < minPlayerDistance || (playerDistance == minPlayerDistance && distance < minScreenDistance)) {
                if (IsTargetWithinFOV(entity->Pawn.Position, head))
                {
                    minScreenDistance = distance;
                    minPlayerDistance = playerDistance;
                    tempEnt = entity;
                }
            }
        }
        //Sleep(10);
    }
    return tempEnt;
}

void Aimbot::execute() {
	RunAimbot();
}