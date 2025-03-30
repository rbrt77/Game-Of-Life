#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functiigof.h"



char** alocare(int N, int M)
{
    char** matrice = (char**) malloc(N * sizeof(char*)); //pt linii
    if(matrice == NULL)
    {
        printf("EROARE - NU SE ALOCA LINIILE! \n");
        exit(1);
    }

    for(int i=0; i<N; i++)
    {
        matrice[i] = (char*) malloc(M * sizeof(char)); //pt elem pe linie
        if(matrice[i] == NULL)
        {
            printf("ERAORE - NU SE ALOCA PT COLOANA %d! \n", i);
            return (1);
        }
    }

    return matrice;
}



char **citire(const char *fisier, int *T, int *N, int *M, int *K)
{
    FILE *in = fopen(fisier, "r");
    if(in == NULL)
    {
        printf("EROARE - NU S A DESCHIS FISIERUL INTRARE \n");
        exit(1);
    }
    fscanf(in, "%d %d %d %d", T, N, M, K);
    char** matrice = alocare(*N, *M);

    for(int i=0; i< (*N); i++)
    {
        fgets(in, "%s", (*matrice)[i]);
    }

    fclose(in);
    return matrice;
}



int numarare(char** matrice, int N, int M, int x, int y)
{
    int nr=0;                                                  // c(-1,-1)   c( 0,-1)   c( 1,-1)  
    const int coordX[8] = {-1,  0,  1, -1, 1, -1, 0, 1};       // c(-1, 0)   C( 0, 0)   c( 1, 0)   fara C(0,0)
    const int coordY[8] = {-1, -1, -1,  0, 0,  1, 1, 1};       // c(-1, 1)   c( 0, 1)   c( 1, 1)
    
    for(int i=0; i<8; i++)
    {
        int xvec = x + coordX[i];
        int yvec = y + coordY[i];

        if(xvec >= 0 && yvec >= 0 && xvec < N && yvec < M && matrice[xvec][yvec] == 'X')
            nr++;
    }

    return nr;
}



void eliberare(char** matrice, int N)
{
    for(int i=0; i<N; i++)
        free(matrice [i]);
    
    free(matrice);
}



int schimbare(char** matrice, int N, int M)
{
    int nr=0;
    char** next = alocare(N,M);
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            nr = (numarare(matrice, N, M, i, j));

            if(matrice[i][j] == 'X')
            {
                if(nr < 2 || nr > 3)
                    next[i][j] = '+';  
                else
                    next[i][j] = 'X';  
            }
            
            else
            {
                if(nr == 3)
                    next[i][j] = 'X';
                else
                    next[i][j] = '+';
            }



        }
    }


    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            matrice[i][j] = next[i][j];
        }
    }

    eliberare(next, N);
}



void afisare(const char *fisier, char** matrice, int N)
{
    FILE *out = fopen(fisier, "a");
    if(out == NULL)
    {
        printf("EROARE - NU S A DESCHIS FISIERUL IESIRE \n");
        exit(1);
    }    

    for(int i=0; i<N; i++)
    {
        fprintf(out, "%s\n", matrice[i]);
    }
    fprintf(out, "\n");

    fclose(out);
}