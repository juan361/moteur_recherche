#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char string_scan[250], string_maj[250];

    printf("__moteur de recherche__ \n");
    printf("What do you want to search ? : \n");

    scanf("%s", &string_scan);

    for (int i = 0; i < strlen(string_scan); i++) {
      string_maj[i] = toupper(string_scan[i]);
  }

    printf("vous recherchez %s \nnous rechercherons alors avec le mot %s \n", string_scan, string_maj);
    return 0;
}