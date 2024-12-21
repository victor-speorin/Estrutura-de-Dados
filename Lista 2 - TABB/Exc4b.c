#include "TABB.c"
int conta(TABB*a, int N, int c){
    if (!a) return c;
    if (a->info<N){
        c++;
    }
    c = conta(a->esq,N,c);
    c = conta(a->dir,N,c);
    return c;
}
int* conta2(TABB*a, int N, int *vet, int *ind){
    if (!a) return vet;
    if (a->info<N){
        vet[(*ind)++] = a->info;
    }
    vet = conta2(a->esq,N,vet,ind);
    vet = conta2(a->dir,N,vet,ind);
    return vet;
}

int* mN(TABB*a, int N){
    int x = conta(a,N,0);
    int *vetmig = (int*)malloc(sizeof(int)*x);
    int ind = 0;
    vetmig = conta2(a,N,vetmig,&ind);
    return vetmig;
}

int main(){
    int opcao, x, n, u;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - inserir o n colocar os menores num vetor:\n\t");
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
                raiz = TABB_insere(raiz, x);
                break;

            case 2:
                printf("\tA arvore eh: ");
                TABB_imp_ident(raiz);
                printf("\n");
                break;

            case 3:
                scanf("%d", &n);
                u = conta(raiz, n, 0);
                int *vet = mN(raiz, n);
                for (int i = 0; i < u; i++){
                    printf("%d ", vet[i]);
                }
                free(vet);
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    return 0;
}
