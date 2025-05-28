#include <stdio.h>
#include <stdlib.h>

        //task1


char** alocare(int N, int M);

char** citire(const char *fisier, int *T, int *N, int *M, int *K);

int numarare(char** matrice, int N, int M, int x, int y);

void eliberare(char** matrice, int N);

void schimbare(char** matrice, int N, int M);

void afisare(const char *fisier, char** matrice, int N);

void afisareinit(const char *fisier, char** matrice, int N);


        //task2


struct Elem{
    int valX, valY;
    struct Elem *next, *prev;
};
typedef struct Elem Node;


struct Q{

    Node *front, *rear;
};

typedef struct Q Queue;

Queue* createQueue();

void enQueue(Queue* q, int x, int y);
int deQueue(Queue* q, int* x, int* y);

int isEmpty(const Queue* q);
void deleteQueue(Queue* q);

void schimbare2(const char *fisier, char** matrice, int N, int M, int gen);




    //task 3

struct T { 
	Queue* modificari;
	struct  T  *left,*right; 
}; 
typedef struct T Arbore;

void schimbare3st(char** matrice, int N, int M, Queue* schimbat);
void schimbare3dr(char** matrice, int N, int M, Queue* schimbat);
Arbore* creare(char** matrice, int N, int M, int gen, int genmax);
void afisare3pre(const char *fisier, Arbore* nod, char** matrice, int N, int M);
void eliberareArbore(Arbore* nod);



    //bonus

struct NodSt {
    int valX, valY;
    struct NodSt *next;
};
typedef struct NodSt NodeS;


struct S
{
    NodeS *front;
    struct S *next;
};
typedef struct S Stack; 
