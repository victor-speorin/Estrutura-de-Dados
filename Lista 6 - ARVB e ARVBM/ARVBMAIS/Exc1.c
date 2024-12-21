/*
sucessor de um elemento na árvore. Se o elemento for o maior da estrutura, sua
função deve retornar INT_MAX: int suc (TARVB *a, int elem);
*/
#include "TARVBM.c"
int suc (TARVBM *a, int elem){
    a = TARVBM_busca(a,elem);
    for (int i=0;i<a->nchaves;i++){
        if (a->chave[i]==elem){
            if (i<a->nchaves-1) return a->chave[i+1];
            if (a->prox) return a->prox->chave[0];
            return INT_MAX;
        }
    }
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
    int elem;
    printf("insira o elem: ");
    scanf("%d",&elem);
    printf("%d", suc(arvore,elem));
    TARVBM_libera(arvore);
    return 0;
}
