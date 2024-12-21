/*
maior elemento da árvore: TARVB* maior(TARVB *a)
*/
#include "TARVB.c"

int maior(TARVB *a){
    while (a->filho[a->nchaves]) a = a->filho[a->nchaves];
    return a->chave[a->nchaves-1];
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
    if (maior(arvore)) printf("o maior elem eh: %d", maior(arvore));
    else printf("erro");
    TARVB_Libera(arvore);
    return 0;
}
