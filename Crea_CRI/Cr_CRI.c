
#include "Cr_CRI.h"


#define TXT_PATH "/home/isen/Algo/MotdeRech/moteur_recherche/textes_txt/"
#define CRI_PATH "/home/isen/Algo/MotdeRech/moteur_recherche/textes_CRI/"
#define MAX_WORDS   1000
#define NB_FILE 3

char* filename(char* PATH,char FileName[3][20])
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
			strncpy(FileName[i],c, strlen(c) - 4);
			FileName[i][strlen(c) - 4] = '\0';
			//printf("%s\n",FileName[i]);
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

void Crea_CRI(char *TxtName)
{
	char *TxtPath = malloc(strlen(TXT_PATH) + strlen(TxtName) + 1);
	TxtPath = strcpy(TxtPath, TXT_PATH);
	TxtPath = strcat(TxtPath, TxtName);
	TxtPath = strcat(TxtPath, ".txt");
	FILE *doc = fopen(TxtPath, "r");
	
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
		printf("Error opening document : %s\n", TxtPath);
		exit(1);
	}
	// vérifie si le fichier CRI c'est bien crée
	if (index == NULL) 
	{
		printf("Error opening/creating index file %s\n", CIRPath);
		exit(1);
	}
	fclose(doc);
	fclose(index);
}

void Fill_Cri(char path[100])
{
	{
		int i, len, index, isUnique;
		FILE *F;
	    
	    // déclarations liste de mots

		char words[MAX_WORDS][50];
	    	char word[50];
		
		char PathTxt[200]=TXT_PATH;
		strcat(PathTxt,path);
		strcat(PathTxt,".txt");
		char PathCRI[200]=CRI_PATH;
		strcat(PathCRI,path);
		strcat(PathCRI,".CRI");
		
	    // déclaration de la liste compte mot

		int  count[MAX_WORDS];

	    // Ouverture du fichier et vérification 
		F = fopen(PathTxt, "r");
		if (F == NULL)
		{
	    		printf("Erreur d'ouverture.\n");
			exit(EXIT_FAILURE);
		}

	    // Initialisation du tableau compte mot a 0

		for (i=0; i<MAX_WORDS; i++)
			count[i] = 0;

		index = 0;

		while (fscanf(F, "%s", word) != EOF)
		{
	    // Mettre le mot récupéré en minuscule

			tolower(word);

	    // Supression des caractères spéciaux 

			 len = strlen(word);
        
		if (ispunct(word[len - 1]))
 			word[len - 1] = '\0';
		while (ispunct(word[strlen(word) - 1]))
		{
			word[strlen(word) - 1] = '\0';
		}
	    // Check si le mot lue est déja présent dans la liste de tous les mots

			isUnique = 1;				//IsUnique = 1 -> le mot est unique , IsUnique = 0 -> le mot esty déja présent
			for (i=0; i<index && isUnique; i++)
			{
				if (strcmp(words[i], word) == 0)
				isUnique = 0;
			}

		// If word is unique then add it to distinct words list

		// and increment index. Otherwise increment occurrence 

		// count of current word.

			if (isUnique) 
			{
			    strcpy(words[index], word);
			    count[index]++;

			    index++;
			}
			else
			{
			    count[i - 1]++;
			}
		}



	    // Close file

	    fclose(F);
	FILE *D=fopen(PathCRI,"w");

	    for (i=0; i<index; i++)

	    {
	    	fprintf(D,"%-45s%d\n", words[i],count[i]);
	    }    
	    fclose(D);
	    return ;

	}
}
