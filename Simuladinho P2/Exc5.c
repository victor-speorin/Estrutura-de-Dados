/*

*/

#include "TARVB.c"
int *retorno(TARVB *a, int n, int m, int *vet, int *ind){
    if (!a) return vet;
    for (int i=0;i<=a->nchaves;i++){
        if (i==a->nchaves) vet = retorno(a->filho[i],n,m,vet,ind);
        else if (!(a->chave[i]%n) && !(a->chave[i]%m)){
            vet[(*ind)++] = a->chave[i];
            vet = retorno(a->filho[i],n,m,vet,ind);
        }
        else vet = retorno(a->filho[i],n,m,vet,ind);
    }
    return vet;
}

int tam(TARVB *a, int n, int m){
    if (!a) return 0;
    int cont = 0;
    for (int i=0;i<=a->nchaves;i++){
        if (i==a->nchaves) cont += tam(a->filho[i],n,m);
        else if (!(a->chave[i]%n) && !(a->chave[i]%m)){
            cont ++;
            cont += tam(a->filho[i],n,m);
        }
        else cont += tam(a->filho[i],n,m);
    }
    return cont;
}

int *mult_NM(TARVB *a, int n, int m, int *tam_vet){
    if (!a){
        *tam_vet = 0;
        return NULL;
    }
    int zero = 0;
    *tam_vet = tam(a,n,m);
    int *vet = (int*)malloc(sizeof(int) * (*tam_vet));
    vet = retorno(a,n,m,vet,&zero);
    return vet;
}

int main(int argc, char *argv[]){
    TARVB *arvore = TARVB_Inicializa();
    int t;
    printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
    scanf("%d", &t);
    if(t < 2) t = 2;
    int num = 0, from, to;
    while(num != -1){
        printf("Digite um numero para adicionar. 0 para imprimir. -9 para realizar a operacao e -1 para sair\n");
        scanf("%d", &num);
        if(num == -9){
            printf("Digite n e m... ");
            int n, m, tam_vet = 0, i;
            scanf("%d%d", &n, &m);
            int *vet = NULL;
            vet = mult_NM(arvore, n, m, &tam_vet);
            for(i = 0; i < tam_vet; i++) printf("vet[%d] = %d\n", i, vet[i]);
            free(vet);
        }
        else if(num == -1){
            printf("\n");
            TARVB_Imprime(arvore);
            TARVB_Libera(arvore);
            return 0;
        }
        else if(!num){
            printf("\n");
            TARVB_Imprime(arvore);
        }
        else arvore = TARVB_Insere(arvore, num, t);
        printf("\n\n");
    }
}