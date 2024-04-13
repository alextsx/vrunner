#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <limits.h>


unsigned int g_dwRunningPID = 0;

std::string resolveSymbolicLink(const char* path) {
    char resolvedPath[PATH_MAX];
    if (realpath(path, resolvedPath) == nullptr) {
        perror("realpath");
        return "";
    }
    return std::string(resolvedPath);
}

bool isProcessRunning(unsigned int pid) {
    if (pid < 1) {
        return false;
    }
    return kill(pid, 0) == 0;
}

bool initializePid() {
    FILE* pfPid;
    if (!(pfPid = fopen("pid", "r"))) {
        printf_s("ERROR: cannot read pid file \"pid\": %s\n", strerror(errno));
        return false;
    }

    char szDstBuf[4 + 1];
    szDstBuf[4] = '\0';
    fread(szDstBuf, sizeof(szDstBuf), 4, pfPid);
    g_dwRunningPID = atoi(szDstBuf);
    printf_s("Running pid%d\n", g_dwRunningPID);
    fclose(pfPid);
    return true;
}

void log(const char* format, ...) {
    FILE* logFile = fopen("vrunner_error.log", "a");
    if (!logFile) {
        printf("ERROR: Failed to open log file.\n");
        return;
    }

    va_list args;
    va_start(args, format);
    vfprintf(logFile, format, args);
    va_end(args);

    fclose(logFile);
}

bool parseArguments(int argc, char* argv[], std::string& fileName) {
    for (int i = 1; i < argc; ++i) {
        if (!interpret_argument(argv[i], fileName)) {
            return false;
        }
    }

    if (fileName.empty()) {
        printf_s("ERROR: no run file name given (use --file)\n");
        return false;
    }

    return true;
}

bool interpret_argument(char* arg, std::string& fileName) {
    char* szPos = strstr(arg, "=");
    int iArgNameLen = szPos - arg;

    if (!szPos || !iArgNameLen || *(szPos + 1) == '\0') {
        printf_s("ERROR: interpreting argument : %s\n", arg);
        return false;
    }

    char* szArgName = arg;
    char* szArgData = szPos + 1;
    *szPos = '\0';

    if (!strcasecmp(szArgName, "--file")) {
        fileName = szArgData;
    } else {
        printf_s("Skip argument : %s=%s\n", szArgName, szArgData);
    }

    return true;
}