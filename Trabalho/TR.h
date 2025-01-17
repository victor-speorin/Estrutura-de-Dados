#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_T 50

typedef struct tiporesidencia{
    long int id;
    char bairro[30];
    char tipo[30];
    char rua[50];
    int numero;
    double preco_total;
    double preco_m2;
    char descricao[2500];
    int cep;
    char latitude[20];
    char longitude[20];
}TR;

typedef struct listatr{
    TR *info;
    struct listatr *prox;
}TLSE_TR;

typedef struct arvbm{
    int folha;
    int nchaves;
    char prox[30];
    TR chaves[(2 * MAX_T) - 1];
    char filhos[2 * MAX_T][30];
}TABM;

void substituir_virgula_por_ponto(char *str);

void funcauxbusca(char *raiz, long int id, int t);

void TABM_libera(TABM *a);

void TABM_escreve(char* arquivo, TABM* no, int t);

void TABMtoTABM(TABM *origem, TABM *destino, int t);

TABM *TABM_cria_no(int t);

void TABM_cria(int t, char **arq, int *c);


TABM *arq2TABM(char *arq, int t);

TR TRtoTR(TR aux, TR T) ;

void TABM_imprime_chaves(char *raiz, int t);

char *TABM_busca(char *arq, long id, int t);

void copia_no(TABM *x, char *arq, int t);

TABM *divisao(TABM *x, int i, TABM *y, int t, int *cont);

TABM *insere_nao_completo(TABM *x, TR *r, int t, int *cont);


char* TABM_insere(TR *residencia, int t, char **raiz, int *cont);

TLSE_TR *TLSE_TR_insere(TLSE_TR *l, TR *r);

TLSE_TR *ledados(char *arq, TLSE_TR *l);

void TLSE_TR_imprime(TLSE_TR *l);

void TLSE_TR_libera(TLSE_TR *l);

char *remocao(char *no, long id, int t);

void le_dados(char * arquivo, char ** raiz, int t, int* cont);

void imp(char *raiz, int andar, int t);

void TABM_imprime(char **raiz, int t);

void contachaves(char *arq, int t);

void le_dados(char * arquivo, char ** raiz, int t, int* cont);

void TABM_imprime(char** raiz,int t);

void contachaves(char *arq, int t);

void procuraqto (long int id,int t,char *arq);

void retornaBAIRRO(char *bairro, int t, char *arq);

void retornaCEP(int cep, int t, char *arq);

// Retorna todas residências de mesma latitude
void retornaLAT(char *latitude, int t, char *arq);

// Retorna todas residências de mesma longitude
void retornaLO(char *longitude, int t, char *arq);

// Retorna todas residências situadas no mesmo bairro
void retornaBAIRRO(char *bairro, int t, char *arq);

// Retorna todas residências de mesmo tipo
void retornaTIPO(int tipo, int t, char **arq);

// Retorna todas residências com mesma quantidade de metros quadrados
void retornaM2(double m2, int t, char *arq);

// Retorna todas residências na mesma rua
void retornaRUA(char *rua, int t, char *arq);

// Remove todos imoveis dentro de uma faixa de preço
void removeImoveisPorPreco(double precoMin, double precoMax, int t, char *arq);

// Alterando preço por m2
void alteraPrecoPorM2(long int id, double novoPrecoM2, int t, char *arq);
// Alterando descrições
void alteraDescricao(long int id, char *novaDescricao, int t, char *arq);


void retiraPorTipo(char *tipo, int t, char *arq);


void retiraPorCEP(int cep, int t, char *arq);


void retiraPorRua(char *rua, int t, char *arq);

void retiraPorLatitude(char *latitude, int t, char *arq);

void retiraPorLongitude(char *longitude, int t, char *arq);


void retiraPorBairro(char *bairro, int t, char *arq);

void procuraqto (long int id,int t,char *arq);

void procuravenda (int t,char *arq);