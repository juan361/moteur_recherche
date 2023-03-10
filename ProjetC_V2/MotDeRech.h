#ifndef MOT_RECH_H
#define MOT_RECH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define PATH_TXT "./textes_txt/"
#define PATH_CRI "./textes_CRI/"

typedef enum { false, true } bool;

void Créa_glob_CRI();
/**
 * @brief La fonction Créa_glob_CRI appelle la fonction Créa_CRI pour chaque document dans un dossier de documents pour créer des fichiers d'index pour chacun de ces documents.
 *  Ces fichiers d'index contiennent des mots uniques, convertis en minuscules et en singulier en anglais, pour chaque document.
 */
void Créa_CRI(const char *NomFichier);
/**
 * @brief La fonction Créa_CRI prend en paramètre le nom d'un document, elle ouvre le document, lit chaque mot dans le document, 
 * utilise la fonction Min_Ponct pour convertir le mot en minuscules et enlever les symboles,
 *  puis utilise la fonction SingulierTransfo pour convertir le mot en singulier en anglais. 
 * Elle vérifie ensuite si le mot contient des lettres en utilisant la fonction containLetters, 
 * et si c'est le cas, elle ajoute le mot à un fichier d'index pour ce document.
 * 
 * @param NomFichier The name of the document to index
 */


void Find_glob_Doc(const char *MotATrouver);
/**
 * @brief La fonction Find_glob_Doc prend en paramètre un mot à rechercher, elle ouvre le dossier d'index, lit chaque fichier 
 * d'index dans le dossier et appelle la fonction Find_Doc pour rechercher le mot dans chaque fichier d'index. Elle stocke ensuite le nombre de fois où 
 * le mot apparaît dans chaque document dans un tableau, trie le tableau en fonction de ce nombre, et imprime les résultats.
 * 
 * @param MotATrouver The Mot to search for
 */
int Find_Doc(const char *MotATrouver, const char *NomFichier);
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


bool Mot_Egaux(const char *Mot1, const char *Mot2);
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
bool containLetters(const char *Mot);
/**
 * @brief La fonction containLetters prend en paramètre un mot et vérifie si ce mot contient des lettres. 
 * Elle retourne true si le mot contient des lettres, false sinon.
 * 
 * @param Mot 
 * @return true 
 * @return false 
 */


char *transformer_en_minuscule_sans_ponctuation(const char *Mot);
/**
 * @brief Convert a Mot to lower case and remove symbols
 * 
 * @param Mot 
 * @return char*
 */
char *SingulierTransfo(const char *Mot);
/**
 * @brief La fonction SingulierTransfo prend en paramètre un mot, 
 * il convertit le mot en singulier en anglais et retourne le mot modifié.
 * 
 * @param Mot 
 * @return char* 
 */

#endif
