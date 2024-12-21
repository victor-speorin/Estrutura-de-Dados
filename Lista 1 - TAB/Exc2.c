// espelho de uma arvore

#include "TAB.c"
TAB* espelho (TAB *a){
    if (!a) return a;
    return TAB_cria(a->info,espelho(a->dir), espelho(a->esq));
}
int main(){
    int x,y;
    printf("insira a qtd de valores da arvore: ");
    scanf("%d",&y);
    int vet[y];
    for (int i=0;i<y;i++){
        scanf("%d",&x);
        vet[i]=x;
    }
    TAB *a = vet2ab(vet,x);
    printf("arvore og:\n");
    TAB_imp_ident(a);
    TAB *b = espelho(a);
    printf("arvore copia:\n");
    TAB_imp_ident(b);
    TAB_libera(a);
    TAB_libera(b);
    return 0;
}