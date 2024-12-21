/*
Dado um grafo conectado, verifique se ele pode ser
transformado em uma árvore binária. Se ele pode ser
uma árvore binária, retorne um. Se não, retorne zero.
DICA: use TLSE para resolver esta questão: int teste (TG *g); e
*/
#include "TG.c"
#include "TLSE.c"
int teste (TG *g){
    
}

int main(){
    int opcao, x, y, n1,n2;
    TG* grafo = NULL;
    TLSE *l = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Verificar Arvore\n");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\tDigite o no a ser inserido no grafo: ");
                scanf("%d", &x);
                printf("\n");
                grafo = TG_ins_no(grafo,x);
                break;

            case 2:
                printf("\n\tDigite o no que deseja inserir a aresta: ");
                scanf("%d", &x);
                printf("\n");
                printf("\n\tDigite o no que deseja conectar com o no inserido: ");
                scanf("%d", &y);
                printf("\n");
                TG_ins_aresta(grafo,x,y);

            case 3:
                printf("\n\tO grafo eh: ");
                TG_imp_rec(grafo);
                printf("\n");
                break;
            case 4:
                if (teste(grafo)) printf("sim!");
                else printf("nao");
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TG_libera(grafo);
    return 0;
}