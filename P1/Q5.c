#include "TG.h"
#include <limits.h>
// ** Victor Teles Araujo Speorin **

// Essa questão eu não fiz na prova, então não tem nada para corrigir, o código é novo.

int aux(TG*g){
    int x = 0;
    TG* p = g;
    while (p) {
        if (p->id_no > x) x = p->id_no;
        p = p->prox_no;
    }
    return x;
}

void teste(TG* g, int k_atual, int k_ofc ,int destino, int atual, int caminho_atual, int* caminho_ofc, int* visitados, int* k_menor){
    visitados[atual] = 1;
    k_atual++;
    if (k_atual > k_ofc) caminho_atual = INT_MAX;
    if (atual == destino){
        if (caminho_atual < *caminho_ofc){
            *k_menor = k_atual;
            *caminho_ofc = caminho_atual;
        }
    }
    else{
        TG* x = TG_busca_no(g,atual);
        TVIZ* viz = x->prim_viz;
        while(viz){
            if(!visitados[viz->id_viz]){
                teste(g, k_atual,k_ofc,destino,viz->id_viz,caminho_atual+viz->custo,caminho_ofc,visitados,k_menor);
            }
            viz = viz->prox_viz;
        }
    }
    visitados[atual] = 0;
}

int mdk(TG *g, int origem, int destino, int k, int *tam_real_caminho){
    if (!g) return 0;
    int* visitados = (int *)malloc(sizeof(int) * (aux(g) + 1));
    for (int i=0;i<(aux(g)+1);i++) visitados[i]=0;
    int* menor_k = malloc(sizeof(int));
    *menor_k = INT_MAX;
    *tam_real_caminho= INT_MAX;
    teste(g,-1,k,destino,origem,0,tam_real_caminho,visitados,menor_k);
    int resultado = *tam_real_caminho;
    *tam_real_caminho = *menor_k;
    free(menor_k);
    free(visitados);
    return resultado;
}

int main(){
  TG *g = TG_inicializa();
  int n;
  do{
    scanf("%d", &n);
    if(n <= 0) break;
    g = TG_ins_no(g, n);
  }while(1);
  
  int m, custo;
  do{
    scanf("%d%d%d", &n, &m, &custo);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g, n, m, custo);
  }while(1);
  TG_imprime(g);
  int k;
  scanf("%d%d%d", &n, &m, &k);
  int tam_real = 0;
  custo = mdk(g, n, m, k, &tam_real);
  printf("no %d alcanca o no %d em %d arestas: %d (%d)\n", n, m, k, custo, tam_real);
  TG_libera(g);
  return 0;
}

