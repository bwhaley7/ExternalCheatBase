#pragma once
#include "../pch.h"

class ESPConfig
{
	std::string ConfigName;

public:
	ESPConfig(const std::string& name)
	{
		ConfigName = name;
	}

	bool enabled = true;
	bool drawSkeleton = true;
	bool drawBoundingBox = false;
	bool drawPlayerName = true;
	bool drawHealthBar = false;

	json ToJson()
	{
		json j;
		j[ConfigName]["enabled"] = enabled;
		j[ConfigName]["drawSkeleton"] = drawSkeleton;
		j[ConfigName]["drawBoundingBox"] = drawBoundingBox;
		j[ConfigName]["drawPlayerName"] = drawPlayerName;
		j[ConfigName]["drawHealthBar"] = drawHealthBar;
		return j;
	}

	void FromJson(const json& j)
	{
		if (!j.contains(ConfigName))
			return;

		if (j[ConfigName].contains("enabled"))
			enabled = j[ConfigName]["enabled"];
		if (j[ConfigName].contains("drawSkeleton"))
			drawSkeleton = j[ConfigName]["drawSkeleton"];
		if (j[ConfigName].contains("drawBoundingBox"))
			drawBoundingBox = j[ConfigName]["drawBoundingBox"];
		if (j[ConfigName].contains("drawPlayerName"))
			drawPlayerName = j[ConfigName]["drawPlayerName"];
		if (j[ConfigName].contains("drawHealthBar"))
			drawHealthBar = j[ConfigName]["drawHealthBar"];
	}
};