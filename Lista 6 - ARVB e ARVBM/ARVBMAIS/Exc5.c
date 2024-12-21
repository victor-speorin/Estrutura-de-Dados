/*
função em C que, dada uma árvore qualquer, retire todos os elementos pares da
árvore original. A função deve ter o seguinte protótipo: TARVB* retira_pares
(TARVB* arv);
*/
#include "TARVBM.c"
#include "TLSE.c"
TLSE *achapar(TARVBM*a, TLSE*l){
    while (a){
        for(int i=0;i<a->nchaves;i++){
            if (!(a->chave[i]%2)) l = TLSE_ins_fim(l,a->chave[i]);
        }
        a=a->prox;
    }
    return l;
}
TARVBM* retira_pares (TARVBM* arv, int t){
    if (!arv) return NULL;
    TARVBM *aux = arv;
    TLSE *l = NULL;
    while (aux->filho[0]) aux = aux->filho[0];
    l = achapar(aux,l);
    TLSE_imp_rec_rev(l);
    while(l){
        arv = TARVBM_retira(arv,l->info,t);
        l=l->prox;
    }
    TLSE_lib_rec(l);
    return arv;
}
int main(){
    TARVBM *arvore = TARVBM_inicializa();
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
            arvore = TARVBM_retira(arvore, from, t);
            TARVBM_imprime(arvore);
            printf("\n\n");
            TARVBM_imprime_chaves(arvore);

        }
        else if(num == -1){
            printf("\n");
            TARVBM_imprime(arvore);
            printf("\n\n");
            TARVBM_imprime_chaves(arvore);
        }
        else if(!num){
            printf("\n");
            TARVBM_imprime(arvore);
            printf("\n\n");
            TARVBM_imprime_chaves(arvore);
        }
        else arvore = TARVBM_insere(arvore, num, t);
        printf("\n\n");
    }
    arvore = retira_pares(arvore,t);
    TARVBM_imprime(arvore);
    TARVBM_libera(arvore);
    return 0;
}
