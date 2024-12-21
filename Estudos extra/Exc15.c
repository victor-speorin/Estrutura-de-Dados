/*
Escreva uma função que retorne o elemento menor ou igual (floor) que um de referência
x em uma ABB.
*/
#include "TABB.c"

TABB* aux(TABB*og, TABB*resp, int x, int ref){
    if (!og) return resp;
    if (x-og->info < ref && x-og->info > 0) {
        ref = x - og->info;
        resp = og;
        if (og->info > x) return aux(og->esq,resp,x,ref);
        else return aux(og->dir,resp,x,ref);
    }
    else{
        if (og->info > x) return aux(og->esq,resp,x,ref);
        else return aux(og->dir,resp,x,ref);
    }
}

TABB* menor(TABB*a, int x){
    if (!a) return NULL;
    if (TABB_busca(a,x)) return TABB_busca(a,x);
    int ref;
    if (x - a->info > 0) ref = x - a->info;
    else {
        while(x - a->info < 0) a = a->esq;
        ref = x - a->info;
    }
    return aux(a,a,x,ref);
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
