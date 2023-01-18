#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define INDEX_PATH "./textes_CRI/"


void searchWords(const char *word);



int main(){
    
    char string_scan[250], string_min[250];
    int x=1, i=10, c;

    while (x != 0)
    {
        puts(" .----------------.  .----------------.  .----------------. ");
        puts("| .--------------. || .--------------. || .--------------. |");
        puts("| | ____    ____ | || |      __      | || |     ______   | |");
        puts("| ||_   \\  /   _|| || |     /  \\     | || |   .' ___  |  | |");
        puts("| |  |   \\/   |  | || |    / /\\ \\    | || |  / .'   \\_|  | |");
        puts("| |  | |\\  /| |  | || |   / ____ \\   | || |  | |         | |");
        puts("| | _| |_\\/_| |_ | || | _/ /    \\ \\_ | || |  \\ `.___.'\\  | |");
        puts("| ||_____||_____|| || ||____|  |____|| || |   `._____.'  | |");
        puts("| |              | || |              | || |              | |");
        puts("| '--------------' || '--------------' || '--------------' |");
        puts(" '----------------'  '----------------'  '----------------' ");

        puts("What do you want to do ?");
        puts("0. Quit");
        puts("1. Do a research ");
        scanf("%i", &c);
        switch (c)
        {
            case 1:
            puts("What do you want to search ? : \n");
            scanf("%s", &string_scan);

            for (int i = 0; i < strlen(string_scan); i++) {
                string_min[i] = tolower(string_scan[i]);
            }
            /*
            for(int i = 1; i < argc; i++) {
                searchDocuments(argv[i]);

            }
            */
            printf("Vous recherchez %s \nnous rechercherons alors avec le mot %s \n", string_scan, string_min);
            //TODO on mettra le petit programme pour chercher le programme
            break;
            case 0:
            x = 0;
            break;
        default:
            puts("Please choose between 0 and 1, quit or do some research");
            x = 1;

            break;
        }
    }
    return 1;
}