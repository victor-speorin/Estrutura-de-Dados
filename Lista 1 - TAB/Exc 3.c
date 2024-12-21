// retornar o maior elemento
#include "TAB.c"

TAB *Maior (TAB *a){
    if (!a) return a;
    TAB *maior = a, *mesq = Maior(a->esq), *mdir = Maior(a->dir);
    if ((mesq) && (mesq->info>a->info)) maior=mesq;
    if ((mdir) && (mdir->info>maior->info)) maior=mdir;
    return maior;
}

TAB* insere(TAB* a, int x){ // estou usando o metodo de ABB para inserir
    if(!a){
        TAB* novo = (TAB*)malloc(sizeof(TAB));
        novo ->info = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if(x >= a->info) a->dir = insere(a->dir,x);
    if(x < a->info) a->esq = insere(a->esq,x);
    return a;
}

int main(){
    int opcao, x;
    TAB* oi = NULL;
    TAB* raiz = NULL;
    TAB* copy = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Achar o maior elemento\n\t ");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf("%d", &x);
                printf("\n");
                raiz = insere(raiz,x);
                break;

            case 2:
                printf("\tA arvore eh: ");
                TAB_imp_pre(raiz);
                printf("\n");
                break;

            case 3:
                copy=Maior(raiz);
                printf("O maior elemento da arvore eh: %d", copy->info); printf("\n");
                break;


            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TAB_libera(raiz);
    TAB_libera(copy);
    return 0;
}