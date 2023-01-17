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