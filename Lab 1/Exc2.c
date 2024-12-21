/*
 Dados um grafo, dois nós x e y, retorne um caminho qualquer
 entre x e y. Se não tiver caminho, o retorno
 é NULL: TLSE *caminho (TG *g, int x, int y)
 */

#include "TG.c"
#include "TLSE.c"

TLSE* caminhoAux(TG* g, TG* no, TLSE* path, TLSE** l_vis, int y) {
    path = TLSE_ins_fim(path, no->id_no);
    if(no->id_no == y) return path;
    *l_vis = TLSE_ins_ini(*l_vis, no->id_no);
    TVIZ* viz = no->prim_viz;
    while(viz) {
        if(!TLSE_busca(*l_vis, viz->id_viz)) {
            TG* no_viz = TG_busca_no(g, viz->id_viz);
            TLSE* path_aux = caminhoAux(g, no_viz, path, l_vis, y);
            if(path_aux) return path_aux;
        }
        viz = viz->prox_viz;
    }

    return NULL;
}

TLSE* caminho(TG* g, int x, int y) {
    TG* no_x = TG_busca_no(g, x);
    if(!no_x) return NULL;
    TVIZ* viz = no_x->prim_viz;
    TLSE* l_vis = TLSE_ins_ini(NULL, no_x->id_no);
    while(viz) {
        TG* no_viz = TG_busca_no(g, viz->id_viz);
        TLSE* path = TLSE_ins_ini(NULL, no_x->id_no);
        path = caminhoAux(g, no_viz, path, &l_vis, y);
        TLSE_imprime(path);
        if(path) return path;
        viz = viz->prox_viz;
    }
    return NULL;
}


int main(){
    int opcao, x, y, n1,n2;
    TG* grafo = NULL;
    TLSE *l = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Inserir No\n\t2 - Inserir Aresta\n\t3 - Imprimir grafo\n\t4 - Acha Caminho\n");
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
                printf("\n insira o primeiro numero:\n ");
                scanf("%d",&n1);
                printf("\n insira o segundo numero:\n ");
                scanf("%d",&n2);
                l = caminho(grafo,n1,n2);
                printf("\n um caminho de %d ate %d eh:\n ", n1,n2);
                TLSE_imp_rec(l);
                printf("\n");
                TLSE_lib_rec(l);
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    TG_libera(grafo);
    return 0;
}