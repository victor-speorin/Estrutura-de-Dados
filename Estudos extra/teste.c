/*
Verificar se as condições estabelecidas no enunciado são
respeitadas, caso sim, retore 1, caso não, retorne 0. int teste(TABB* a);

1 - Todos os nós folhas devem estar no mesmo nivel.
2 - Todos os nós de altura {0, 3, 6, 9 ...} devem ser ou folha ou pai de dois filhos.
3 - Todos os nós de altura {1, 4, 7, 10 ...} devem ter somente um filho a esquerda.
4 - Todos os nós de altura {2, 5, 8, 11 ...} devem ter somente um filho a direita.
*/

#include "TABB.c"

TABB *achafolha(TABB*a){
    if (!a->esq && !a->dir) return a;
    if (a->esq) return achafolha(a->esq);
    return achafolha(a->dir);
}

int verni(TABB*a, TABB* b){
    if (a==b) return 0;
    if (b->info > a->info) return verni(a->dir,b) + 1;
    else return verni(a->esq,b) + 1;
}

int folhas(TABB*raiz, TABB*anda, int x){
    if (!anda->esq && !anda->dir){
        if (verni(raiz,anda)==x) return 1;
        return 0;
    }
    return (folhas(raiz,anda->esq,x) && folhas(raiz,anda->dir,x));
}

int veralt(TABB*a){
    if (!a) return 1;
    int x = TABB_altura(a);
    if (x%3==0) {
        if ((!a->esq && a->dir) || (!a->esq && !a->dir)) return 0;
    }
    else if (x%3==1){
        if (!a->esq || a->dir) return 0;
    }
    else {
        if (a->esq || !a->dir) return 0;
    }
    return (veralt(a->esq) && veralt(a->dir));
}

int teste(TABB* a){
    TABB *f = achafolha(a);
    int x = verni(a,f);
    return (veralt(a) && folhas(a,a,x));
}

int main(){
    int n;
    TABB *resp = NULL;
    while(1){
        scanf("%d", &n);
        if(n < 0) break;
        resp = TABB_insere(resp,n);
    }
    TABB_imp_ident(resp);
    printf("Segue o padrao? %d\n", teste(resp));
    TABB_libera(resp);
    return 0;
}