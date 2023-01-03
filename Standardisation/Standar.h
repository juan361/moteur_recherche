/**
* \name       Standard
* \brief      Ensemble de fonction permettant de copier les fichier textes puis de formaliser ces copies pour permettre l'indexation
**/

void CopieTxt(char Nom_du_texte)
/*cette fonction réalise une copie d'un fichier texte donné*/
{
    FILE *ft1, *ft2;
    char ch;
  
    // ouvrir le fichier en lecture
    ft1 = fopen(Nom_du_texte, "r");
    // ouvrir le fichier en écriture
    ft2 = fopen("STD.txt", "w");
    // Lire le contenu du fichier puis l'écrire dans l'autre
    while((ch = getc(fp1)) != EOF)
        putc(ch, fp2);
  
    fclose(fp1);
    fclose(fp2);
    getch();
}






srtlwr()
