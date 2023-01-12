#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


//#define PATH "/home/isen/Algo/MotdeRech/moteur_recherche/textes"
void filename(char* PATH,)
{
	DIR* dir=opendir(PATH);
	int i=0,c;
	if (dir == NULL)
	{
		return ;
	}
	struct dirent* entity;	// on fait appel a la structure présente dans la bibliothèque dirent.h
	char **FileName = (char**)malloc(sizeof(char *) * 1000);
	
	entity = readdir(dir);
	while (entity != NULL) 
	{
		if (entity->d_type==DT_REG)	//DT_REG enum qui réfere au entitée de type fichier
		{
			FileName[i] = (char*)malloc(strlen(entity->d_name) + 1);
			FileName[i] = entity->d_name;
			printf("%s\n",FileName[i]);
			i++;
			c=i;
        	}
		entity= readdir(dir);
        }
        puts("ok2");
        for (i=0;i<=3;i++){free(FileName[i]);}
        free(FileName);
	closedir(dir);
}

int main(int argc, char* argv[]) 
{
    filename("/home/isen/Algo/MotdeRech/moteur_recherche/textes");
    return 0;
}
