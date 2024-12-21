// Testar se dois grafos são iguais - int ig(TG *g1, TG *g2)
#include "TG.c"

int verar(TVIZ *x1, TVIZ *x2){
    if (!x1 && !x2) return 1;
    if (!x1 || !x2) return 0;
    if (x1->id_viz != x2->id_viz) return 0;
    return verar(x1->prox_viz,x2->prox_viz);
}

int ig(TG *g1, TG *g2){
    if (!g1) return 1;
    if (!(TG_busca_no(g2,g1->id_no))) return 0;
    if (!verar(g1->prim_viz, TG_busca_no(g2,g1->id_no)->prim_viz)) return 0;
    return ig(g1->prox_no,g2);
}

int main() {
    int opcao, x, g1, g2,y;
    TG *grafo1 = NULL, *grafo2 = NULL;
    do {
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Verificar se sao iguais");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                printf("\n\tDigite em qual grafo deseja inserir: ");
                scanf("%d", &g1);
                printf("\n\tdigite o no: ");
                scanf("%d", &x);
                if (g1 == 1) grafo1 = TG_ins_no(grafo1,x);
                else grafo2 = TG_ins_no(grafo2,x);
                break;

            case 2:
                printf("\n\tDigite em qual grafo deseja inserir: ");
                scanf("%d", &g1);
                printf("\n\tdigite o primeiro no: ");
                scanf("%d", &y);
                printf("\n\t digite em qual no vai contecta-lo: ");
                scanf("%d", &g2);
                if (g1 == 1) TG_ins_aresta(grafo1,y,g2);
                else TG_ins_aresta(grafo2,y,g2);
                break;

            case 3:
                printf("\n\tOs grafos sao: ");
                printf("\n\tgrafo1:\n");
                TG_imp_rec(grafo1);
                printf("\n\tgrafo2:\n");
                TG_imp_rec(grafo2);
                printf("\n");
                break;

            case 4:
                if (ig(grafo1,grafo2)) printf("\n\tiguais!");
                else printf("\n\tnao :(");
                break;

            default:
                if (opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TG_libera(grafo1);
    TG_libera(grafo2);
    return 0;
}