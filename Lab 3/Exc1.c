/*
Uma função em C que, dada uma árvore B qualquer,
retorne, numa lista, todos os elementos maiores que N.
A função deve ter o seguinte protótipo: TLSE* mN(TARVB*a, int N);
*/

#include "TARVB.c"
#include "TLSE.c"

TLSE *insere_ord(TLSE*l, int x){
    if ((!l)||(x<l->info)) l= TLSE_ins_ini(l,x);
    else l->prox = insere_ord(l->prox,x);
    return l;
}

TLSE *retorno (TARVB *a, int n, TLSE *l){
    if (!a) return l;
    if (a->chave[0] > n){
        for (int i=0;i<a->nchaves;i++) l = insere_ord(l,a->chave[i]);
        for (int i=0;i<=a->nchaves;i++) l = retorno(a->filho[i],n,l);
    }
    if (a->chave[0] <= n){
        for (int i=0;i<a->nchaves;i++){
            if (a->chave[i] > n) l = insere_ord(l,a->chave[i]);
        }
        for (int i=0;i<=a->nchaves;i++){
            if (a->chave[i] > n) l = retorno(a->filho[i],n,l);
        }
    }
    return l;
}

TLSE* mN(TARVB*a, int N){
    TLSE *l = NULL;
    return retorno(a,N,l);
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
    if (resp) TLSE_imp_rec_rev(resp);
    else printf("erro");
    TARVB_Libera(arvore);
    return 0;
}
