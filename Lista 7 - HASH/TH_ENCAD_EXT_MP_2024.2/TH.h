#include <stdio.h>
#include <stdlib.h>

#define TAM_VET 101

typedef struct aluno{
  int mat;
  float cr;
  struct aluno *prox;
}TA;

typedef TA* TH[TAM_VET];

int TH_hash(int mat, int n);
void TH_inicializa(TH tab, int n);
TA* TH_busca(TH tab, int n, int mat);
void TH_insere(TH tab, int n, int mat, float cr);
void TH_libera(TH tab, int n);
float TH_retira(TH tab, int n, int mat);
void TH_imprime(TH tab, int n);
