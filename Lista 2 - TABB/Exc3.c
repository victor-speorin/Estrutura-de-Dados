#include "TABB.c"
#include "TLSE.c"

TLSE* achaimpar(TABB*a, TLSE*x){
    if (!a) return x;
    if (a->info%2) x = TLSE_ins_ini(x,a->info);
    x = achaimpar(a->esq,x);
    x = achaimpar(a->dir,x);
    return x;
}

TABB* retira_impares(TABB* a){
    TLSE *lista = NULL;
    lista = achaimpar(a,lista);
    while (lista){
        a=TABB_retira(a,lista->info);
        lista=lista->prox;
    }
    return a;
}

int main(){
    int opcao, x;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - retirar os impares\n\t");
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
                raiz = retira_impares(raiz);
                TABB_imp_ident(raiz);
                break;


            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    return 0;
}
