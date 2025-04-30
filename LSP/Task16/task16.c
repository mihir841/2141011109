#include <stdio.h>

int main() {
    int i = 5;  // Directly initializing i here
    printf("Counting down from 5...\n");

    for (i = 5; i >= 0; i--) {
        printf("%d\n", i);
    }

    printf("Done!\n");
    return 0;
}
