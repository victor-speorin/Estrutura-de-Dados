/*
 Retornar todos os ancestrais de um nó na árvore
 de busca binária, da raiz da árvore até o elemento
 passado como parâmetro, usando a biblioteca de
 lista encadeada - TLSE* ancestrais(TABB *a, int elem);
*/
#include "TABB.c"
#include "TLSE.c"
TLSE* ancestrais2(TABB *a, int elem, TLSE *l){
    if (a->info == elem) return l;
    if (a->info > elem){
        l = TLSE_ins_ini(l,a->info);
        l = ancestrais2(a->esq,elem,l);
    }
    else {
        l = TLSE_ins_ini(l,a->info);
        l = ancestrais2(a->dir,elem,l);
    }
    return l;
}

TLSE* ancestrais(TABB *a, int elem){
    TLSE *l = NULL;
    l = ancestrais2(a,elem,l);
    return l;
}

int main(){
    int opcao, x;
    TABB* raiz = NULL;
    TLSE *l = NULL;
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
                printf("digite o n: \n");
                scanf("%d",&x);
                l = ancestrais(raiz,x);
                TLSE_imp_rec_rev(l);
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    TLSE_lib_rec(l);
    return 0;
}