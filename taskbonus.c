#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functiigof.h"



        // alocare copiata functii.c 
char** alocare(int N, int M) 
{
    char** matrice = (char**) malloc(N * sizeof(char*));
    for (int i = 0; i < N; i++) 
        matrice[i] = (char*) malloc(M * sizeof(char));
    return matrice;
}



Stack* citireBonus(const char* fisier, int* T, int* N, int* M, int* K, char*** matriceFinala) 
{
   
    FILE* bonusinput = fopen(fisier, "r");
    if (!bonusinput) 
    {
        printf("Eroare la deschiderea fișierului.\n");
        exit(1);
    }

    fscanf(bonusinput, "%d%d%d%d", T, N, M, K);
    Stack* stiva = NULL;

    for (int gen = 0; gen < *K; gen++) 
    {
        int nr;
        fscanf(bonusinput, "%d", &nr);
        NodeS* head = NULL;
        for (int i = 0; i < nr; i++) 
        {
            int x, y;
            fscanf(bonusinput, " (%d,%d)", &x, &y);     //citeste dorect NR (coor,coord) cu tot cu spatiu
            NodeS* nodnou = (NodeS*) malloc(sizeof(NodeS));
            nodnou->valX = x;
            nodnou->valY = y;
            nodnou->next = head;
            head = nodnou;
        }

        Stack* nodStiva = (Stack*) malloc(sizeof(Stack));
        nodStiva->front = head;
        nodStiva->next = stiva;
        stiva = nodStiva;
    }

    *matriceFinala = alocare(*N, *M);
    fscanf(bonusinput, "%*c");      //pt enetr ignora
    for (int i = 0; i < *N; i++) 
    {
        fgets((*matriceFinala)[i], *M + 2, bonusinput);
        (*matriceFinala)[i][strcspn((*matriceFinala)[i], "\r\n")] = 0;
    }

    fclose(bonusinput);
    return stiva;
}


void sch(NodeS* head, char** matrice) 
{
    while (head) 
    {
        int x = head->valX;
        int y = head->valY;
        if (matrice[x][y] == 'X') 
            matrice[x][y] = '+';
        else 
            matrice[x][y] = 'X';
        head = head->next;
    }
}


void afisare(const char* numeFisier, char** matrice, int N)
{
    FILE* bonusout = fopen(numeFisier, "w");
    for (int i = 0; i < N; i++) 
    {
        fprintf(bonusout, "%s\n", matrice[i]);
    }
    fclose(bonusout);
}


void eliberaremat(char** matrice, int N) 
{
    for (int i = 0; i < N; i++)
        free(matrice[i]);
    free(matrice);
}


void eliberarest(Stack* stiva) 
{
    while (stiva) 
    {
        NodeS* head = stiva->front;
        while (head) 
        {
            NodeS* temp = head;
            head = head->next;
            free(temp);
        }
        Stack* tempStiva = stiva;
        stiva = stiva->next;
        free(tempStiva);
    }
}


int main(int argc, char* argv[]) 
{

    int T, N, M, K;
    char** matriceFinala;
    Stack* stiva = citireBonus(argv[1], &T, &N, &M, &K, &matriceFinala);

    Stack* p = stiva;
    while (p) {
        sch(p->front, matriceFinala);
        p = p->next;
    }

    afisare(argv[2], matriceFinala, N);
    eliberaremat(matriceFinala, N);
    eliberarest(stiva);

    return 0;
}
