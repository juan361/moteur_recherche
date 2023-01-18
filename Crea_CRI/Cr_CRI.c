
#include "Cr_CRI.h"

#define PATH_TXT "../textes_txt/"
#define PATH_CRI "../textes_CRI/"

void indexDocuments();
void indexDocument(const char *docName);

void searchDocuments(const char *wordToFind);
int searchDocument(const char *wordToFind, const char *docName);

bool areTwoWordsEqual(const char *word1, const char *word2);
bool containLetters(const char *word);

char *toLowerCaseAndRemoveSymbols(const char *word);
char *englishSingular(const char *word);


int main(int argc, char *argv[]) {
    indexDocuments();
    for(int i = 1; i < argc; i++) {
        searchDocuments(argv[i]);
    }
}

/**
 * @brief La fonction searchDocuments prend en paramètre un mot à rechercher, elle ouvre le dossier d'index, lit chaque fichier 
 * d'index dans le dossier et appelle la fonction searchDocument pour rechercher le mot dans chaque fichier d'index. Elle stocke ensuite le nombre de fois où 
 * le mot apparaît dans chaque document dans un tableau, trie le tableau en fonction de ce nombre, et imprime les résultats.
 * 
 * @param wordToFind The word to search for
 */
void searchDocuments(const char *wordToFind){
    DIR *dirIndexs = opendir(PATH_CRI);
    int *counts = malloc(sizeof(int) * 1000);
    char **docNames = malloc(sizeof(char *) * 1000);
    int documents = 0;
    if (dirIndexs) {
        struct dirent *ent;
        while ((ent = readdir(dirIndexs)) != NULL) {
            if (ent->d_type == DT_REG) {
                int count = searchDocument(wordToFind, ent->d_name);
                if (count > 0) {
                    counts[documents] = count;
                    docNames[documents] = malloc(strlen(ent->d_name) + 1);
                    strcpy(docNames[documents], ent->d_name);
                    documents++;
                }
            }
        }
        closedir(dirIndexs);
    } else {
        printf("Error opening index folder %s %d\n", strerror(errno), errno);
        exit(1);
    }

    // Sort the documents by the number of times the word appears in them
    for (int i = 0; i < documents; i++) {
        for (int j = i + 1; j < documents; j++) {
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

    // Print the results
    printf("\n> \"%s\" search results :\n", wordToFind);
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

/**
 * @brief La fonction searchDocument prend en paramètre un mot à rechercher et le nom d'un document, elle ouvre un fichier d'index donné, lit chaque ligne du fichier, 
 * et utilise la fonction areTwoWordsEqual pour vérifier si le mot recherché est égal à un mot dans la ligne. 
 * Si c'est le cas, elle incrémente un compteur et retourne le nombre de fois où le mot a été trouvé dans le document.
 * 
 * @param wordToFind The word to search for
 * @param docName The name of the document to search
 * 
 * @return The number of times the word appears in the document
 */
int searchDocument(const char *wordToFind, const char *docName){
    char *indexPath = malloc(strlen(PATH_CRI) + strlen(docName) + 1);
    strcpy(indexPath, PATH_CRI);
    strcat(indexPath, docName);
    FILE *index = fopen(indexPath, "r");

    if (index == NULL) {
        printf("Error opening index file %s\n", indexPath);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    int count = 0;

    // Read each line of the index file and get the count for the word
    while ((read = getline(&line, &len, index)) != -1) {
        char *word = strtok(line, " ");
        char *countStr = strtok(NULL, " ");

        if (areTwoWordsEqual(word, wordToFind)) {
            count = atoi(countStr);
            break;
        }
    }

    fclose(index);
    free(line);
    free(indexPath);
    return count;
}


/**
 * @brief La fonction indexDocuments appelle la fonction indexDocument pour chaque document dans un dossier de documents pour créer des fichiers d'index pour chacun de ces documents.
 *  Ces fichiers d'index contiennent des mots uniques, convertis en minuscules et en singulier en anglais, pour chaque document.
 */
void indexDocuments(){
    DIR *dirIndexs = opendir(PATH_CRI);
    if (dirIndexs) {
        closedir(dirIndexs);
    } else {
        printf("Error opening index folder %s %d\n", strerror(errno), errno);
        exit(1);
    }

    DIR *dirDocs = opendir(DOC_PATH);
    if (dirDocs) {
        struct dirent *ent;
        while ((ent = readdir(dirDocs)) != NULL) {
            if (ent->d_type == DT_REG) {
                indexDocument(ent->d_name);
            }
        }
        closedir(dirDocs);
    } else {
        printf("Error opening docs folder %s %d\n", strerror(errno), errno);
        exit(1);
    }
}

/**
 * @brief La fonction indexDocument prend en paramètre le nom d'un document, elle ouvre le document, lit chaque mot dans le document, 
 * utilise la fonction toLowerCaseAndRemoveSymbols pour convertir le mot en minuscules et enlever les symboles,
 *  puis utilise la fonction englishSingular pour convertir le mot en singulier en anglais. 
 * Elle vérifie ensuite si le mot contient des lettres en utilisant la fonction containLetters, 
 * et si c'est le cas, elle ajoute le mot à un fichier d'index pour ce document.
 * 
 * @param docName The name of the document to index
 */
void indexDocument(const char *docName)
{
    char *docPath = malloc(strlen(DOC_PATH) + strlen(docName) + 1);
    docPath = strcpy(docPath, DOC_PATH);
    docPath = strcat(docPath, docName); 
    FILE *doc = fopen(docPath, "r");
    
    char *indexPath = malloc(strlen(PATH_CRI) + strlen(docName) + 1);
    if(strstr(docName, ".txt") == NULL)
    {
        return;
    }

    char *docNameWithoutExtension = malloc(strlen(docName) - 4 + 1);
    strncpy(docNameWithoutExtension, docName, strlen(docName) - 4);
    docNameWithoutExtension[strlen(docName) - 4] = '\0';

    strcpy(indexPath, PATH_CRI);
    strcat(indexPath, docNameWithoutExtension);
    strcat(indexPath, ".CRI");
    FILE *index = fopen(indexPath, "w");

    if (doc == NULL) 
    {
        printf("Error opening document : %s\n", docPath);
        exit(1);
    }

    if (index == NULL) 
    {
        printf("Error opening/creating index file %s\n", indexPath);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    char **words = malloc(sizeof(char *) * 1000);
    int *wordsIterate = malloc(sizeof(int) * 1000);
    int wordCount = 0;

    // Read each line of the document and get each unique word
    while ((read = getline(&line, &len, doc)) != -1) 
    {
        char *word = strtok(line, " ");
        while (word != NULL) 
        {
            char *wordLower = toLowerCaseAndRemoveSymbols(word);
            char *wordSingular = englishSingular(wordLower);
            
            if(!containLetters(wordSingular))
            {
                break;
            }

            bool wordExists = false;
            for (int i = 0; i < wordCount; i++) 
           {
                if (areTwoWordsEqual(wordSingular, words[i])) 
                {
                    wordsIterate[i]++;
                    wordExists = true;
                    break;
                }
            }

            if (!wordExists) 
           {
                char *wordCopy = malloc(strlen(wordSingular) + 1);
                strcpy(wordCopy, wordSingular);
                words[wordCount] = wordCopy;
                wordsIterate[wordCount] = 1;
                wordCount++;
                if(wordCount % 1000 == 0)
                {
                    words = realloc(words, sizeof(char *) * (wordCount + 1000));
                    wordsIterate = realloc(wordsIterate, sizeof(int) * (wordCount + 1000));
                }
            }

            word = strtok(NULL, " ");
            free(wordLower);
            free(wordSingular);
        }
    }

    // Write each word and the number of times it appears in the document to the index file
    for (int i = 0; i < wordCount; i++) 
    {
        fprintf(index, "%s %d\n", words[i], wordsIterate[i]);
    }

    fclose(doc);
    fclose(index);
    for(int i = 0; i < wordCount; i++)
    {
        free(words[i]);
    }

    free(words);
    free(wordsIterate);
    free(line);
    free(indexPath);
}

/**
 * @brief La fonction areTwoWordsEqual prend en paramètre deux mots, elle convertit les deux mots en minuscules, enlève les symboles et vérifie si les deux mots sont égaux. 
 * Elle retourne true si les deux mots sont égaux, false sinon. 
 * Elle est utilisée pour vérifier si un mot recherché est présent dans un document.
 * 
 * @param word1
 * @param word2
 * @return true if equal
 * @return false if not equal
 */
bool areTwoWordsEqual(const char *word1, const char *word2){
    char *word1Copy = malloc(strlen(word1) + 1);
    char *word2Copy = malloc(strlen(word2) + 1);
    strcpy(word1Copy, word1);
    strcpy(word2Copy, word2);

    char *word1Lower = toLowerCaseAndRemoveSymbols(word1Copy);
    char *word2Lower = toLowerCaseAndRemoveSymbols(word2Copy);

    char *word1Singular = englishSingular(word1Lower);
    char *word2Singular = englishSingular(word2Lower);

    bool areEqual = strcmp(word1Singular, word2Singular) == 0;

    free(word1Copy);
    free(word2Copy);
    free(word1Lower);
    free(word2Lower);
    free(word1Singular);
    free(word2Singular);
    
    return areEqual;
}


/**
 * @brief La fonction containLetters prend en paramètre un mot et vérifie si ce mot contient des lettres. 
 * Elle retourne true si le mot contient des lettres, false sinon.
 * 
 * @param word 
 * @return true 
 * @return false 
 */
bool containLetters(const char *word){
    bool onlyLetters = true;
    if(strlen(word) == 0){
        return false;
    }
    for(size_t i = 0; i < strlen(word); i++){
        if(!(word[i] >= 'a' && word[i] <= 'z') && !(word[i] >= 'A' && word[i] <= 'Z') && word[i] != '-'){
            onlyLetters = false;
        }
    }
    return onlyLetters;
}

/**
 * @brief Convert a word to lower case and remove symbols
 * 
 * @param word 
 * @return char*
 */
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

/**
 * @brief La fonction englishSingular prend en paramètre un mot, 
 * il convertit le mot en singulier en anglais et retourne le mot modifié.
 * 
 * @param word 
 * @return char* 
 */
char *englishSingular(const char *word) {
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
