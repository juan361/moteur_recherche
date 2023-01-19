#include "MotDeRech.h"

void Find_glob_Doc(const char *MotATrouver)
{
    DIR *DirCRI = opendir(PATH_CRI);
    int *counts = malloc(sizeof(int) * 1000);
    char **NomFichiers = malloc(sizeof(char *) * 1000);
    int documents = 0;
    if (DirCRI)
    {
        struct dirent *ent;
        while ((ent = readdir(DirCRI)) != NULL) 
        {
            if (ent->d_type == DT_REG)
            {
                int count = Find_Doc(MotATrouver, ent->d_name);
                if (count > 0) 
                {
                    counts[documents] = count;
                    NomFichiers[documents] = malloc(strlen(ent->d_name) + 1);
                    strcpy(NomFichiers[documents], ent->d_name);
                    documents++;
                }
            }
        }
        closedir(DirCRI);
    }
    else 
    {
        printf("Erreur d'ouverture du répertoire textes_CRI %s %d\n", strerror(errno), errno);
        exit(1);
    }
    
    //Trie les documents par le nombre de fois que Mot appairait en eux
    for (int i = 0; i < documents; i++) 
    {
        for (int j = i + 1; j < documents; j++) 
        {
            if (counts[i] < counts[j]) 
            {
                int tempCount = counts[i];
                counts[i] = counts[j];
                counts[j] = tempCount;

                char *tempNomFichier = NomFichiers[i];
                NomFichiers[i] = NomFichiers[j];
                NomFichiers[j] = tempNomFichier;
            }
        }
    }

    // Affichage
    printf("\n> \"%s\" est présent tant de fois :\n", MotATrouver);
    for (int i = 0; i < documents; i++) 
    {
        printf("%s : %d\n", NomFichiers[i], counts[i]);
    }
    if(documents == 0) {
        printf("Aucun mot trouvé\n");
    }

    for (int i = 0; i < documents; i++) 
    {
        free(NomFichiers[i]);
    }
    free(NomFichiers);
    free(counts);
}


int Find_Doc(const char *MotATrouver, const char *NomFichier){
    char *PathCRI = malloc(strlen(PATH_CRI) + strlen(NomFichier) + 1);
    strcpy(PathCRI, PATH_CRI);
    strcat(PathCRI, NomFichier);
    FILE *index = fopen(PathCRI, "r");

    if (index == NULL) {
        printf("Erreur d'ouverture du fichier CRI %s\n", PathCRI);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    int count = 0;
    
    //Lis chaque ligne du CRI pour récupérer l'occurence du mot
    while ((read = getline(&line, &len, index)) != -1) {
        char *Mot = strtok(line, " ");
        char *countStr = strtok(NULL, " ");

        if (Mot_Egaux(Mot, MotATrouver)) {
            count = atoi(countStr);
            break;
        }
    }

    fclose(index);
    free(line);
    free(PathCRI);
    return count;
}



void Créa_glob_CRI()
{
	//teste l'ouverture des dossier
    DIR *DirCRI = opendir(PATH_CRI);
    if (DirCRI)
    {
        closedir(DirCRI);
    }
    else
    {
        printf("Erreur d'ouverture du répertoire textes_CRI %s %d\n", strerror(errno), errno);
        exit(1);
    }

    DIR *dirDocs = opendir(PATH_TXT);
    if (dirDocs) 
    {
        struct dirent *ent;// srtucture de gestion de dossier
        while ((ent = readdir(dirDocs)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                Créa_CRI(ent->d_name);
            }
        }
        closedir(dirDocs);
    }
    else
    {
        printf("Erreur d'ouverture du répertoire textes_txt %s %d\n", strerror(errno), errno);
        exit(1);
    }
}


void Créa_CRI(const char *NomFichier)
{
	//gere l'ouverture du fichier .txt
    char *PathTxt = malloc(strlen(PATH_TXT) + strlen(NomFichier) + 1);
    strcpy(PathTxt, PATH_TXT);
    strcat(PathTxt, NomFichier); 
    FILE *doc = fopen(PathTxt, "r");
    
    char *PathCRI = malloc(strlen(PATH_CRI) + strlen(NomFichier) + 1);
    if(strstr(NomFichier, ".txt") == NULL) //cherche la première occurence de .txt dans NomFichier
    {
        return;
    }
	//gere l'ouverture du fichier .CRI
    char *NomSansExtention = malloc(strlen(NomFichier) - 4 + 1);
    strncpy(NomSansExtention, NomFichier, strlen(NomFichier) - 4);
    NomSansExtention[strlen(NomFichier) - 4] = '\0';

    strcpy(PathCRI, PATH_CRI);
    strcat(PathCRI, NomSansExtention);
    strcat(PathCRI, ".CRI");
    FILE *index = fopen(PathCRI, "w");
	//vérif que ouverture correcte
    if (doc == NULL) 
    {
        printf("Erreur d'ouverture du document : %s\n", PathTxt);
        exit(1);
    }

    if (index == NULL) 
    {
        printf("Erreur d'ouverture ou de création du document CRI %s\n", PathCRI);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    char **Mots = malloc(sizeof(char *) * 1000);
    int *Ocu_Mot = malloc(sizeof(int) * 1000);
    int wordCount = 0;

    //Lis chaque ligne du document et récupère chaque mot
    while ((read = getline(&line, &len, doc)) != -1) 
    {
        char *Mot = strtok(line, " ");// créer une sous liste de caratère a chaque espace
        while (Mot != NULL) 
        {
            char *wordLower = transformer_en_minuscule_sans_ponctuation(Mot);
            char *MotSingulier = SingulierTransfo(wordLower);
            
            if(!hasOnlyLetters(MotSingulier))
            {
                break;
                //s'il y a des caractère spéciaux on passe au mot d'après
            }

            bool MotExiste = false;
            for (int i = 0; i < wordCount; i++) 
           {
                if (Mot_Egaux(MotSingulier, Mots[i])) 
                {
                // Si on retrouve le même mot on augmante l'occurence
                    Ocu_Mot[i]++;
                    MotExiste = true;
                    break;
                }
            }

            if (!MotExiste) //si le mot n'est pas déjà écrit dans le fichier on l'écrit
           {
                char *CopieMot = malloc(strlen(MotSingulier) + 1);
                strcpy(CopieMot, MotSingulier);
                Mots[wordCount] = CopieMot;
                Ocu_Mot[wordCount] = 1;
                wordCount++;
                if(wordCount % 1000 == 0)
                {
                //si on a rempli le tableau de mots on réalloue de la mémoire
                    Mots = realloc(Mots, sizeof(char *) * (wordCount + 1000));
                    Ocu_Mot = realloc(Ocu_Mot, sizeof(int) * (wordCount + 1000));
                }
            }

            Mot = strtok(NULL, " "); //termine strtok
            free(wordLower);		
            free(MotSingulier);
        }
    }

    //On écrit chaque mot et leurs nbs d'occurences dans le fichier CRI
    for (int i = 0; i < wordCount; i++) 
    {
        fprintf(index, "%s %d\n", Mots[i], Ocu_Mot[i]);
    }

    fclose(doc);
    fclose(index);
    for(int i = 0; i < wordCount; i++)
    {
        free(Mots[i]);
    }

    free(Mots);
    free(Ocu_Mot);
    free(line);
    free(PathCRI);
}

bool Mot_Egaux(const char *Mot1, const char *Mot2)
{
    char *Mot1Minu = transformer_en_minuscule_sans_ponctuation(Mot1);
    char *Mot2Minu = transformer_en_minuscule_sans_ponctuation(Mot2);

    char *Mot1Singulier = SingulierTransfo(Mot1Minu);
    char *Mot2Singulier = SingulierTransfo(Mot2Minu);

    bool areEqual = strcmp(Mot1Singulier, Mot2Singulier) == 0;

	//libère les espace des malloc
    free(Mot1Minu);
    free(Mot2Minu);
    free(Mot1Singulier);
    free(Mot2Singulier);
    
    return areEqual;
}

bool hasOnlyLetters(const char *word) 
{
    for (int i = 0; i < strlen(word); i++) 
    {
        if (!isalpha(word[i]) && word[i] != '-') /* isalpha vérifie si word[i] est une lettre ou un - */
        {
            return false;
        }
    }
    return true;
}

char *transformer_en_minuscule_sans_ponctuation(const char *Mot) 
{
    char *MotMinuscule = (char *) malloc(strlen(Mot) + 1);
    for (int i = 0; i < strlen(Mot); i++) 
    {
    	//si Mot[i] est compris entre A et Z
        if (Mot[i] >= 'A' && Mot[i] <= 'Z') 
        {
        // On rajoute 32 a son code ASCI ce qui veut dire quon les fait passer en minuscule
            MotMinuscule[i] = Mot[i] + 32;
        }
        else if (Mot[i] >= 'a' && Mot[i] <= 'z') 
        {
            MotMinuscule[i] = Mot[i];
        } 
        else 
        {
        // Si Mot[i] n'est pas une lettre je le remplace par un \0 
            MotMinuscule[i] = '\0';
            break;
        }
    }
    MotMinuscule[strlen(Mot)] = '\0';

    return MotMinuscule;
}

char *SingulierTransfo(const char *Mot) 
{
    char *Singulier;
    // vas regarder si le mot finis par un s 
    if(Mot[strlen(Mot) -1] == 's') 
    {
    	// si oui on enlève la dernière lettre (donc un le s) 
        Singulier = strndup(Mot, strlen(Mot) -1);  
        /* The  strdup() function returns a pointer to a new string which is a du‐
       plicate of the string s.  Memory for the new string  is  obtained  with
       malloc(3), and can be freed with free(3).
       The strndup() function is similar, but copies at most n bytes.  If s is
       longer than n, only n bytes are copied, and  a  terminating  null  byte
       ('\0') is added.*/
    }
    else
    {
        Singulier = strdup(Mot);
    }
    return Singulier;
}
