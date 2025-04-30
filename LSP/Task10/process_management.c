#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Error in creating child
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process started. Executing 'ls' command...\n");

        char *args[] = {"ls", "-l", NULL};  // Command and arguments
        execvp(args[0], args);  // Execute the command

        // If execvp returns, an error occurred
        perror("execvp failed");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);  // Wait for child to complete

        if (WIFEXITED(status)) {
            printf("Child process terminated with exit status %d.\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally.\n");
        }
    }

    return 0;
}

