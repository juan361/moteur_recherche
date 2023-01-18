#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define PATH_TXT "../textes_txt/"
#define PATH_CRI "../textes_CRI/"

typedef enum { false, true } bool;

void Créa_glob_CRI();
void Créa_CRI(const char *NomFichier);

void Find_glob_Doc(const char *MotATrouver);
int Find_Doc(const char *MotATrouver, const char *NomFichier);

bool Mot_Egaux(const char *Mot1, const char *Mot2);
bool fileContainsWord(char *MotATrouver, char *filePath);
bool containLetters(const char *Mot);

char *Min_Ponct(const char *Mot);
char *SingulierTransfo(const char *Mot);

//void Mise_A_Jour();


int main(int argc, char *argv[]) {
    //Créa_glob_CRI();
    printf("File: %s\n", argv[0]);
    //Mise_A_Jour();
    for(int i = 1; i < argc; i++) {
        Find_glob_Doc(argv[i]);
    }
}
/*
void Mise_A_Jour()
{
	FILE *pipe = popen("/tmp/crontab.S4aol3/crontab","w+");
	if (pipe == NULL) 
	{
        perror("popen failed");
        return;
        }
        
        pclose(pipe);
}
*/

/**
 * @brief La fonction Find_glob_Doc prend en paramètre un mot à rechercher, elle ouvre le dossier d'index, lit chaque fichier 
 * d'index dans le dossier et appelle la fonction Find_Doc pour rechercher le mot dans chaque fichier d'index. Elle stocke ensuite le nombre de fois où 
 * le mot apparaît dans chaque document dans un tableau, trie le tableau en fonction de ce nombre, et imprime les résultats.
 * 
 * @param MotATrouver The Mot to search for
 */
void Find_glob_Doc(const char *MotATrouver){
    DIR *DirCRI = opendir(PATH_CRI);
    int *counts = malloc(sizeof(int) * 1000);
    char **NomFichiers = malloc(sizeof(char *) * 1000);
    int documents = 0;
    if (DirCRI) {
        struct dirent *ent;
        while ((ent = readdir(DirCRI)) != NULL) {
            if (ent->d_type == DT_REG) {
                int count = Find_Doc(MotATrouver, ent->d_name);
                if (count > 0) {
                    counts[documents] = count;
                    NomFichiers[documents] = malloc(strlen(ent->d_name) + 1);
                    strcpy(NomFichiers[documents], ent->d_name);
                    documents++;
                }
            }
        }
        closedir(DirCRI);
    } else {
        printf("Error opening index folder %s %d\n", strerror(errno), errno);
        exit(1);
    }

    // Sort the documents by the number of times the Mot appears in them
    for (int i = 0; i < documents; i++) {
        for (int j = i + 1; j < documents; j++) {
            if (counts[i] < counts[j]) {
                int tempCount = counts[i];
                counts[i] = counts[j];
                counts[j] = tempCount;

                char *tempNomFichier = NomFichiers[i];
                NomFichiers[i] = NomFichiers[j];
                NomFichiers[j] = tempNomFichier;
            }
        }
    }

    // Print the results
    printf("\n> \"%s\" search results :\n", MotATrouver);
    for (int i = 0; i < documents; i++) {
        printf("%s : %d\n", NomFichiers[i], counts[i]);
    }
    if(documents == 0) {
        printf("No results found\n");
    }

    for (int i = 0; i < documents; i++) {
        free(NomFichiers[i]);
    }
    free(NomFichiers);
    free(counts);
}

/**
 * @brief La fonction Find_Doc prend en paramètre un mot à rechercher et le nom d'un document, elle ouvre un fichier d'index donné, lit chaque ligne du fichier, 
 * et utilise la fonction Mot_Egaux pour vérifier si le mot recherché est égal à un mot dans la ligne. 
 * Si c'est le cas, elle incrémente un compteur et retourne le nombre de fois où le mot a été trouvé dans le document.
 * 
 * @param MotATrouver The Mot to search for
 * @param NomFichier The name of the document to search
 * 
 * @return The number of times the Mot appears in the document
 */
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

    // Read each line of the index file and get the count for the Mot
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


/**
 * @brief La fonction Créa_glob_CRI appelle la fonction Créa_CRI pour chaque document dans un dossier de documents pour créer des fichiers d'index pour chacun de ces documents.
 *  Ces fichiers d'index contiennent des mots uniques, convertis en minuscules et en singulier en anglais, pour chaque document.
 */
void Créa_glob_CRI(){
    DIR *DirCRI = opendir(PATH_CRI);
    if (DirCRI) {
        closedir(DirCRI);
    } else {
        printf("Error opening index folder %s %d\n", strerror(errno), errno);
        exit(1);
    }

    DIR *dirDocs = opendir(PATH_TXT);
    if (dirDocs) {
        struct dirent *ent;
        while ((ent = readdir(dirDocs)) != NULL) {
            if (ent->d_type == DT_REG) {
                Créa_CRI(ent->d_name);
            }
        }
        closedir(dirDocs);
    } else {
        printf("Error opening docs folder %s %d\n", strerror(errno), errno);
        exit(1);
    }
}

/**
 * @brief La fonction Créa_CRI prend en paramètre le nom d'un document, elle ouvre le document, lit chaque mot dans le document, 
 * utilise la fonction Min_Ponct pour convertir le mot en minuscules et enlever les symboles,
 *  puis utilise la fonction SingulierTransfo pour convertir le mot en singulier en anglais. 
 * Elle vérifie ensuite si le mot contient des lettres en utilisant la fonction containLetters, 
 * et si c'est le cas, elle ajoute le mot à un fichier d'index pour ce document.
 * 
 * @param NomFichier The name of the document to index
 */
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
        printf("Error opening document : %s\n", PathTxt);
        exit(1);
    }

    if (index == NULL) 
    {
        printf("Error opening/creating index file %s\n", PathCRI);
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
            char *wordLower = Min_Ponct(Mot);
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

/**
 * @brief La fonction Mot_Egaux prend en paramètre deux mots, elle convertit les deux mots en minuscules, enlève les symboles et vérifie si les deux mots sont égaux. 
 * Elle retourne true si les deux mots sont égaux, false sinon. 
 * Elle est utilisée pour vérifier si un mot recherché est présent dans un document.
 * 
 * @param Mot1
 * @param Mot2
 * @return true if equal
 * @return false if not equal
 */
bool Mot_Egaux(const char *Mot1, const char *Mot2){
    char *CopieMot1 = malloc(strlen(Mot1) + 1);
    char *CopieMot2 = malloc(strlen(Mot2) + 1);
    strcpy(CopieMot1, Mot1);
    strcpy(CopieMot2, Mot2);

    char *Mot1Minu = Min_Ponct(CopieMot1);
    char *Mot2Minu = Min_Ponct(CopieMot2);

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


/**
 * @brief La fonction containLetters prend en paramètre un mot et vérifie si ce mot contient des lettres. 
 * Elle retourne true si le mot contient des lettres, false sinon.
 * 
 * @param Mot 
 * @return true 
 * @return false 
 */
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

/**
 * @brief Convert a Mot to lower case and remove symbols
 * 
 * @param Mot 
 * @return char*
 */
char *Min_Ponct(const char *Mot){
    size_t len = strlen(Mot);
    char *MotMinuscule = (char *) malloc(len + 1);

    for (size_t i = 0; i < len; i++)
    {
        if(Mot[i] >= 'A' && Mot[i] <= 'Z'){
            MotMinuscule[i] = Mot[i] + 32;
        } else {
            MotMinuscule[i] = Mot[i];
        }
    }
    MotMinuscule[len] = '\0';

    for(size_t i = 0; i < len; i++){
        if (MotMinuscule[i] == '.' || MotMinuscule[i] == ',' || MotMinuscule[i] == ';' || MotMinuscule[i] == ':' || MotMinuscule[i] == '!' || MotMinuscule[i] == '?' || MotMinuscule[i] == '"' || MotMinuscule[i] == '(' || MotMinuscule[i] == ')' || MotMinuscule[i] == '\'' || MotMinuscule[i] == '\n'){
            MotMinuscule[i] = '\0';
            break;
        }
    }

    return MotMinuscule;
}

/**
 * @brief La fonction SingulierTransfo prend en paramètre un mot, 
 * il convertit le mot en singulier en anglais et retourne le mot modifié.
 * 
 * @param Mot 
 * @return char* 
 */
char *SingulierTransfo(const char *Mot) {
    size_t len = strlen(Mot);
    char *Singulier = (char *) malloc(len + 1);
    if (len > 2 && Mot[len - 1] == 's') {
        if(
            (Mot[len - 2] == 'e' && Mot[len - 3] == 'i')
            || (Mot[len - 2] == 'a')
        ){
            // Mot is already in Singulier form
            strcpy(Singulier, Mot);
        } else {
            strncpy(Singulier, Mot, len - 1);
            Singulier[len - 1] = '\0';
        }
    } else {
        //Mot is already in Singulier form
        strcpy(Singulier, Mot);
    }

    return Singulier;
}
