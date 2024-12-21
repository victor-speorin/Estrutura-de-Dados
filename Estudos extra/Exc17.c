/*
 Dada uma árvore binária de busca, escreva uma função que
 verifique se existe algum par de nós na árvore cuja soma de
 seus valores seja igual a um número S fornecido. int
 temPar(TABB* arv, int S).
*/
#include "TABB.c"

int temPar(TABB* arv, int S){
    if (!arv || !arv->esq || !arv->dir) return 0;
    if (arv->esq->info + arv->dir->info == S) return 1;
    return (temPar(arv->esq,S) || temPar(arv->dir,S));
}

int main(){
    int opcao, x, y;
    TABB* raiz = NULL, *resp = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - soma = s\n");
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
                printf("\tdigite o S:");
                scanf("%d",&y);
                if (temPar(raiz,y)) printf("\tsim!");
                else printf("\tnao");
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
