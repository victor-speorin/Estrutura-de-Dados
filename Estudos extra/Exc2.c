//Retorne todos os elementos de TAB em um vetor,
// ordenado, sem usar metodos de ordenação ou estruturas auxiliares.

#include "TABB.c"

int *coloca(TABB*a,int*vet,int n){
    TABB* b = a;
    int x = 0;
    do{
        a = b;
        if (a->esq) {
            while (a->esq) a = a->esq;
            vet[x] = a->info;
            b = TABB_retira(b, a->info);
            x++;
        }
        else {
            break;
        }
    } while (1);
    vet[x] = b->info;
    do{
        a = b;
        if (a->dir) {
            while (a->dir) a = a->dir;
            vet[n-1] = a->info;
            b = TABB_retira(b, a->info);
            n--;
        }
        else {
            break;
        }
    } while (1);
    return vet;
}

int tamanho(TABB*a, int x){
    if (!a) return x;
    else x+=1;
    if (a->esq) x=tamanho(a->esq,x);
    if (a->dir) x= tamanho(a->dir,x);
    return x;
}
int* TAB2vet(TABB* a){
    int n = tamanho(a,0);
    int *vet = (int*) malloc(sizeof(int)*n);
    vet = coloca(a,vet,n);
    return vet;
}


int main(){
    int opcao, x,n, *vet;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista ordenada\n");
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
                n = tamanho(raiz,0);
                vet = TAB2vet(raiz);
                for (int i=0;i<n;i++) printf("%d ",vet[i]);
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    free(vet);
    return 0;
}