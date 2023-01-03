#include <stdio.h>
#include <stdio.h>
#include <string.h>

int main(){
    char string_variable_name[250];

    printf("__moteur de recherche__ \n");
    printf("What do you want to search ? : \n");

    scanf("%s", &string_variable_name);

    printf("vous recherchez %s\n", string_variable_name);
    return 0;
}