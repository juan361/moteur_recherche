#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>



#define TXT_PATH "/home/isen/Algo/MotdeRech/moteur_recherche/textes_TXT/"
#define CRI_PATH "/home/isen/Algo/MotdeRech/moteur_recherche/textes_CRI/"
char** filename(char* PATH,char *FileName[3][20])
{
	DIR* dir=opendir(PATH);
	int i=0;
	char * c;
	if (dir == NULL)
	{
		exit(EXIT_FAILURE);
	}
	struct dirent* entity;	// on fait appel a la structure présente dans la bibliothèque dirent.h
	
	
	entity = readdir(dir);
	while (entity != NULL) 
	{
		if (entity->d_type==DT_REG)	//DT_REG enum qui réfere au entitée de type fichier
		{
			//FileName[i] = (char*)malloc(strlen(entity->d_name) + 1);
			c=entity->d_name;
			i++;
        	}
		entity= readdir(dir);
        }
       /*for (i=0;i<c;i++)
        	{free(FileName[i]);}
        free(FileName);*/
	closedir(dir);
}
void Crea_CIR(char TxtName)
{
	char *docPath = malloc(strlen(TXT_PATH) + strlen(TxtName) + 1);
	docPath = strcpy(docPath, TXT_PATH);
	docPath = strcat(docPath, TxtName); 
	FILE *doc = fopen(docPath, "r");
	
	char *CIRPath = malloc(strlen(CRI_PATH) + strlen(TxtName) + 1);
	if(strstr(TxtName, ".txt") == NULL)
	{
		return;
	}
	//crée une version de la variable TxtName sans extension
	char *SimpleName = malloc(strlen(TxtName) - 4 + 1);
	strncpy(SimpleName, TxtName, strlen(TxtName) - 4);
	SimpleName[strlen(TxtName) - 4] = '\0';
	
	strcpy(CIRPath, CRI_PATH);
	strcat(CIRPath, SimpleName);
	strcat(CIRPath, ".CRI");
	FILE *index = fopen(CIRPath, "w");
	
	//vérifie si le fichier txt c'est bien ouvert
	if (doc == NULL) 
	{
		printf("Error opening document : %s\n", docPath);
		exit(1);
	}
	// vérifie si le fichier CRI c'est bien ouvert
	if (index == NULL) 
	{
		printf("Error opening/creating index file %s\n", CIRPath);
		exit(1);
	}
}

int main(int argc, char* argv[]) 
{
	//char **FileName = (char**)malloc(sizeof(char *) * 3);
	char test[3][20];
    	filename("/home/isen/Algo/MotdeRech/moteur_recherche/textes_txt",test);
    for (int i=0;i<3;i++)
    {
    	printf("%s\n",test[i]);
    	puts("c");
    }
    Crea_CIR("brain.txt");
    return 0;
}

