//Faça uma função que recebe uma TAB e retorna uma lista simplismente encadeada ordenada

#include"TAB.c"
#include"TLSE.c"

TLSE *insere_ord(TLSE*l, int x){
    if ((!l)||(x<l->info)) l= TLSE_ins_ini(l,x);
    else l->prox = insere_ord(l->prox,x);
    return l;
}

TLSE* percorre(TAB *a, TLSE *l){
    if (!a) return l;
    l = insere_ord(l, a->info);
    if (a->esq) l = percorre(a->esq, l);
    if (a->dir) l = percorre(a->dir, l);
    return l;
}

TAB* insere(TAB* a, int x){
    if(!a){
        TAB* novo = (TAB*)malloc(sizeof(TAB));
        novo ->info = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if(x > a->info) a->dir = insere(a->dir,x);
    if(x < a->info) a->esq = insere(a->esq,x);
    return a;
}

int main(void){
    int opcao, x;
    TAB* raiz = NULL;
    TLSE* lista = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Lista ordenada\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf("%d", &x);
                raiz = insere(raiz,x);
                printf("\n");
                break;

            case 2:
                printf("\tA arvore eh: ");
                TAB_imp_sim(raiz);
                printf("\n");
                break;

            case 3:
                printf("\n\tA lista ordenada com os elementos da arvore eh: ");
                lista = percorre(raiz,lista);
                if(!lista) printf("se fudeu");
                TLSE_imp_rec(lista);
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TAB_libera(raiz);
    TLSE_libera(lista);
    return 0;
}