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
        printf("Error opening index file %s\n", PathCRI);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    int count = 0;
    
    //Lie chauque ligne du CRI pour récupérer l'occurance du mot
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



void Créa_glob_CRI(){
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
        struct dirent *ent;
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
    char *PathTxt = malloc(strlen(PATH_TXT) + strlen(NomFichier) + 1);
    PathTxt = strcpy(PathTxt, PATH_TXT);
    PathTxt = strcat(PathTxt, NomFichier); 
    FILE *doc = fopen(PathTxt, "r");
    
    char *PathCRI = malloc(strlen(PATH_CRI) + strlen(NomFichier) + 1);
    if(strstr(NomFichier, ".txt") == NULL)
    {
        return;
    }

    char *NomSansExtention = malloc(strlen(NomFichier) - 4 + 1);
    strncpy(NomSansExtention, NomFichier, strlen(NomFichier) - 4);
    NomSansExtention[strlen(NomFichier) - 4] = '\0';

    strcpy(PathCRI, PATH_CRI);
    strcat(PathCRI, NomSansExtention);
    strcat(PathCRI, ".CRI");
    FILE *index = fopen(PathCRI, "w");

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

    // Read each line of the document and get each unique Mot
    while ((read = getline(&line, &len, doc)) != -1) 
    {
        char *Mot = strtok(line, " ");
        while (Mot != NULL) 
        {
            char *wordLower = transformer_en_minuscule_sans_ponctuation(Mot);
            char *MotSingulier = SingulierTransfo(wordLower);
            
            if(!containLetters(MotSingulier))
            {
                break;
            }

            bool MotExiste = false;
            for (int i = 0; i < wordCount; i++) 
           {
                if (Mot_Egaux(MotSingulier, Mots[i])) 
                {
                    Ocu_Mot[i]++;
                    MotExiste = true;
                    break;
                }
            }

            if (!MotExiste) 
           {
                char *CopieMot = malloc(strlen(MotSingulier) + 1);
                strcpy(CopieMot, MotSingulier);
                Mots[wordCount] = CopieMot;
                Ocu_Mot[wordCount] = 1;
                wordCount++;
                if(wordCount % 1000 == 0)
                {
                    Mots = realloc(Mots, sizeof(char *) * (wordCount + 1000));
                    Ocu_Mot = realloc(Ocu_Mot, sizeof(int) * (wordCount + 1000));
                }
            }

            Mot = strtok(NULL, " ");
            free(wordLower);
            free(MotSingulier);
        }
    }

    // Write each Mot and the number of times it appears in the document to the index file
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

bool Mot_Egaux(const char *Mot1, const char *Mot2){
    char *CopieMot1 = malloc(strlen(Mot1) + 1);
    char *CopieMot2 = malloc(strlen(Mot2) + 1);
    strcpy(CopieMot1, Mot1);
    strcpy(CopieMot2, Mot2);

    char *Mot1Minu = transformer_en_minuscule_sans_ponctuation(CopieMot1);
    char *Mot2Minu = transformer_en_minuscule_sans_ponctuation(CopieMot2);

    char *Mot1Singulier = SingulierTransfo(Mot1Minu);
    char *Mot2Singulier = SingulierTransfo(Mot2Minu);

    bool areEqual = strcmp(Mot1Singulier, Mot2Singulier) == 0;

    free(CopieMot1);
    free(CopieMot2);
    free(Mot1Minu);
    free(Mot2Minu);
    free(Mot1Singulier);
    free(Mot2Singulier);
    
    return areEqual;
}

bool containLetters(const char *Mot){
    bool onlyLetters = true;
    if(strlen(Mot) == 0){
        return false;
    }
    for(size_t i = 0; i < strlen(Mot); i++){
        if(!(Mot[i] >= 'a' && Mot[i] <= 'z') && !(Mot[i] >= 'A' && Mot[i] <= 'Z') && Mot[i] != '-'){
            onlyLetters = false;
        }
    }
    return onlyLetters;
}

char *transformer_en_minuscule_sans_ponctuation(const char *Mot) {
    size_t len = strlen(Mot);
    char *MotMinuscule = (char *) malloc(len + 1);

    for (size_t i = 0; i < len; i++) {
        if (Mot[i] >= 'A' && Mot[i] <= 'Z') {
            MotMinuscule[i] = Mot[i] + 32;
        } else if (Mot[i] >= 'a' && Mot[i] <= 'z') {
            MotMinuscule[i] = Mot[i];
        } else {
            MotMinuscule[i] = '\0';
            break;
        }
    }
    MotMinuscule[len] = '\0';

    return MotMinuscule;
}

char *SingulierTransfo(const char *Mot) {
    char *Singulier;
    if(Mot[strlen(Mot) -1] == 's') {
        Singulier = strndup(Mot, strlen(Mot) -1);
    } else {
        Singulier = strdup(Mot);
    }
    return Singulier;
}
