#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <TlHelp32.h>
#include <mutex>
#include "Misc/Vector.h"
#include "Memory/Memory.h"
#include "SDK/CGame.h"
#include "Global.h"
#include "Misc/json.hpp"
#include "Features/VisCheck/RayTrace.h"

using json = nlohmann::json;
