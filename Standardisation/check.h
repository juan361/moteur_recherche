#ifndef CHECK_H
#define CHECK_C

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>

#include "check.c"

char *toLowerCaseAndRemoveSymbols(const char *word);

char *englishSing(const char *word);

bool wEqual(char word1[10],char word2[10]);


#endif