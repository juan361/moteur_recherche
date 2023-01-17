#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Standardisation/check.h"


int main(){
    char string_scan[250], string_maj[250], string_min[250];

    printf("__moteur de recherche__ \n");
    printf("What do you want to search ? : \n");

    scanf("%s", &string_scan);

    for (int i = 0; i < strlen(string_scan); i++) {
      string_maj[i] = toupper(string_scan[i]);
      string_min[i] = tolower(string_scan[i]);
  }

    printf("vous recherchez %s \nnous rechercherons alors avec le mot %s \n, ou %s", string_scan, string_maj, string_min);
    return 0;
}

int find_word(int argc, char *argv[]) {
    char *searchWord = argv[1];
    char line[256];
    FILE *file = fopen(argv[2], "r");

    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, searchWord)) {
            printf("Mot trouvé : %s", line);
        }
    }

    fclose(file);

    return 0;
}