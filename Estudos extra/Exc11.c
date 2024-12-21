//Testar se duas árvores possuem as mesmas informações - int mi(TAB*a1,TAB*a2).
#include "TABB.c"

int mi(TABB*a1,TABB*a2){
    if (!a1 || !a2) return 1;
    int x = a1->info;
    if(!(TABB_busca(a2,x))) return 0;
    return (mi(a1->esq,a2) && mi(a1->dir,a2));
}

int main(void){
    int opcao, x, y;
    TABB* raiz1 = NULL, *raiz2 = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Verificar se sao iguais\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\t em qual arvore esta inserindo: ");
                scanf("%d", &y);
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf("%d", &x);
                if (y == 1) raiz1 = TABB_insere(raiz1,x);
                else raiz2 = TABB_insere(raiz2,x);
                break;

            case 2:
                printf("\tA arvore 1 eh: ");
                TABB_imp_ident(raiz1);
                printf("\n\n");
                printf("\tA arvore 2 eh : ");
                TABB_imp_ident(raiz2);
                printf("\n");
                break;

            case 3:
                x = mi(raiz1,raiz2);
                if(!x) printf("\n\tNAO sao iguais");
                else printf("\n\tiguais");
                printf("\n");
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz1);
    TABB_libera(raiz2);
    return 0;
}