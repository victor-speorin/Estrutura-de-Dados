/*
Retornar todas as informações ancestrais de um nó
na árvore binária, da raiz da árvore até o elemento
passado como parâmetro, usando a biblioteca de
lista encadeada - TLSEINT* misc(TAB *a, int elem), onde:
typedef struct lseint{
  int lim_inf, lim_sup;
  struct lseint *prox;
} TLSEINT;
* COM TAB *
*/

#include "TABB.c"
#include "TLSEINT.c"
#include "TLSE.c"
#include "limits.h"

TLSEINT* percorre(TABB *a, int x, TLSEINT* l){
    if (a->info == x || !a) return l;
    if (TABB_busca(a->esq,x)){
       if (a->info > x) l = TLSEINT_insere(l,INT_MIN,a->info);
       else  l = TLSEINT_insere(l,a->info,INT_MAX);
       l = percorre(a->esq,x,l);
    }
    else if (TABB_busca(a->dir,x)) {
        if (a->info > x) l = TLSEINT_insere(l, INT_MIN, a->info);
        else l = TLSEINT_insere(l, a->info, INT_MAX);
        l = percorre(a->dir, x, l);
    }
    return l;
}

TLSEINT* misc(TABB *a, int elem){
    if (!a) return NULL;
    TLSEINT *resp = TLSEINT_inicializa();
    resp = percorre(a,elem,resp);
    resp = TLSEINT_insere(resp,INT_MIN,INT_MAX);
    return resp;
}

int main(){
    int opcao, x,y;
    TABB* raiz = NULL;
    TLSEINT* lista = TLSEINT_inicializa();
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista com maiores\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf("%d", &x);
                raiz = TABB_insere(raiz,x);
                printf("\n");
                break;

            case 2:
                printf("\tA arvore eh: ");
                TABB_imp_ident(raiz);
                printf("\n");
                break;

            case 3:
                printf("\tdigite o no: ");
                scanf("%d",&y);
                if (!(TABB_busca(raiz,y))) printf("\tnao existe esse elemento!\n");
                else {
                    lista = misc(raiz,y);
                    TLSEINT_imprime(lista);
                }
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    TLSEINT_libera(lista);
    return 0;
}