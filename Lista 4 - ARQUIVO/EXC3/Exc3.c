/*
Escreva um procedimento que receba o nome de um arquivo texto, cujo conteúdo são valores
inteiros e imprima na tela o número de vezes que cada elemento aparece e em quais linhas
void resumo(char *Arq).
*/
#include "stdio.h"
#include "stdlib.h"

typedef struct linhas{
    int id_linha;
    struct linhas *prox_linha;
}TL;

typedef struct info{
    int info;
    int qtd;
    TL *prim_linha;
    struct info *prox_info;
}TI;

void libera_linhas(TL* p){
    if(!p) return;
    libera_linhas(p->prox_linha);
    free(p);
}

void libera_elem(TI* l){
    if(!l) return;
    libera_linhas(l->prim_linha);
    libera_elem(l->prox_info);
    free(l);
}

void imp_linhas(TL* p){
    if(!p) return;
    printf("%d ",p->id_linha);
    imp_linhas(p->prox_linha);
}

void imp_elem(TI* l){
    if(!l) return;
    printf("O elemento %d apareceu %d vez(es) na(s) linha(s): ",l->info, l->qtd);
    imp_linhas(l->prim_linha);
    printf("\n");
    imp_elem(l->prox_info);
}

TI* busca_info(TI* g, int x){
    if((!g) || (g->info == x)) return g;
    return(busca_info(g->prox_info, x));
}

TL* insere_linha(TL* p, int linha){
    if(!p){
        TL* novo = (TL*)malloc(sizeof(TL));
        novo->id_linha = linha;
        novo->prox_linha = NULL;
        p = novo;
        return p;
    }
    p->prox_linha = insere_linha(p->prox_linha,linha);
    return p;
}

TI* insere_elem(TI *g, int x, int linha){
    TI *p = busca_info(g, x);
    if(!p){
        p = (TI*) malloc(sizeof(TI));
        p->info = x;
        p->prox_info = g;
        p->prim_linha = insere_linha(NULL,linha);
        p->qtd = 1;
        g = p;
    }
    return g;
}

void resumo(char *Arq){
    FILE *fp = fopen(Arq,"r");
    if (!fp) exit(1);
    TI *grafo = NULL;
    int linha = 1, x;
    int ver = fscanf(fp,"%d",&x);
    while (ver==1){
        if (!busca_info(grafo,x)) grafo = insere_elem(grafo,x,linha);
        else{
            TI *atual = busca_info(grafo,x);
            atual->qtd++;
            atual->prim_linha = insere_linha(atual->prim_linha,linha);
        }
        linha++;
        ver = fscanf(fp,"%d",&x);
    }
    imp_elem(grafo);
    libera_elem(grafo);
    fclose(fp);
}

int main(){
    resumo("Ex3");
    return 0;
}