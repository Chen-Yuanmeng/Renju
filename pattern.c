#include "pattern.h"

// Return the number of occurrences of t in s.
int my_strstr(char* s, char* t) {
    int count = 0;
    int len_s = strlen(s);
    int len_t = strlen(t);

    for (int i = 0; i < len_s; ++i) {
        if (s[i] == t[0]) {
            int j = 1;
            for (; j < len_t; ++j) {
                if (s[i + j] != t[j]) {
                    break;
                }
            }
            if (j == len_t) {
                ++count;
            }
        }
    }

    return count;
}
