#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define DOC_PATH "./docs/"
#define INDEX_PATH "./index/"


__MINGW_EXTENSION typedef unsigned __int64 size_t;
typedef enum { false, true } bool;

char *toLowerCaseAndRemoveSymbols(const char *word){
    size_t len = strlen(word);
    char *lowerCaseWord = (char *) malloc(len + 1);

    for (size_t i = 0; i < len; i++)
    {
        if(word[i] >= 'A' && word[i] <= 'Z'){
            lowerCaseWord[i] = word[i] + 32;
        } else {
            lowerCaseWord[i] = word[i];
        }
    }
    lowerCaseWord[len] = '\0';

    for(size_t i = 0; i < len; i++){
        if (lowerCaseWord[i] == '.' || lowerCaseWord[i] == ',' || lowerCaseWord[i] == ';' || lowerCaseWord[i] == ':' || lowerCaseWord[i] == '!' || lowerCaseWord[i] == '?' || lowerCaseWord[i] == '"' || lowerCaseWord[i] == '(' || lowerCaseWord[i] == ')' || lowerCaseWord[i] == '\'' || lowerCaseWord[i] == '\n'){
            lowerCaseWord[i] = '\0';
            break;
        }
    }

    return lowerCaseWord;
}

char *englishSing(const char *word) {
    size_t len = strlen(word);
    char *singular = (char *) malloc(len + 1);
    if (len > 2 && word[len - 1] == 's') {
        if(
            (word[len - 2] == 'e' && word[len - 3] == 'i')
            || (word[len - 2] == 'a')
        ){
            // word is already in singular form
            strcpy(singular, word);
        } else {
            strncpy(singular, word, len - 1);
            singular[len - 1] = '\0';
        }
    } else {
        //word is already in singular form
        strcpy(singular, word);
    }

    return singular;
}


bool wEqual(const char *word1, const char *word2){
    char *word1C = malloc(strlen(word1) + 1);
    char *word2C = malloc(strlen(word2) + 1);
    strcpy(word1C, word1);
    strcpy(word2C, word2);
    char *word1L = toLowerCaseAndRemoveSymbols(word1C);
    char *word2L = toLowerCaseAndRemoveSymbols(word2C);
    char *word1S = englishSing(word1C);
    char *word2S = englishSing(word2C);
    bool equal = strcmp(word1S, word2S) == 0;
    free(word1C);
    free(word2C);
    free(word1L);
    free(word2L);
    free(word1S);
    free(word2S);
    return equal;
}

int main(int argc, char *argv[]){
    bool r;
    char *w1;
    char *w2;
    printf("mot 1 \n");
    scanf("%s", &w1);

    printf("mot 2 \n");
    scanf("%s", &w2);

    r = wEqual(*w1,*w2);
    

    if(r==0){
        printf("false\n");
    }else if(r==1){
        printf("true\n");
    }else{
        puts("ERROR");
    }

    return 1;
}