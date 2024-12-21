/*
Verifique se um grafo é bipartido, retorne 1 caso sim e 0 caso não,
é permitido o uso da estrutura TLSE para auxiliar. int teste(TG* g)

Definição de bipartido:
Um grafo ao qual podemos separar em duas partições,
como exemplo uma U e outra V, na qual, os nós de U
somente se ligam aos nós de V e os de V somente aos
de U. Além disso, o grafo deve ser todo conectado para
configurar como um grafo bipartido.

Dica:
Para entender melhor, um grafo bipartido, olhado
na implementação de sua estrutura (nós principais e nós de vizinhos),
se trata de um grafo ao qual podemos dividir em 2 grafos,
um em que os nós principais são somente do conjunto U e
os vizinhos todos somente de V, e no outro vice-versa,
desenhe e ficará mais visível a definição de fato de um grafo bipartido.
*/
#include "TG.c"
#include "TLSE.c"

int teste(TG* g){
    if (!g) return 1;
    TLSE *g1 = NULL, *g2 = NULL;
    TVIZ *aux = NULL;
    while (g) {
        if (TLSE_busca(g1, g->id_no)) {
            aux = g->prim_viz;
            while (aux) {
                if (TLSE_busca(g1, aux->id_viz)) return 0;
                if (!TLSE_busca(g2, aux->id_viz)) g2 = TLSE_ins_ini(g2, aux->id_viz);
                aux = aux->prox_viz;
            }
        } else if (TLSE_busca(g2, g->id_no)) {
            aux = g->prim_viz;
            while (aux) {
                if (TLSE_busca(g2, aux->id_viz)) return 0;
                if (!TLSE_busca(g1, aux->id_viz)) g1 = TLSE_ins_ini(g1, aux->id_viz);
                aux = aux->prox_viz;
            }
        } else{
            aux = g->prim_viz;
            int ver = 0;
            while (aux){
                if (TLSE_busca(g1, aux->id_viz)){
                    if (ver == 2) return 0;
                    ver = 1;
                }
                else if (TLSE_busca(g2, aux->id_viz)) {
                    if (ver == 1) return 0;
                    ver = 2;
                }
                aux = aux->prox_viz;
            }
            aux = g->prim_viz;
            if (ver == 1) {
                while (aux) {
                    g1 = TLSE_ins_ini(g1, aux->id_viz);
                    aux = aux->prox_viz;
                }
                g2 = TLSE_ins_ini(g2,g->id_no);
            }
            else if (ver == 2) {
                while (aux) {
                    g2 = TLSE_ins_ini(g2, aux->id_viz);
                    aux = aux->prox_viz;
                }
                g1 = TLSE_ins_ini(g1,g->id_no);
            }
            else {
                g1 = TLSE_ins_ini(g1, g->id_no);
                while (aux) {
                    g2 = TLSE_ins_ini(g2, aux->id_viz);
                    aux = aux->prox_viz;
                }
            }
            }
        g = g->prox_no;
    }
    TLSE_lib_rec(g1);
    TLSE_lib_rec(g2);
    return 1;
}
int main(){
    int opcao, x, y;
    TG* grafo = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Verificar grafo bipartido\n");
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
                break;

            case 3:
                printf("\n\tO grafo eh: ");
                TG_imp_rec(grafo);
                printf("\n");
                break;
            case 4:
                printf("\n\tO verificador eh: %d",teste(grafo));
                printf("\n");
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TG_libera(grafo);
    return 0;
}