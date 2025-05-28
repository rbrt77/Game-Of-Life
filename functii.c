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
            return NULL; 
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
    fscanf(in, "%d%d%d%d", T, N, M, K); 
    fscanf(in,"%*c");
    char** matrice = alocare(*N, *M);

    for(int i=0; i< (*N); i++)
    {
        fgets(matrice[i], sizeof(matrice[i])*(*M),in );
        matrice[i][strcspn(matrice[i], "\r\n")] = 0; 
        // matrice[i][strlen(matrice[i]) - 1] = 0
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



void schimbare(char** matrice, int N, int M)
{
    int nr;
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


void afisareinit(const char *fisier, char** matrice, int N)
{
    FILE *out = fopen(fisier, "w");
    if(out == NULL)
    {
        printf("EROARE - NU S A DESCHIS FISIERUL IESIRE INCEPUT \n");
        exit(1);
    }    

    for(int i=0; i<N; i++)
    {
        fprintf(out, "%s\n", matrice[i]);
    }
    fprintf(out, "\n");

    fclose(out);
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


            //task 2

Queue* createQueue() 
{
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL) 
        return NULL;
    q->front = q->rear = NULL;
    return q;
}



void enQueue(Queue* q, int x, int y) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->valX = x;
    newNode->valY = y;
    newNode->next = NULL;

    // nodurile noi se adauga la finalul cozii
    // daca nu exista niciun nod in coada
    if (q->rear == NULL) 
        q->rear = newNode;
    else {
        newNode -> prev = q -> rear;
        (q->rear)->next = newNode;
        q->rear = newNode;
    }

    // daca exista un singur element in coada
    if (q->front == NULL) 
        q->front = q->rear;
}


int deQueue(Queue* q, int* x, int* y) {
    Node* aux;

    // dacă coada este goală, se returnează NULL
    if(isEmpty(q))
        return 0;

    aux = q->front;
    *x = aux->valX;
    *y = aux->valY;
    q->front = (q->front)->next;

    // dacă coada devine goală după eliminare
    if (q->front == NULL)
        q->rear = NULL;
    else
        q->front->prev = NULL;

    free(aux);
    return 1;   //caz bun
}




// Verifică dacă coada este goală
int isEmpty(const Queue* q) {
    return (q->front == NULL);
}

// Șterge întreaga coadă și eliberează memoria
void deleteQueue(Queue* q) {
    
    while (!isEmpty(q)) 
    {
        Node* aux;
        aux = q->front;
        q->front = q->front->next;
        // printf("%d", aux->val); // pentru afișarea valorii nodului șters
        free(aux);
    }
    free(q); // eliberare memorie pentru structura cozii
}






void schimbare2(const char *fisier, char** matrice, int N, int M, int gen)
{
    int nr;
    char** next = alocare(N,M);

    Queue* q;
    q = createQueue();

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            nr = (numarare(matrice, N, M, i, j));

            if(matrice[i][j] == 'X')
            {
                if(nr < 2 || nr > 3)
                {
                    enQueue(q, i, j); 
                    next[i][j] = '+';  
                }
                else
                    next[i][j] = 'X'; 
                    
            }
            
            else
            {
                if(nr == 3)
                {
                    enQueue(q, i, j);
                    next[i][j] = 'X';
                }
                else
                    next[i][j] = '+';
            }
        }
    }

    //afisare prin parc si elim
    
    if(gen==1)                                //initiala
    {
        FILE *out = fopen(fisier, "w");         
        if(out == NULL)
        {
            printf("EROARE - NU S A DESCHIS FISIERUL IESIRE INITIAL \n");
            exit(1);
        }    
    
        fprintf(out, "%d", gen);

        int coordx, coordy;
        while (deQueue(q, &coordx, &coordy)) 
        {
            fprintf(out, " %d %d", coordx, coordy);
        } 
        
        if(!deQueue(q, &coordx, &coordy))
        {
            deleteQueue(q);    
        }
    
        fprintf(out, "\n");
    
    
        fclose(out);
    
    
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<M; j++)
            {
                matrice[i][j] = next[i][j];
            }
        }
    
        eliberare(next, N);
    }



    else
    {
        FILE *out = fopen(fisier, "a");         //dupa gen 1
        if(out == NULL)
        {
            printf("EROARE - NU S A DESCHIS FISIERUL IESIRE \n");
            exit(1);
        }   
    
        fprintf(out, "%d",gen);

        int coordx, coordy;
        while (deQueue(q, &coordx, &coordy)) 
        {
            fprintf(out, " %d %d", coordx, coordy);
        } 
        
        if(!deQueue(q, &coordx, &coordy))
        {
            deleteQueue(q);    
        }
    
        fprintf(out, "\n");
    
    
        fclose(out);
    
    
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<M; j++)
            {
                matrice[i][j] = next[i][j];
            }
        }
    
        eliberare(next, N);
    }
}



    //      TASK 3

void schimbare3st(char** matrice, int N, int M, Queue* schimbat)
{
    int nr;
    char** next = alocare(N,M);


    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            nr = (numarare(matrice, N, M, i, j));
                if(nr == 2)
                    next[i][j] = 'X';
                else
                    next[i][j] = matrice[i][j];

                if (next[i][j] != matrice[i][j])
                    enQueue(schimbat, i, j);
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

void schimbare3dr(char** matrice, int N, int M, Queue* schimbat)
{
   
    char** next = alocare(N,M);


    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            int nr = (numarare(matrice, N, M, i, j));

            if(matrice[i][j] == 'X')
            {
                if(nr < 2 || nr > 3)
                {
                    enQueue(schimbat, i, j); 
                    next[i][j] = '+';  
                }
                else
                    next[i][j] = 'X'; 
                    
            }
            
            else
            {
                if(nr == 3)
                {
                    enQueue(schimbat, i, j);
                    next[i][j] = 'X';
                }
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


Arbore* creare(char** matrice, int N, int M, int gen, int genmax)
{
    if(gen > genmax)
        return NULL;

    Arbore* nod = (Arbore*)malloc(sizeof(Arbore));
       
    nod->modificari = createQueue();    // goala inc

    if (gen == 0) 
    {

        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < M; j++) 
            {
                if (matrice[i][j] == 'X') 
                    enQueue(nod->modificari, i, j); 

            }
        }
    } 

    else
    {
        char** matraux = alocare(N, M);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                matraux[i][j] = matrice[i][j];

        // sch st pe matrice init
        schimbare3st(matrice, N, M, nod->modificari);
    
        //pt fiu stamga
        nod->left = creare(matrice, N, M, gen+1, genmax);
        eliberare(matraux, N);
    }

    if (gen == 0)
    nod->left = creare(matrice, N, M, gen + 1, genmax);  // doar dacă e gen 0

    char** matraux2 = alocare(N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matraux2[i][j] = matrice[i][j];

    Queue* schdr = createQueue();
    schimbare3dr(matraux2, N, M, schdr);

    nod->right = creare(matraux2, N, M, gen + 1, genmax);

    eliberare(matraux2, N);
    deleteQueue(schdr);

    return nod;

}



void afisare3pre(const char *fisier, Arbore* nod, char** matrice, int N, int M) 
{
    if (nod == NULL) 
        return;

    char** aux = alocare(N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            aux[i][j] = matrice[i][j];


    Node* modif = nod->modificari->front;
    while (modif) {
        int x = modif->valX;
        int y = modif->valY; 


        if (aux[x][y] == 'X')
            aux[x][y] = '+';
        else
            aux[x][y] = 'X';

        modif = modif->next;
    }
 
    FILE *out = fopen(fisier, "a");
    if(out == NULL)
    {
        printf("EROARE - NU S A DESCHIS FISIERUL IESIRE \n");
        exit(1);
    }    

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++)
            fprintf(out, "%c", aux[i][j]);
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
    fclose(out);

    afisare3pre(out, nod->left, aux, N, M);
    afisare3pre(out, nod->right, aux, N, M);

    eliberare(aux, N);  
}

// void preorder(Node* root) {
//     if (root) {
//         printf("%d ", root->val);     // 1. Procesează rădăcina
//         preorder(root->left);         // 2. Parcurge subarborele stâng
//         preorder(root->right);        // 3. Parcurge subarborele drept
//     }
// }

void eliberareArbore(Arbore* nod) 
{
    if (nod == NULL)
        return;

    eliberareArbore(nod->left);  
    eliberareArbore(nod->right); 

    deleteQueue(nod->modificari); 
    free(nod);  
}
 