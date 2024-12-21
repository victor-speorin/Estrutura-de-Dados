/*
Escreva um código em C que, dados dois grafos G1 e G2,
verifique se eles são isomórficos (retornando 1) ou não (retornando 0).
Dois grafos G1 = {V1, E1} e G2 = {V2, E2} são isomórficos se:
1) Há uma correspondência um-para-um de V1 para V2; e
2) Há uma correspondência um-para-um de E1 para E2 que mapeia cada aresta de G1 para G2.
A função deve ter o seguinte protótipo: int iso(TG *G1, TG *G2);
*/

#include "TG.c"

int compara(const void* a, const void* b) {
    int int_a = *(int*)a;
    int int_b = *(int*)b;
    return int_a - int_b;
}

int contano(TG *g){
    if (!g) return 0;
    return contano(g->prox_no) + 1;
}

int contaarest(TVIZ*v, int x){
    while (v){
        x++;
        v = v->prox_viz;
    }
    return x;
}

int iso(TG *G1, TG *G2){
    if ((!G1 || !G2) || (contano(G1) != contano(G2))) return 0;
    TG *aux1 = G1, *aux2 = G2;
    int *vet = (int*) malloc(sizeof(int)* contano(G1));
    int *vet2 = (int*) malloc(sizeof(int)* contano(G1));
    for (int i=0;i< contano(G1);i++){
        vet[i] = contaarest(G1->prim_viz,0);
        G1 = G1->prox_no;
    }
    for (int i=0;i< contano(G1);i++){
        vet2[i] = contaarest(G2->prim_viz,0);
        G2 = G2->prox_no;
    }
    G1 = aux1;
    G2 = aux2;
    qsort(vet, contano(G1),sizeof(int),compara);
    qsort(vet2, contano(G1),sizeof(int),compara);
    for (int i=0;i< contano(G1);i++){
        if (vet[i]!=vet2[i]) return 0;
    }
    TG_libera(aux1);
    TG_libera(aux2);
    free(vet);
    free(vet2);
    return 1;
}

int main() {
    int opcao, x, g1, g2, y;
    TG *grafo1 = NULL, *grafo2 = NULL;
    do {
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Verificar se sao iso");
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
                if (g1 == 1) grafo1 = TG_ins_no(grafo1, x);
                else grafo2 = TG_ins_no(grafo2, x);
                break;

            case 2:
                printf("\n\tDigite em qual grafo deseja inserir: ");
                scanf("%d", &g1);
                printf("\n\tdigite o primeiro no: ");
                scanf("%d", &y);
                printf("\n\t digite em qual no vai contecta-lo: ");
                scanf("%d", &g2);
                if (g1 == 1) TG_ins_aresta(grafo1, y, g2);
                else TG_ins_aresta(grafo2, y, g2);
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
                if (iso(grafo1, grafo2)) printf("\n\tisos!");
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