#include <stdio.h>
#include <stdlib.h>

int esq (int ind){ 
  return 2 * ind + sizeof(int);
}


int dir (int ind){ 
  return 2 * (ind + sizeof(int));
}


int pai(int ind){
  if(ind) return (((ind - sizeof(int))/sizeof(int))/2) * sizeof(int);
  return -1;
}

// essa eu n fiz na prova, entao o codigo eh todo novo.
void min_heapfy(char *narq, int ind){
    FILE *fp = fopen(narq, "rb+");
    if(!fp) exit(1);
    int esquerda, direita, valoresq, valordir, valorend, menor = ind, fim;
    esquerda = esq(ind);
    direita = dir(ind);
    fseek(fp, 0L, SEEK_END);
    fim = ftell(fp);
    fseek(fp, ind, SEEK_SET);
    fread(&valorend, sizeof(int), 1, fp);
    if(esquerda < fim){
        fseek(fp, esquerda, SEEK_SET);
        fread(&valoresq, sizeof(int), 1, fp);
        if(valoresq < valorend){
            menor = esquerda;
            valorend = valoresq;
        }
    }
    if(direita < fim){
        fseek(fp, direita, SEEK_SET);
        fread(&valordir, sizeof(int), 1, fp);
        if(valordir < valorend){
            menor = direita;
            valorend = valordir;
        }
    }
    if(menor != ind){
        int tmp;
        fseek(fp, ind, SEEK_SET);
        fread(&tmp, sizeof(int), 1, fp);
        fseek(fp, ind, SEEK_SET);
        fwrite(&valorend, sizeof(int), 1, fp);
        fseek(fp, menor, SEEK_SET);
        fwrite(&tmp, sizeof(int), 1, fp);
        fclose(fp);
        min_heapfy(narq, menor);
    }
    else fclose(fp);
}

int main(void){
  char nome_arq[31];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nome_arq);
  int nvet, i = 1, aux;
  printf("Digite o numero de elementos distintos do arquivo: ");
  scanf("%d", &nvet);
  if(nvet <= 0) return 0;
  int vet[nvet];
  scanf("%d", &vet[0]);
  while (i < nvet){
    scanf("%d", &aux);
    if(aux > vet[i - 1]) vet[i++] = aux;
  }

  vet[0] = vet[i - 1] + 1;
  FILE *fp = fopen(nome_arq, "wb");
  if(!fp) exit(1);
  fwrite(&vet, sizeof(int), nvet, fp);
  fclose(fp);

  //min_heapfy(nome_arq, 0);
  
  int resp[nvet];
  fp = fopen(nome_arq, "rb");
  if(!fp) exit(1);
  fread(&resp, sizeof(int), nvet, fp);
  fclose(fp);

  printf("\nVerificacao da operacao min_heapfy...\n");
  for(i = 0; i < nvet; i++) printf("[%d]:\t%d\t%d\n", i, vet[i], resp[i]);

  return 0;
}

