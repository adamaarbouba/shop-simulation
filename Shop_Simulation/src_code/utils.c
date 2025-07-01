#include "utils.h"
#include <ctype.h>

int strcasecmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) return 1;
        s1++; s2++;
    }
    return *s1 || *s2;
}
