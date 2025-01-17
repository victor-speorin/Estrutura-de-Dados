/*
 Retornar todas as informações ancestrais de um nó na
 árvore B, da raiz da árvore até o elemento passado como parâmetro,
 usando a biblioteca de lista encadeada -
 TLSEINT* misc(TARVB *a, int elem), onde:

typedef struct lseint{
  int lim_inf, lim_sup;
  struct lseint *prox;
} TLSEINT;

*/
#include "TARVB.c"
#include "TLSEINT.c"
#include "limits.h"

TLSEINT *percorre(TARVB*a,int x, TLSEINT*l){
    if (!a) return l;
    for (int i=0;i<=a->nchaves;i++){
        if (a->chave[i]==x){
            if (i > 0 && i < a->nchaves) l = TLSEINT_insere(l,a->chave[i-1],a->chave[i+1]);
            else if (i==0) l = TLSEINT_insere(l,INT_MIN,INT_MAX);
            else if (i == a->nchaves) l = TLSEINT_insere(l,a->chave[i-1],INT_MAX);
            return l;
        }
        else if (a->chave[i] > x || i == a->nchaves){
            if (i > 0 && i < a->nchaves) l = TLSEINT_insere(l,a->chave[i-1],a->chave[i]);
            else if (i==0) l = TLSEINT_insere(l,INT_MIN,a->chave[0]);
            else if (i == a->nchaves) l = TLSEINT_insere(l,a->chave[i-1],INT_MAX);
            return percorre(a->filho[i],x,l);
        }
    }
    return l;
}

TLSEINT *misc(TARVB *a, int elem){
    TLSEINT *l = NULL;
    return percorre(a,elem,l);
}
int main(){
    TARVB *arvore = TARVB_Inicializa();
    int t;
    printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
    scanf("%d", &t);
    if(t < 2) t = 2;
    int num = 0, from, to;
    while(num != -1){
        printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
        scanf("%d", &num);
        if(num == -9){
            scanf("%d", &from);
            arvore = TARVB_Retira(arvore, from, t);
            TARVB_Imprime2(arvore);
        }
        else if(num == -1){
            printf("\n");
            TARVB_Imprime2(arvore);
        }
        else if(!num){
            printf("\n");
            TARVB_Imprime2(arvore);
        }
        else arvore = TARVB_Insere(arvore, num, t);
        printf("\n\n");
    }
    int ele;
    printf("digite o elem: ");
    scanf("%d",&ele);
    TLSEINT *resp = misc(arvore,ele);
    if (resp) TLSEINT_imprime(resp);
    else printf("erro");
    TARVB_Libera(arvore);
    return 0;
}
