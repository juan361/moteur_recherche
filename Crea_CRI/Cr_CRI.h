#ifndef CR_CRI_H
#define CR_CRI_H

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>

#include "Cr_CRI.c"

char* filename(char* PATH,char FileName[3][20]);
/* Fonction qui récupère les noms de tous les fichiers présent dans le répertoire pointé par PATH et qui les stoque dans le tableau FileName*/

void Crea_CRI(char *TxtName);
/* Fonction qui créée des fichier vide qui se termine par CRI de meme nom que les fichier texte */

void Fill_Cri(char path[100]);
/* Fonction qui remplie les fichier CRI par le compte de tous les mots */

#endif
