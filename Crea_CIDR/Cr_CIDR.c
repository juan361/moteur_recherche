#include "Standard.h"


#define MAX_WORDS   1000

void Cop_Mot(FILE *F)
{
	{
		char path[100];
		int i, len, index, isUnique;
	    
	    // déclarations liste de mots

		char words[MAX_WORDS][50];
	    	char word[50];

	    // déclaration de la liste compte mot

		int  count[MAX_WORDS];

	    // récupération du chemin vers le fichier

		printf("quel est le chemin vers le fichier: ");
		scanf("%s", path);

	    // Ouverture du fichier et vérification 

		F = fopen(path, "r");
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


	    for (i=0; i<index; i++)

	    {
		printf("%-15s %d\n", words[i], count[i]);
	    }    
	    return 0;

	}
}
