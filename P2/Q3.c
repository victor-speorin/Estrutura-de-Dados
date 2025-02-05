/*
dado dois arquivos de inteiros, onde nao há repetição dentro de cada arquivo,
retorne num arquivo saida (usando hashing) todos os pares tais que:
a pertence ao primeiro arq
b pertence ao segundo arq
(a%k) + (b%k) = k
*/

#include "TH.c"

void misc(char *arq_entrada1, char *arq_entrada2, char *saida, int k){
    int x, tam = 5;
    TH_inicializa("Hash.bin", "Dados.bin", tam);
    FILE *fp1 = fopen(arq_entrada1,"r");
    if (!fp1) exit(1);
    while (fscanf(fp1,"%d",&x)==1)
        TH_insere("Hash.bin","Dados.bin",tam,x);
    FILE *hash = fopen("Hash.bin","rb+");
    FILE *fp2 = fopen(arq_entrada2,"r");
    if (!fp2) exit(1);
    while (fscanf(fp2,"%d",&x)==1){
        for (int i=0;i< tam;i++){
            int end;
            TA aux;
            fread(&end, sizeof(int),1,hash);
            TH_imprime("Hash.bin", "Dados.bin",tam);
            printf("\n");
            printf("%d", end);
            if (end!=-1){
                FILE *dados = fopen("Dados.bin","rb+");
                fseek(dados,end,SEEK_SET);
                fread(&aux, sizeof(TA),1,dados);
                if (aux.status && ((aux.mat % k) + (x%k) == k)){
                    FILE *fs = fopen(saida,"at");
                    fprintf(fs,"%d\n",aux.mat);
                    fprintf(fs,"%d\n\n",x);
                    fclose(fs);
                }
                while (aux.prox!=-1){
                    fseek(dados,aux.prox,SEEK_SET);
                    fread(&aux, sizeof(TA),1,dados);
                    if (aux.status && ((aux.mat % k) + (x%k) == k)){
                        FILE *fs = fopen(saida,"at");
                        fprintf(fs,"%d\n",aux.mat);
                        fprintf(fs,"%d\n\n",x);
                        fclose(fs);
                    }
                }
                fclose(dados);
            }
        }
        rewind(hash);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(hash);
}
  
int main(void){
    int k;
    printf("digite o k:");
    scanf("%d", &k);
    misc("Arq1.txt", "Arq2.txt", "Saida.txt",k);
  return 0;
}
