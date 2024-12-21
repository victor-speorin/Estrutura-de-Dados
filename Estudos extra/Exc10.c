//Verifique se uma TABB é AVL, 1 caso sim e 0 caso não.

#include"TABB.c"
int maior(int x, int y){
    if(x >= y) return x;
    return y;
}

int TABB_altura(TABB *a){
    if(!a) return -1;
    return maior(TABB_altura(a->esq), TABB_altura(a->dir)) + 1;
}

int FB (TABB*a){
    return (TABB_altura(a->esq) - TABB_altura(a->dir));
}

int ver_AVL(TABB*a){
    if (!a) return 1;
    if (FB(a) > 1 || FB(a) < -1) return 0;
    return (ver_AVL(a->esq) && ver_AVL(a->dir));
}

int main(void){
    int opcao, x;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Verificar se eh AVL\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
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
                x = ver_AVL(raiz);
                if(!x) printf("\n\tNAO eh AVL");
                else printf("\n\tEh AVL");
                printf("\n");
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    return 0;
}