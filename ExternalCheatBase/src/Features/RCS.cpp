#include "../pch.h"
#include "RCS.h"
#include "../SDK/LocalPlayer.h"
#include "../Config/ConfigInstance.h"
#include "../Misc/Util.h"

RCS::RCS() {}

void RCS::execute()
{
	RunRCS();
}

void MoveMouse(int x, int y) {
    mouse_event(MOUSEEVENTF_MOVE, x, y, 0, 0);
}

void RCS::RunRCS()
{
    gLocalPlayer.GetAimPunchCache();
    gLocalPlayer.GetViewAngles();

    static Vector3 oldPunch;
    Vector3 aimPunchAngle = mem.RPM<Vector3>(gLocalPlayer.aimPunchCache.Data + (gLocalPlayer.aimPunchCache.Count - 1) * sizeof(Vector3));

    if (gLocalPlayer.GetShotsFired() > 1) {

        Vector3 recoilVector = {
            gLocalPlayer.ViewAngles.x + oldPunch.x - aimPunchAngle.x * 2.f,
            gLocalPlayer.ViewAngles.y + oldPunch.y - aimPunchAngle.y * 2.f,
            0.0f
        };
        Util.ClampAngles(recoilVector);

        mem.WPM<Vector3>(gGame.GetViewAngleAddress(), recoilVector);
    }
    oldPunch.x = aimPunchAngle.x *2.f;
    oldPunch.y = aimPunchAngle.y *2.f;
}