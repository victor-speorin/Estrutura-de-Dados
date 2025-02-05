#include <limits.h>
#include "TARVB.c"
#include "TLSE.c"

TLSE *percorre(TARVB *a, int ind, TLSE *l){
    if (!a) return l;
    for (int i=0;i<=a->nchaves;i++){
        if (i==a->nchaves)
            l = percorre(a->filho[i],ind,l);
        else if (i==ind){
            l = percorre(a->filho[i],ind,l);
            l = TLSE_ins_ini(l,a->chave[i]);
        }
        else
            l = percorre(a->filho[i],ind,l);
    }
    return l;
}

int* todos_ind(TARVB *a, int ind, int *tam_vet){
    if (!a){
        *tam_vet = 0;
        return NULL;
    }
    TLSE *l = NULL;
    l = percorre(a,ind,l);
    TLSE *aux = l;
    TLSE *aux2 = l;
    int c=0;
    while (aux){
        c++;
        aux=aux->prox;
    }
    int *vet = (int*) malloc(sizeof(int)*c);
    for (int i=c-1;i>=0;i--){
        vet[i] = l->info;
        l=l->prox;
    }
    *tam_vet = c;
    aux = aux2;
    l = aux2;
    TLSE_lib_rec(aux);
    TLSE_lib_rec(aux2); // o que alterei foi isso, pois antes eu liberava com o l e o aux em NULL.
    TLSE_lib_rec(l);
    return vet;
}

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  int t;
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num;
  do{
    scanf("%d", &num);
    if(num <= 0) break;
    arvore = TARVB_Insere(arvore, num, t);
  }while(1);

  /*
  if(arvore){
    int ind, tam_vet;
    scanf("%d", &ind);
    int *resp = todos_ind(arvore, ind, &tam_vet);
    if(tam_vet){
      int i;
      for(i = 0; i < tam_vet; i++) printf("resp[%d] = %d\n", i, resp[i]);
      free(resp);
    }
  }
  */
  TARVB_Libera(arvore);
  return 0;
}
