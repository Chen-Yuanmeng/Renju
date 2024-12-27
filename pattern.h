#ifndef __PATTERN_H
#define __PATTERN_H

#include <string.h>

#define TOTAL_PATTERN 55

typedef struct _Pattern {
    char pattern_black[10];
    char pattern_white[10];
    int score_my;
    int score_opponent;
} Pattern;

int my_strstr(char* s, char* t);

#endif
