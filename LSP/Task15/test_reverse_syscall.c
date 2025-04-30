#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

// Define your syscall number (must match the one in syscall_64.tbl)
#define SYS_REVERSE_STRING 440

int main() {
    char *input = NULL;
    char *output = NULL;
    size_t len = 0;
    ssize_t read;

    // Prompt the user
    printf("Enter a string to reverse: ");
    read = getline(&input, &len, stdin);

    if (read == -1) {
        perror("Failed to read input");
        free(input);
        return EXIT_FAILURE;
    }

    // Remove newline character if present
    if (input[read - 1] == '\n') {
        input[read - 1] = '\0';
        read--;
    }

    // Allocate space for the output string
    output = malloc(read + 1);
    if (!output) {
        perror("Failed to allocate memory");
        free(input);
        return EXIT_FAILURE;
    }
    memset(output, 0, read + 1);

    // Call the custom system call
    long result = syscall(SYS_REVERSE_STRING, input, output, read);

    if (result == 0) {
        printf("Reversed string: %s\n", output);
    } else {
        perror("System call failed");
        printf("Error code: %ld\n", result);
    }

    free(input);
    free(output);
    return 0;
}

