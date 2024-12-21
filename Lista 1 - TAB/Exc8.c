// verificar o numero de nós internos
#include"TAB.c"

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

int ni(TAB *a){
    if (!a) return 0;
    if(a->esq || a->dir) return 1 + ni(a->esq) + ni(a->dir);
    else return 0;
}

int main(void){
    int opcao, x;
    TAB* raiz = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Contar nos internos\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf(" %d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf(" %d", &x);
                printf("\n");
                raiz = insere(raiz,x);
                break;

            case 2:
                printf("\tA arvore eh: ");
                TAB_imp_sim(raiz);
                printf("\n");
                break;

            case 3:
                if(!raiz) printf("\n\tNao ha arvore!");
                else printf("\n\tA quantidade de nos eh: %d", ni(raiz));
                printf("\n");
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);


    TAB_libera(raiz);
    return 0;
}