#include <stdio.h>
#include "functiigof.h"

int main(int argc, char* argv[])
{
    
    int T, N, M, K;
    char **matrice = citire(argv[1], &T, &N, &M, &K);
    

//              TASK 1

if(T == 1)
{
    afisareinit(argv[2], matrice, N);


    for(int i=0; i<K; i++)
    {
        schimbare(matrice, N, M);
        afisare(argv[2], matrice, N);
    }

    eliberare(matrice, N);
}

//              TASK 1 end


//              TASK 2 (e facut cu COADA de liste, NU STIVA de liste)
    
 else if(T == 2)
{
    for(int i=0; i<K; i++)
    {
        schimbare2(argv[2], matrice, N, M, i+1);
    }

    eliberare(matrice, N);
}

//              TASK 2 end

//              TASK 3

else if(T < 5)
{

    Arbore* arbore = creare(matrice, N, M, 0, K);
    afisare3pre(argv[2], arbore, matrice, N, M);
    eliberareArbore(arbore);
    eliberare(matrice, N);
}

//              TASK 3 END


}