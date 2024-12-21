// Q1) descubra a quantidade de nós de um grafo: int nn(TG *g);

// Q2) descubra a quantidade de arestas de um grafo: int na(TG *g);
#include "TG.c"

// Q1:
int nn(TG *g){
    if (!g) return 0;
    return nn(g->prox_no) + 1;
}

// Q2:
int aux(TVIZ *x){
    if (!x) return 0;
    return aux(x->prox_viz) + 1;
}

int na(TG *g){
    if (!g) return 0;
    return aux(g->prim_viz) + na(g->prox_no);
}

// Main:
int main() {
    int opcao, x, y, n1, n2;
    TG *grafo = NULL;
    do {
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Contar Nos\n\t5 - Contar Arestas");
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
                printf("\to grafo tem %d nos\n", nn(grafo));
                break;

            case 5:
                printf("\to grafo tem %d arestas\n", na(grafo)/2);
                break;

            default:
                if (opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TG_libera(grafo);
    return 0;
}