#include "TABB.c"

int temPar(TABB* arv, int S){
    if (!arv) return 0;
    if (TABB_busca(arv,S-arv->info)) return 1;
    return (temPar(arv->dir,S) || temPar(arv->esq,S));
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
