#pragma once
#include <string>

#undef printf_s
#define printf_s(...) log(__VA_ARGS__)

#ifdef _WIN32
#include <windows.h>
#define platformSleep(milliseconds) Sleep(milliseconds)
#else
#include <unistd.h>
#define platformSleep(milliseconds) sleep(milliseconds / 1000)
#endif

extern unsigned int g_dwRunningPID;

std::string resolveSymbolicLink(const char* path);
bool isProcessRunning(unsigned int pid);
bool initializePid();
void log(const char* format, ...);
bool parseArguments(int argc, char* argv[], std::string& fileName);
bool interpret_argument(char* arg, std::string& fileName);