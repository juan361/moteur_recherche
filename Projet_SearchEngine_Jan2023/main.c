#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "MotDeRech.h"

int main(int argc, char *argv[]) {
    Créa_glob_CRI();
    for(int i = 1; i < argc; i++) {
        Find_glob_Doc(argv[i]);
    }
}

