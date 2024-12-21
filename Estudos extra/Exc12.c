/*
Q2 - Verificar se as condições estabelecidas no enunciado são respeitadas, caso sim, retore 1, caso não, retorne 0. int teste(TABB* a);

1 - Todos os nós folhas devem estar no mesmo nivel.
2 - Todos os nós de altura {0, 3, 6, 9 ...} devem ser ou folha ou pai de dois filhos.
3 - Todos os nós de altura {1, 4, 7, 10 ...} devem ter somente um filho a esquerda.
4 - Todos os nós de altura {2, 5, 8, 11 ...} devem ter somente um filho a direita.
*/
#include "TABB.c"

int nivel (TABB *a, TABB*b){
    if (b==a) return 0;
    if (b->info > a->info) return nivel(a,b->esq) + 1;
    else return nivel(a,b->dir) + 1;
}

int teste2(TABB* a, TABB*b, int x){
    if (!a) return 1;
    if (!a->esq && !a->dir){
        int y = nivel(a,b);
        if (y!=x) return 0;
        return 1;
    }
    return (teste2(a->esq,b,x) && teste2(a->dir,b,x));
}

TABB *achafolha(TABB*a){
    if (a->esq) return achafolha(a->esq);
    else if (a->dir) return achafolha(a->dir);
    return a;
}

int veralt(TABB *a){
    if (!a) return 1;
    int x = TABB_altura(a);
    if (x%3==0){
        if ((a->esq && !a->dir) || (!a->esq && a->dir)) return 0;
    }
    else if (x%3==1){
        if (a->dir || !a->esq) return 0;
    }
    else if (x%3==2){
        if (a->esq || !a->dir) return 0;
    }
    return ((veralt(a->esq))&&(veralt(a->dir)));
}

int teste(TABB* a){
    if (!a) return 1;
    TABB*b = a;
    a = achafolha(a);
    int x = nivel(a,b);
    a=b;
    return ((teste2(a,b,x)) && (veralt(a)));
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