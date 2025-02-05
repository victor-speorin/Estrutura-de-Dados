/*
Dada uma Árvore B qualquer, retorne, numa lista, todos os
elementos menores que N. A função tem o seguinte protótipo:
TLSE* mN(TARVB *a, int N);
*/
#include "TLSE.c"
#include "TARVB.c"



TLSE *percorre(TARVB *a, int x, TLSE *l){
    if (!a) return l;
    for (int i=0;i<=a->nchaves;i++){
        if (i == a->nchaves){
            l = percorre(a->filho[i],x,l);
        }
        else if (a->chave[i] < x){
            l = percorre(a->filho[i],x,l);
            l = TLSE_ins_fim(l,a->chave[i]);
        }
    }
    return l;
}

TLSE* mN(TARVB *a, int N){
    TLSE *l = NULL;
    return percorre(a,N,l);
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
    TLSE *resp = mN(arvore,ele);
    if (resp) TLSE_imp_rec(resp);
    else printf("erro");
    TARVB_Libera(arvore);
    return 0;
}
