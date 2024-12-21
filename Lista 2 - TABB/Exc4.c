#include "TABB.c"
#include "TLSE.c"
int conta(TABB*a, int N, int c, TLSE **y){
    if (!a) return c;
    if (a->info<N){
        c++;
        (*y) = TLSE_ins_fim((*y),a->info);
    }
    c = conta(a->esq,N,c,y);
    c = conta(a->dir,N,c,y);
    return c;
}

int* mN(TABB*a, int N){
    TLSE *l = NULL;
    int x = conta(a,N,0,&l);
    int *vet = (int*) malloc(sizeof(int)*x);
    while(x){
        TABB *oi =TABB_busca(a,l->info);
        vet[x-1] = oi->info;
        l=l->prox;
        x--;
    }
    return vet;
}

int main(){
    int opcao, x,n,u;
    TABB* raiz = NULL;
    TLSE *laux = NULL;
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
                raiz = TABB_insere(raiz,x);
                break;

            case 2:
                printf("\tA arvore eh: ");
                TABB_imp_ident(raiz);
                printf("\n");
                break;

            case 3:
                scanf("%d",&n);
                u = conta(raiz,n,0,&laux);
                int *vet = mN(raiz,n);
                printf("oi");
                for (int i=0;i<u;i++){
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
