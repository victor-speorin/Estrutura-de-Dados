//Percorra uma TABB e retorne um vetor contendo os valores menores que n.

#include"TABB.c"

int *percorre(TABB*a, int *vet, int x, int *ind){
    if (!a) return vet;
    vet = percorre(a->esq,vet,x,ind);
    if (a->info < x) vet[(*ind)++] = a->info;
    vet = percorre(a->dir,vet,x,ind);
    return vet;
}

int percorre2(TABB*a, int x, int c){
    if (!a) return 0;
    if(a->info<x) return percorre2(a->esq,x,c) + percorre2(a->dir,x,c) + 1;
    else return percorre2(a->esq,x,c) + percorre2(a->dir,x,c);
}

int* mn(TABB* a, int n){
    int x = percorre2(a,n,0), ind = 0;
    int *vet = (int*) malloc(sizeof(int)*x);
    vet = percorre(a,vet,n,&ind);
    for (int i=0;i<x;i++) printf("%d ",vet[i]);
    return vet;
}

int main(){
    int opcao, x,ma;
    TABB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Vetor de valores menores que n\n");
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
                printf("\n\tDigite o valor de n: ");
                scanf("%d", &ma);
                printf("\n");
                int * resp;
                resp = mn(raiz,ma);
                if(resp) printf("\n\tOK!");
                else printf("\n\tDeu ruim!");
                printf("\n");
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