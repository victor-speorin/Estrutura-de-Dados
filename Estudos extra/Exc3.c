/*
Retornar um vetor entre dois numeros (M e N), de uma ABB
Sendo este vetor, ordenado, sem metodos de ordenacao disponiveis
(nao pode usar, ou implementar o proprio).
*/

#include "TABB.c"

int tamanho(TABB *a){
    if (!a) return 0;
    return tamanho(a->esq) + tamanho(a->dir) + 1;
}

int *percorre(TABB *a, int *vet, int *ind){
    if (!a) return vet;
    vet = percorre(a->esq, vet, ind);
    vet[(*ind)++] = a->info;
    vet = percorre(a->dir, vet, ind);
    return vet;
}

int* vet_mn(TABB *a, int m, int n, int *qtd){
    int x = tamanho(a), indice = 0;
    int *vet = (int*) malloc(sizeof(int) * x);
    int *vetresp;
    vet = percorre(a, vet, &indice);
    *qtd = 0;
    for (int i = 0; i < x; i++) {
        if (vet[i] > m && vet[i] < n) (*qtd)++;
    }
    vetresp = (int*) malloc(sizeof(int) * (*qtd));
    int j = 0;
    for (int i = 0; i < x; i++) {
        if (vet[i] > m && vet[i] < n) {
            vetresp[j++] = vet[i];
        }
    }
    free(vet);
    return vetresp;
}

int main(void){
    int opcao, x, na, ma, m, *resp;
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
                raiz = TABB_insere(raiz, x);
                break;
            case 2:
                printf("\tA arvore eh: ");
                TABB_imp_ident(raiz);
                printf("\n");
                break;
            case 3:
                printf("\n\tDigite o valor do limite inferior: ");
                scanf("%d", &ma);
                printf("\n");
                printf("\n\tDigite o valor do limite superior: ");
                scanf("%d", &na);
                printf("\n");
                m = 0;
                resp = vet_mn(raiz, ma, na, &m);
                printf("\n\tO vetor dos valores maiores que m e menores que n eh: \n");
                for(int i = 0; i < m; i++)
                    printf("\tElemento %d: %d\n", i, resp[i]);
                printf("\n");
                free(resp);
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
