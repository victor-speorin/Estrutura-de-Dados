// verificar se duas arvores são iguais
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

int igual(TAB* a1, TAB* a2){
    if (!a1 && !a2) return 1;
    if (!a1 || !a2) return 0;
    if (a1->info!=a2->info) return 0;
    return (igual(a1->esq,a2->esq) && igual(a1->dir, a2->dir));
}

int main(void){
    //Para facilitar o meu processo de criação da árvore, colocarei ela numa lógica binaria de busca, pois o foco aqui é a verificação da função copia
    int opcao, x,ver;
    TAB* raiz = NULL;
    TAB* secundaria = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir na primeira\n\t2 - Imprimir a primeira\n\t3 - Inserir na segunda\n\t4 - Imprimir a segunda\n\t5 - Verificar se sao iguais\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf(" %d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\tDigite o valor a ser inserido na primeira arvore: ");
                scanf(" %d", &x);
                printf("\n");
                raiz = insere(raiz,x);
                break;

            case 2:
                printf("\tA primeira arvore eh: ");
                TAB_imp_sim(raiz);
                printf("\n");
                break;

            case 3:
                printf("\n\tDigite o valor a ser inserido na segunda arvore: ");
                scanf(" %d", &x);
                printf("\n");
                secundaria = insere(secundaria,x);
                break;

            case 4:
                printf("\tA segunda arvore eh: ");
                TAB_imp_sim(secundaria);
                printf("\n");
                break;

            case 5:
                ver = igual(raiz,secundaria);
                if(ver) printf("Sao iguais!!!");
                else printf("Nao sao iguais :( ");
                printf("\n");
                break;


            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TAB_libera(raiz);
    TAB_libera(secundaria);
    return 0;
}