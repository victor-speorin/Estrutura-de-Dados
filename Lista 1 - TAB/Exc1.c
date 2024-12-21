// copia de uma arvore
#include "TAB.c"

TAB* copia(TAB*a){
    if(!a) return NULL;
    TAB_cria(a->info,copia(a->esq),copia(a->dir));
    return a;
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



int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x;
    TAB* raiz = NULL;
    TAB* copy = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Copia\n\t4 - Imprimir copia\n");
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
                copy = copia(raiz);
                if(copy) printf("\n\tArvore copiada com sucesso!!! ");
                else printf("\n\tOcorreu algum problema na copia");
                printf("\n");
                break;

            case 4:
                printf("\t\nA arvore coopiada eh: \n");
                TAB_imp_pre(copy);
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