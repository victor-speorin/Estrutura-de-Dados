/*
Escreva uma função que retorne o elemento menor ou igual (floor) que um de referência
x em uma ABB.
*/
#include "TABB.c"

TABB* aux(TABB* a, int x, TABB* resp) {
    if (!a) return resp;
    if (a->info == x) return a;
    else if (a->info < x) {
        resp = a;
        return aux(a->dir, x, resp);
    } else return aux(a->esq, x, resp);
}

TABB* menor(TABB* a, int x) {
    return aux(a, x, NULL);
}

int main(){
    int opcao, x, y;
    TABB* raiz = NULL, *resp = NULL;
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
                resp = menor(raiz,y);
                if (resp) printf("\to menor ao k eh: %d", resp->info);
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
