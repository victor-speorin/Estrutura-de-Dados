/*
verificar se o grafo, passado como parâmetro de entrada,
possui todos os nós com grau gual a k
int testek(TG *g, int k);
*/
#include "TG.c"

int aux(TVIZ *x){
    if (!x) return 0;
    return aux(x->prox_viz) + 1;
}

int testek(TG *g, int k){
    if (!g) return 1;
    if (aux(g->prim_viz) != k) return 0;
    return testek(g->prox_no,k);
}

int main() {
    int opcao, x, y, n1, n2, k;
    TG *grafo = NULL;
    do {
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Testar se todos os nos tem grau k");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                printf("\n\tDigite o no a ser inserido no grafo: ");
                scanf("%d", &x);
                printf("\n");
                grafo = TG_ins_no(grafo, x);
                break;

            case 2:
                printf("\n\tDigite o no que deseja inserir a aresta: ");
                scanf("%d", &x);
                printf("\n");
                printf("\n\tDigite o no que deseja conectar com o no inserido: ");
                scanf("%d", &y);
                printf("\n");
                TG_ins_aresta(grafo, x, y);

            case 3:
                printf("\n\tO grafo eh: ");
                TG_imp_rec(grafo);
                printf("\n");
                break;

            case 4:
                printf("\n\tdigite o k:  ");
                scanf("%d", &k);
                if (testek(grafo,k)) printf("\n\tsim, todos os nos tem grau %d\n", k);
                else printf("\n\tnao :(\n");
                break;

            default:
                if (opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TG_libera(grafo);
    return 0;
}