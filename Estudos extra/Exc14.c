/*
 Escreva uma função não recursiva que retorne o k-ésimo menor valor de uma árvore
 binária de busca.
*/
#include "TABB.c"
TABB *kmenor(TABB*a,int k){
    if(!a) return NULL;
    TABB*b = a;
    k-=1;
    while (k){
        while(a->esq) a = a->esq;
        k--;
        b = TABB_retira(b,a->info);
        a=b;
    }
    while(a->esq) a = a->esq;
    return a;
}
int main(void){
    int opcao, x, y;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - kesimo\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao){
            case 1:
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf("%d", &x);
                printf("\n");
                raiz = TABB_insere(raiz, x);
                break;
            case 2:
                printf("\tA arvore eh: ");
                TABB_imp_ident(raiz);
                printf("\n");
                break;
            case 3:
                printf("\tdigite o k:");
                scanf("%d",&y);
                raiz = kmenor(raiz,y);
                if (raiz) printf("\to kesimo menor eh: %d", raiz->info);
                else printf("ruim");
                break;
            default:
                if(opcao != 0)
                    printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    return 0;
}
