/*
 Escrever uma função em C que, dada uma árvore binária qualquer, retorne,
 num vetor, todos os elementos maiores que N. A função deve ter o
 seguinte protótipo: int* mN(TAB*a, int N, int *tam);
*/

#include "TABB.c"

int tamanhoofc(TABB*a, int x){
    if (!a) return 0;
    if (a->info > x) return (tamanhoofc(a->esq,x) + tamanhoofc(a->dir,x) + 1);
    else return (tamanhoofc(a->esq,x) + tamanhoofc(a->dir,x));
}

int *percorre(TABB*a, int*vet,int x, int *ind){
    if (!a) return vet;
    if (a->info > x) vet[(*ind)++] = a->info;
    vet = percorre(a->esq,vet,x,ind);
    vet = percorre(a->dir,vet,x,ind);
    return vet;
}

int* mN(TABB*a, int N, int *tam){
    *tam = tamanhoofc(a,N);
    int y = 0;
    int *vet = (int*)malloc(sizeof(int)*(*tam));
    vet = percorre(a,vet,N,&y);
    return vet;
}

int main(){
    int opcao, x,ma, *resp, tam;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Vetor de valores maiores que n\n");
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
                printf("\tDigite o valor de N: ");
                scanf("%d",&ma);
                printf("\n");
                resp = mN(raiz,ma,&tam);
                printf("\tAqui esta o vetor com valores menores que N: ");
                for(int i = 0; i < tam; i++) printf("%d ", resp[i]);
                free(resp);
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    return 0;
}