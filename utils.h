#pragma once

#include <string>

std::string resolveSymbolicLink(const char* path);
bool isProcessRunning(unsigned int pid);
bool initializePid();
void log(const char* format, ...);
void platformSleep(int milliseconds);
bool parseArguments(int argc, char* argv[], std::string& fileName);
bool interpret_argument(char* arg, std::string& fileName);