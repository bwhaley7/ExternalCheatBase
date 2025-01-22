#ifndef AIMBOT_H
#define AIMBOT_H

#include "../pch.h"
#include "CheatFeature.h"
#include "../Render/Renderer.h"
#include "../Misc/FastNoiseLite.h"

class Aimbot : public CheatFeature {
public:
	Aimbot();
	void execute() override;

	std::shared_ptr<CEntity> FindBestTarget();
	Vector2 CalculateMouseDelta(const Vector3& target);
	Vector2 BezierCurve(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);
	Vector3 FindClosestBone(const std::shared_ptr<CEntity>& entity);
	bool IsTargetWithinFOV(const Vector3& target, const Vector3& headPos);
	void RecoilSystem();
	void MoveMouse(const Vector2& delta);
	void MoveMouse(int x, int y);
private:
	void RunAimbot();
	float bezierProgress;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastAimTime;
	void ResetTarget();
};

#endif
