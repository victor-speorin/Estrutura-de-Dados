/*
maior elemento da árvore: TARVB* maior(TARVB *a);
*/
#include "TARVBM.c"

int maior(TARVBM *a){
    while (a->filho[a->nchaves]) a = a->filho[a->nchaves];
    return a->chave[a->nchaves-1];
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
    printf("%d", maior(arvore));
    TARVBM_libera(arvore);
    return 0;
}
