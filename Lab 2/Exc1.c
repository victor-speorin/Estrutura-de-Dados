/*
Uma função em C que, dada uma árvore de busca binária qualquer,
retorne, numa lista, todos os elementos maiores que N. A função
deve ter o seguinte protótipo: TLSE* mN(TABB*a, int N);
*/
#include "TABB.c"
#include "TLSE.c"

TLSE* percore(TABB*a,int x, TLSE *l){
    if (!a) return l;
    if (a->esq) l = percore(a->esq,x,l);
    if (a->info > x) l = TLSE_ins_fim(l,a->info);
    if (a->dir) l = percore(a->dir,x,l);
    return l;
}

TLSE* mN(TABB*a, int N){
    if (!a) return NULL;
    TLSE *resp = NULL;
    resp = percore(a,N,resp);
    return resp;
}

int main(void){
    int opcao, x,y;
    TABB* raiz = NULL;
    TLSE* lista = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista com maiores\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf("%d", &x);
                raiz = TABB_insere(raiz,x);
                printf("\n");
                break;

            case 2:
                printf("\tA arvore eh: ");
                TABB_imp_ident(raiz);
                printf("\n");
                break;

            case 3:
                printf("\tdigite o N: ");
                scanf("%d",&y);
                lista = mN(raiz,y);
                if (lista) TLSE_imp_rec(lista);
                else printf("erro");
                printf("\n");
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    TLSE_libera(lista);
    return 0;
}