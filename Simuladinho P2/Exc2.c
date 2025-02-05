/*
Dado um conjunto de arquivos que contêm números inteiros,
fazendo uso de tabela hash em memória secundária, o objetivo é
armazenar num arquivo de saída apenas o números que aparecem
uma quantidade ímpar de vezes. Para cada arquivo de dados,
deve ser feita somente uma leitura. Cabeçalho da função:
void misc(char **arqs, int num_arqs, char *saida);
*/
#include "TH.c"

void misc(char **arqs, int num_arqs, char *saida){
    int tam, aux, x=0;
    printf("digite o tamanho da hash: ");
    scanf("%d",&tam);
    TH_inicializa("HashA.bin",tam);
    for (int i=0;i<num_arqs;i++){
        FILE *fp = fopen(arqs[i],"r");
        if (!fp) exit(1);
        while(fscanf(fp,"%d",&aux)==1)
            TH_insere("HashA.bin","dadosA.bin",tam,aux);
        fclose(fp);
    }
    FILE *hash = fopen("HashA.bin","rb");
    while (x<tam){
        int end;
        TNUM aux2;
        fread(&end,sizeof(int),1,hash);
        if (end != -1){
            FILE *dados = fopen("dadosA.bin","rb");
            fseek(dados,end,SEEK_SET);
            fread(&aux2, sizeof (TNUM),1,dados);
            if (aux2.qtde%2){
                FILE *fs = fopen(saida,"at");
                fprintf(fs,"%d\n",aux2.num);
                fclose(fs);
            }
            while (aux2.prox != -1){
                fseek(dados,aux2.prox,SEEK_SET);
                fread(&aux2, sizeof (TNUM),1,dados);
                if (aux2.qtde%2){
                    FILE *fs = fopen(saida,"at");
                    fprintf(fs,"%d\n",aux2.num);
                    fclose(fs);
                }
            }
            fclose(dados);
        }
        x++;
    }
    fclose(hash);
}