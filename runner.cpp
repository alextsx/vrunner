#include "runner.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

bool runForked(const std::string& fileName) {
    printf_s("Forking this file: %s", fileName.c_str());

    pid_t pid = fork();
    if (pid == -1) {
        // Fork failed
        return false;
    } else if (pid == 0) {
        // Child process
        char resolved_path[PATH_MAX];
        if (readlink(fileName.c_str(), resolved_path, sizeof(resolved_path)) == -1) {
            perror("readlink");
            exit(EXIT_FAILURE);
        }

        execlp(resolved_path, ("./" + fileName).c_str(), nullptr);

        // If execlp returns, an error occurred
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        pid_t result = waitpid(pid, &status, 0);
        if (result == -1) {
            return false;
        }

        if (WIFEXITED(status)) {
            printf_s("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf_s("Child process terminated by signal: %d\n", WTERMSIG(status));
        }
        return true;
    }
}

bool bootApplication(const std::string& fileName) {
    printf_s("Current working directory: %s\n", getcwd(nullptr, 0));

    if (!runForked(fileName)) {
        printf_s("ERROR: Failed to run the game file.\n");
        return false;
    }

    platformSleep(2000);

    int attempts = 0;
    while (!initializePid() && attempts < 50) {
        printf_s("Attempt: %d", attempts);
        platformSleep(5000);
        attempts++;
    }

    if (attempts == 50) {
        printf_s("ERROR: failed to initialize PID after multiple attempts\n");
        return false;
    }

    return g_dwRunningPID != 0;
}
