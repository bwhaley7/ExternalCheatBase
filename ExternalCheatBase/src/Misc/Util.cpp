#include "../pch.h"
#include "Util.h"

Utility& Utility::getInstance() {
	static Utility instance;
	return instance;
}

std::string Utility::wideCharToString(const std::wstring& wideStr) {
    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string str(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &str[0], sizeNeeded, nullptr, nullptr);
    return str;
}

std::wstring Utility::stringToWideChar(const std::string& str) {
    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wideStr(sizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wideStr[0], sizeNeeded);
    return wideStr;
}

float Utility::fixJointSize(float size)
{
	int returnSize = 1;

	if (size > 3.f) returnSize = 3.f;
	if (size > 7.f) returnSize = 4.f;
	if (size < 1.f) returnSize = 2.f;

	return returnSize;
}

float Utility::getJointSize(float jointSize, int distance)
{
	return (jointSize - fixJointSize(distance));
}

float Utility::getDistance(Vector3 from, Vector3 to) {
	return sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2) + pow(to.z - from.z, 2));
}

float Utility::getDistance(const Vector2& from, const Vector2& to) {
	return sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2));
}