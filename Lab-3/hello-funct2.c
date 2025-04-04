#include <stdio.h>

void trackKeyPress() {
    char key;
    int count = 0;  // Key press counter

    printf("Press any key to start counting (Press 'q' to quit):\n");

    while (1) {
        size_t bytesRead = fread(&key, 1, 1, stdin);

        if (bytesRead > 0) {  
            if (key == '\n') continue;  // Ignore newlines

            if (key == 'q' || key == 'Q') {
                printf("Exiting...\n");
                break;
            }

            count++;
            printf("Key pressed %d times\n", count);
        }
    }
}
