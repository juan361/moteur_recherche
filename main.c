#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INDEX_PATH "./textes_CRI/"


void searchWords(const char *word);



int main(){
    char string_scan[250];
    puts(" ----------------------");
    puts("|  ▄▄▄·  ▄▄· • ▌ ▄ ·.  |");
    puts("| ▐█ ▀█ ▐█ ▌▪·██ ▐███▪ |");
    puts("| ▄█▀▀█ ██ ▄▄▐█ ▌▐▌▐█· |");
    puts("| ▐█ ▪▐▌▐███▌██ ██▌▐█▌ |");
    puts("|  ▀  ▀ ·▀▀▀ ▀▀  █▪▀▀▀ |");
    puts("|______________________|");
     
          _____                    _____                    _____          
         /\    \                  /\    \                  /\    \         
        /::\    \                /::\    \                /::\____\        
       /::::\    \              /::::\    \              /::::|   |        
      /::::::\    \            /::::::\    \            /:::::|   |        
     /:::/\:::\    \          /:::/\:::\    \          /::::::|   |        
    /:::/__\:::\    \        /:::/  \:::\    \        /:::/|::|   |        
   /::::\   \:::\    \      /:::/    \:::\    \      /:::/ |::|   |        
  /::::::\   \:::\    \    /:::/    / \:::\    \    /:::/  |::|___|______  
 /:::/\:::\   \:::\    \  /:::/    /   \:::\    \  /:::/   |::::::::\    \ 
/:::/  \:::\   \:::\____\/:::/____/     \:::\____\/:::/    |:::::::::\____\
\::/    \:::\  /:::/    /\:::\    \      \::/    /\::/    / ~~~~~/:::/    /
 \/____/ \:::\/:::/    /  \:::\    \      \/____/  \/____/      /:::/    / 
          \::::::/    /    \:::\    \                          /:::/    /  
           \::::/    /      \:::\    \                        /:::/    /   
           /:::/    /        \:::\    \                      /:::/    /    
          /:::/    /          \:::\    \                    /:::/    /     
         /:::/    /            \:::\    \                  /:::/    /      
        /:::/    /              \:::\____\                /:::/    /       
        \::/    /                \::/    /                \::/    /        
         \/____/                  \/____/                  \/____/         
                                                                           
                                                                           



    printf("What do you want to search ? : \n");

    scanf("%s", &string_scan);
    return 0;
}