#include "TABB.c"

TABB* maior(TABB *a){
    if (!a) return a;
    TABB *resp = a;
    while (resp->dir) {
        resp = resp->dir;
    }
    return resp;
}

int main(){
    int opcao, x;
    TABB* raiz = NULL;
    TABB* copy = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Achar o maior\n\t");
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
                copy = maior(raiz);
                printf("\n%d\n", copy->info);
                break;


            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    TABB_libera(copy);
    return 0;
}