//Retorne todos os elementos de TABB em um vetor,
// ordenado, sem usar metodos de ordenação ou estruturas auxiliares.

#include "TABB.c"

int tamanho(TABB*a, int x){
    if (!a) return x;
    else x+=1;
    if (a->esq) x=tamanho(a->esq,x);
    if (a->dir) x= tamanho(a->dir,x);
    return x;
}

int *percorre(TABB*a, int* indice, int* vet){
    if (!a) return vet;
    vet = percorre(a->esq,indice,vet);
    vet[(*indice)++] = a->info;
    vet = percorre(a->dir,indice,vet);
    return vet;
}

int* TAB2vet(TABB* a){
    int n = tamanho(a,0), indice = 0;
    int *vet = (int*) malloc(sizeof(int)*n);
    vet = percorre(a,&indice,vet);
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