#include <stdio.h>
#include "functiigof.h"

int main(int argc, char* argv[])
{
    
    int T, N, M, K;
    char **matrice = citire(argv[1], &T, &N, &M, &K);
  

    afisare(argv[2], matrice, N);


    for(int i=0; i<K; i++)
    {
        schimbare(matrice, N, M);
        afisare(argv[2], matrice, N);
    }

    eliberare(matrice, N);

    return 0;
}