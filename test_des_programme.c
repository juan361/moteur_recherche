#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


//#define PATH "/home/isen/Algo/MotdeRech/moteur_recherche/textes"
char** filename(char* PATH,char FileName[3][20])
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
			strncpy(FileName[i],c , strlen(c) - 4);
			i++;
        	}
		entity= readdir(dir);
        }
       /*for (i=0;i<c;i++)
        	{free(FileName[i]);}
        free(FileName);*/
	closedir(dir);
	return(FileName);
}

int main(int argc, char* argv[]) 
{
	//char **FileName = (char**)malloc(sizeof(char *) * 3);
	char test[3][20];
    	filename("/home/isen/Algo/MotdeRech/moteur_recherche/textes",test);
    for (int i=0;i<3;i++)
    {
    	printf("%s\n",test[i]);
    }
    return 0;
}
