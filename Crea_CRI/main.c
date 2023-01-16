
#include "Cr_CRI.h"


#define TXT_PATH "/home/isen/Algo/MotdeRech/moteur_recherche/textes_txt/"
#define CRI_PATH "/home/isen/Algo/MotdeRech/moteur_recherche/textes_CIR/"
#define MAX_WORDS   1000
#define NB_FILE 3

int main(int argc, char* argv[]) 
{
	char test[3][20];
	filename(TXT_PATH,test);
	for (int i=0;i<NB_FILE;i++)
	{
		char *pathcri=CRI_PATH;
		Crea_CRI(test[i]);
		
		strcat(pathcri, test[i]);
		strcat(pathcri, ".CRI");
		Fill_Cri(pathcri);
		
		printf("%s\n",test[i]);
	}
	
	
	return 0;
}
