/*
 * Escreva uma funão que retorna a lista de caminhos da raiz até cada folha.

// Estrutura para a lista secundária
typedef struct Listasec {
    int info;
    struct Listasec* prox;
}LS;

// Estrutura para a lista principal
typedef struct Listapri {
    int info;
    LS* lista2;
    struct Listapri* prox;
}LP;

// Função para criar um novo nó da lista secundária
LS* Crianosec(int x) {
    LS* novo = (LS*)malloc(sizeof(LS));
    if (!novo) {
        printf("Erro.\n");
        exit(1);
    }
    novo->info = x;
    novo->prox = NULL;
    return novo;
}

// Função para criar um novo nó da lista principal
LP* Crianopri(int x) {
    LP* novo = (LP*)malloc(sizeof(LP));
    if (!novo) {
        printf("Erro.\n");
        exit(1);
    }
    novo->info = x;
    novo->lista2 = NULL;
    novo->prox = NULL;
    return novo;
}
*/
#include "TABB.c"
#include "TLSE.c"
#include "TG.c"

TG* caminhos(TABB *a){

}

int main(){
    int opcao, x, y;
    TABB* raiz = NULL, *resp = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - kesimo\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao){
            case 1:
                printf("\n\tDigite o valor a ser inserido na arvore: ");
                scanf("%d", &x);
                printf("\n");
                raiz = TABB_insere(raiz, x);
                break;
            case 2:
                printf("\tA arvore eh: ");
                TABB_imp_ident(raiz);
                printf("\n");
                break;
            case 3:
                printf("\tdigite o k:");
                scanf("%d",&y);
                resp = menor(raiz,y);
                if (resp) printf("\to menor ao k eh: %d", resp->info);
                else printf("ruim");
                break;
            default:
                if(opcao != 0)
                    printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TABB_libera(raiz);
    return 0;
}
