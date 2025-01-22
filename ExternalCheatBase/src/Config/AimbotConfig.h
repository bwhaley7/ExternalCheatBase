#pragma once
#include "../pch.h"

class AimbotConfig
{
	std::string ConfigName;

public:
	AimbotConfig(const std::string& name)
	{
		ConfigName = name;
	}

	bool enabled = true;
	bool lockToTarget = false;
	bool rcs = true;
	bool visibleCheck = false;
	bool showFov = true;
	float fov = 1.6f;
	float smoothing = 3.f;
	float noiseFactor = 0.1;
	float rcsXMulti = 1.f;
	float rcsYMulti = 15.f;
	int bezierSteps = 10;

	int bone = 0;
	int boneSelect = 0;
	std::vector<std::string> bones = { "Head", "Neck","Chest", "Crotch", "Closest" };
	std::map <std::string, int> boneMap = { {"Head",6},{"Neck",5},{"Chest",4} ,{"Crotch",0}, {"Closest", 19} };

	json ToJson()
	{
		json j;
		j[ConfigName]["enabled"] = enabled;
		j[ConfigName]["lockToTarget"] = lockToTarget;
		j[ConfigName]["rcs"] = rcs;
		j[ConfigName]["visibleCheck"] = visibleCheck;
		j[ConfigName]["showFov"] = showFov;
		j[ConfigName]["fov"] = fov;
		j[ConfigName]["smoothing"] = smoothing;
		j[ConfigName]["noiseFactor"] = noiseFactor;
		j[ConfigName]["rcsXMulti"] = rcsXMulti;
		j[ConfigName]["rcsYMulti"] = rcsYMulti;
		j[ConfigName]["bezierSteps"] = bezierSteps;
		return j;
	}

	void FromJson(const json& j)
	{
		if (!j.contains(ConfigName))
			return;

		if (j[ConfigName].contains("enabled"))
			enabled = j[ConfigName]["enabled"];
		if (j[ConfigName].contains("lockToTarget"))
			lockToTarget = j[ConfigName]["lockToTarget"];
		if (j[ConfigName].contains("rcs"))
			rcs = j[ConfigName]["rcs"];
		if (j[ConfigName].contains("visibleCheck"))
			visibleCheck = j[ConfigName]["visibleCheck"];
		if (j[ConfigName].contains("showFov"))
			showFov = j[ConfigName]["showFov"];
		if (j[ConfigName].contains("fov"))
			fov = j[ConfigName]["fov"];
		if (j[ConfigName].contains("smoothing"))
			smoothing = j[ConfigName]["smoothing"];
		if (j[ConfigName].contains("noiseFactor"))
			noiseFactor = j[ConfigName]["noiseFactor"];
		if (j[ConfigName].contains("rcsXMulti"))
			rcsXMulti = j[ConfigName]["rcsXMulti"];
		if (j[ConfigName].contains("rcsYMulti"))
			rcsYMulti = j[ConfigName]["rcsYMulti"];
		if (j[ConfigName].contains("bezierSteps"))
			bezierSteps = j[ConfigName]["bezierSteps"];
	}
};