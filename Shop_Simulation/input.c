#include "input.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int strcasecmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) return 1;
        s1++; s2++;
    }
    return *s1 || *s2;
}

int safe_int_input(const char *prompt, int max) {
    char line[64];
    int value = 0;
    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Input error. Try again.\n");
            continue;
        }
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) {
            char choice;
            printf("Empty input detected. Do you want to continue buying? (y/n): ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == 'n' || choice == 'N') {
                return -1;
            } else {
                continue;
            }
        }
        if (!strcasecmp_custom(line, "exit")) {
            return -1;
        }
        if (sscanf(line, "%d", &value) != 1 || value < 0) {
            printf("Please enter a valid non-negative number.\n");
            continue;
        }
        if (value > max) {
            printf("Only %d available. Setting quantity to %d.\n", max, max);
            value = max;
        }
        return value;
    }
}

float safe_float_input(const char *prompt) {
    char line[64];
    float value = 0.0f;
    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Input error. Try again.\n");
            continue;
        }
        if (sscanf(line, "%f", &value) != 1 || value < 0.0f) {
            printf("Please enter a valid positive amount.\n");
            continue;
        }
        return value;
    }
}
