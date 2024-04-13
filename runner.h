#pragma once

#include <string>
#include <limits.h>

extern unsigned int g_dwRunningPID;

bool runForked(const std::string& fileName);
bool bootApplication(const std::string& fileName);