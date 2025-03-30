#include <stdio.h>
#include <stdlib.h>

char** alocare(int N, int M);

char** citire(const char *fisier, int *T, int *N, int *M, int *K);

int numarare(char** matrice, int N, int M, int x, int y);

void eliberare(char** matrice, int N);

int schimbare(char** matrice, int N, int M);

void afisare(const char *fisier, char** matrice, int N);