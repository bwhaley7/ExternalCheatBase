#pragma once
#include "../pch.h"

class Utility
{
public:
	std::string wideCharToString(const std::wstring& wideStr);
	std::wstring stringToWideChar(const std::string& str);
	float fixJointSize(float size);
	float getJointSize(float jointSize, int distance);
	float getDistance(Vector3 from, Vector3 to);
	float getDistance(const Vector2& from, const Vector2& to);
	void ClampAngles(Vector3& angles)
	{
		if (angles.x > 89.0f)
			angles.x = 89.0f;
		if (angles.x < -89.0f)
			angles.x = -89.0f;

		while (angles.y > 180.0f)
			angles.y -= 360.0f;
		while (angles.y < -180.0f)
			angles.y += 360.0f;

		angles.z = 0.0f;
	}

	static Utility& getInstance();

	std::array<int, 6> closestBoneIndices = {
	Utility::bones::head,
	Utility::bones::neck,
	Utility::bones::chest,
	Utility::bones::crotch,
	};
	
	enum bones : int {
		head = 6,
		neck = 5,
		chest = 4,
		shoulderRight = 8,
		shoulderLeft = 13,
		elbowRight = 9,
		elbowLeft = 14,
		handRight = 11,
		handLeft = 16,
		crotch = 0,
		kneeRight = 23,
		kneeLeft = 26,
		ankleRight = 24,
		ankleLeft = 27,
	};

	struct
	{
		std::vector<int> mid = { bones::head, bones::neck, bones::chest, bones::crotch };
		std::vector<int> leftArm = { bones::neck, bones::shoulderLeft, bones::elbowLeft, bones::handLeft };
		std::vector<int> rightArm = { bones::neck, bones::shoulderRight, bones::elbowRight, bones::handRight };
		std::vector<int> leftLeg = { bones::crotch, bones::kneeLeft, bones::ankleLeft };
		std::vector<int> rightLeg = { bones::crotch, bones::kneeRight, bones::ankleRight };
		std::vector<std::vector<int>> allGroups = { mid,leftArm,rightArm,leftLeg,rightLeg };
	}boneGroups;

	Utility() = default;
	~Utility() = default;
	Utility(const Utility&) = delete;
	Utility& operator=(const Utility&) = delete;
};

inline Utility Util;