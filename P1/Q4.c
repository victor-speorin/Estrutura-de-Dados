#include "TAB.c"

TAB *AchaFolha(TAB *a){
    if (!a->esq && !a->dir) return a;
    if (a->esq) return AchaFolha(a->esq);
    return AchaFolha(a->dir);
}

int AchaNivel (TAB *a, TAB *b){
    if (a==b) return 0;
    if (TAB_busca(a->esq,b->info)) return AchaNivel(a->esq,b) + 1;
    return AchaNivel(a->dir,b) + 1;
}

int Folhas (TAB *a, TAB *b, int x){
    if (!b->esq && !b->dir){
        int y = AchaNivel(a,b);
        if (y==x && y%2==0) return 1;
        return 0;
    }
    if (b->esq && b->dir) return (Folhas(a,b->esq,x) && Folhas(a,b->dir,x));
    if (b->esq) return Folhas(a,b->esq,x);
    return Folhas(a,b->dir,x);
}

int Filhos (TAB *a, TAB *b, int ver){
    if (!a) return 1;
    int x = AchaNivel(b,a);
    if (x%2==0){
        if ((!a->esq && a->dir) || (a->esq && !a->dir)) return 0;
        return (Filhos(a->esq,b,0) && Filhos(a->dir,b,1));
    } else{
        if (ver==0){
            if (a->dir || !a->esq) return 0;
            return Filhos(a->esq,b,0);
        }
        else{
            if (a->esq || !a->dir) return 0;
            return Filhos(a->dir,b,1);
        }
    }
}

int Teste (TAB *a){
    if (!a) return 0;
    if((!a->esq && a->dir) || (a->esq && !a->dir)) return 0;
    if (!a->esq && !a->dir) return 1;
    TAB *aux = a;
    a = AchaFolha(a);
    int n = AchaNivel(aux,a);
    return ((Filhos(aux->esq,aux,0) && Filhos(aux->dir,aux,1) && Folhas(aux,aux,n)));
}