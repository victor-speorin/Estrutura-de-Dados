//verificar se uma árvore é estritamente binária,
// isto é, os nós dessa árvore possuem ou zero ou dois filhos
#include "TABB.c"
int estbin(TABB *a){
    if (!a) return 1;
    if ((!a->esq && a->dir) || (a->esq && !a->dir)) return 0;
    return (estbin(a->esq) && estbin(a->dir));
}
int main(){
    int opcao, x;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Ver se eh estbin\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao){
            case 1:
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf("%d", &x);
                printf("\n");
                raiz = TABB_insere(raiz,x);
                break;

            case 2:
                printf("\tA arvore eh: ");
                TABB_imp_ident(raiz);
                printf("\n");
                break;

            case 3:
                x = estbin(raiz);
                if (x) printf("estbin");
                else printf("nao");
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    return 0;
}


