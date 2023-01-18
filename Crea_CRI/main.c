
#include "Cr_CRI.h"

int main(int argc, char *argv[]) 
{
    Documents_CRI();
    for(int i = 1; i < argc; i++)
    {
        CherchMots(argv[i]);
    }
}
