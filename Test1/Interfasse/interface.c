#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./Check_mot/check.h"

#define INDEX_PATH "./textes_CRI/"


void searchWords(const char *word);



int main(){
    char string_scan[250], string_maj[250], string_min[250];

    printf("__moteur de recherche__ \n");
    printf("What do you want to search ? : \n");

    scanf("%s", &string_scan);

    for (int i = 0; i < strlen(string_scan); i++) {
      string_min[i] = tolower(string_scan[i]);
    }

    for(int i = 1; i < argc; i++) {
        searchDocuments(argv[i]);

    }
    printf("vous recherchez %s \nnous rechercherons alors avec le mot %s \n, ou %s", string_scan, string_maj, string_min);
    return 0;
}

void searchWords(const char *word){
	DIR *dirIndex = opendir(INDEX_PATH);
	int *counts = malloc(sizeof(int) * 1000);
	char **dprenom = malloc(sizeof(char *) * 1000);
	int docs = 0;
  if (dirIndex)
  {
    struct dirent *ent;
    while((ent = readdir(dirIndex)) != NULL){
      if(ent->d_type == DT_REG){
        int count = searchDocument(word, ent->d_name);
        if (count > 0) {
          counts[docs] = count;
          docNames[docs] = malloc(strlen(ent->d_name) + 1);
          strcpy(dprenom[docs], ent->d_name);
          docs++;

        }
      }
    }
    closedir(dirIndex);
  }else{
    printf("Error opening index folder %s %d\n", strerror(errno), errno);
    exit(1);
  }
  for (int i = 0; i < docs; i++) {
        for (int j = i + 1; j < docs; j++) {
            if (counts[i] < counts[j]) {
                int tempCount = counts[i];
                counts[i] = counts[j];
                counts[j] = tempCount;

                char *tempDocName = docNames[i];
                docNames[i] = docNames[j];
                docNames[j] = tempDocName;
            }
        }
    }
    printf("\n> \"%s\" search results :\n", word);
    for (int i = 0; i < documents; i++) {
        printf("%s : %d\n", docNames[i], counts[i]);
    }
    if(documents == 0) {
        printf("No results found\n");
    }

    for (int i = 0; i < documents; i++) {
        free(docNames[i]);
    }
    free(docNames);
    free(counts);
}

