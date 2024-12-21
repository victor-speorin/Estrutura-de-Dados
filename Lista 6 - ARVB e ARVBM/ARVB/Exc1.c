/*
sucessor de um elemento na árvore. Se o elemento for o maior da estrutura, sua
função deve retornar INT_MAX: int suc (TARVB *a, int elem);
*/
#include "TARVB.c"

int percorre(TARVB *a, int elem,  int resp) {
    if (!a) return resp;
    for (int i = 0; i < a->nchaves; i++){
        if (a->chave[i] > elem && a->chave[i] < resp){
            resp = a->chave[i];
        }
    }
    for (int j = 0; j <= a->nchaves; j++) {
        if (a->filho[j]){
            resp = percorre(a->filho[j], elem, resp);
        }
    }
    return resp;
}

int suc(TARVB *a, int elem){
    if (!a) return 0;
    return percorre(a,elem,INT_MAX);
}

int main(){
    TARVB *arvore = TARVB_Inicializa();
    int t;
    printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
    scanf("%d", &t);
    if(t < 2) t = 2;
    int num = 0, from, to;
    while(num != -1){
        printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
        scanf("%d", &num);
        if(num == -9){
            scanf("%d", &from);
            arvore = TARVB_Retira(arvore, from, t);
            TARVB_Imprime2(arvore);
        }
        else if(num == -1){
            printf("\n");
            TARVB_Imprime2(arvore);
        }
        else if(!num){
            printf("\n");
            TARVB_Imprime2(arvore);
        }
        else arvore = TARVB_Insere(arvore, num, t);
        printf("\n\n");
    }
    int ele;
    printf("digite o elem: ");
    scanf("%d",&ele);
    if (suc(arvore,ele)) printf("%d", suc(arvore,ele));
    else printf("erro");
    TARVB_Libera(arvore);
    return 0;
}
