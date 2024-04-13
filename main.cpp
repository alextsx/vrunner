#include "utils.h"
#include "runner.h"

int main(int argc, char* argv[]) {
    printf_s("Boot TFP-VRUNNER...\n");

    std::string fileName;
    if (!parseArguments(argc, argv, fileName)) {
        return 0;
    }

    if (!bootApplication(fileName)) {
        printf_s("ERROR: failed to boot application\n");
        return 0;
    }

    printf_s("Current pid%d\n", g_dwRunningPID);

    while (1) {
        if (!isProcessRunning(g_dwRunningPID)) {
            printf_s("*** REBOOT application %s\n", fileName.c_str());
            if (!bootApplication(fileName)) {
                printf_s("ERROR: cannot restart file %s\n", fileName.c_str());
                return 0;
            }
        }

        platformSleep(5000);
    }

    printf_s("Shutdown TFP-VRUNNER...\n");
    return 0;
}