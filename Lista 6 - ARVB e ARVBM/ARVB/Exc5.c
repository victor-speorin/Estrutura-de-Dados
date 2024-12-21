/*
função em C que, dada uma árvore qualquer, retire todos os elementos pares da
árvore original. A função deve ter o seguinte protótipo: TARVB* retira_pares
(TARVB* arv);
*/
#include"TARVB.c"
#include "TLSE.c"

TLSE* acha_pares(TARVB*a, TLSE* l){
    if(!a) return l;
    for (int i=0;i<a->nchaves;i++) if (!(a->chave[i]%2)) l = TLSE_ins_fim(l,a->chave[i]);
    for (int j=0;j<=a->nchaves;j++){
        if (a->filho[j]){
            l = acha_pares(a->filho[j],l);
        }
    }
    return l;
}

TARVB* retira_pares (TARVB* arv, int t){
    TLSE *l = NULL;
    l = acha_pares(arv,l);
    while (l){
        arv = TARVB_Retira(arv,l->info,t);
        l=l->prox;
    }
    return arv;
}

int main(void){
    TARVB *arvore = TARVB_Inicializa();
    int t, x;
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
            TARVB_Imprime(arvore);
        }
        else if(num == -1){
            printf("\n");
            TARVB_Imprime(arvore);
            break;
        }
        else if(!num){
            printf("\n");
            TARVB_Imprime(arvore);
        }
        else arvore = TARVB_Insere(arvore, num, t);
        printf("\n\n");
    }
    arvore = retira_pares(arvore,t);
    printf("A arvore sem pares eh:");
    TARVB_Imprime(arvore);
    TARVB_Libera(arvore);
    return 0;
}