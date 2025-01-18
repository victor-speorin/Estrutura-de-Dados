/*
 Dados dois arquivos texto que representam conjuntos inteiros
 (isto é, não há elementos repetidos nos arquivos),
 um elemento por linha, e fazendo SOMENTE uma leitura em cada arquivo,
 faça cada uma das questões utilizando tabelas hash em memória secundária:

(a) interseção dos conjuntos: void inter(char* arq1, char* arq2, char* saida);

(b) diferença simétrica de conjuntos: void dif_sim(char* arq1, char* arq2, char* saida);

(c) união de conjuntos: void uniao(char* arq1, char* arq2, char* saida);

*/

#include "TH.c"

//// QUESTÃO 1 ////
void inter(char* arq1, char* arq2, char* saida){
    FILE *fp1 = fopen(arq1,"r");
    FILE *fp2 = fopen(arq2,"r");
    if(!fp1 || !fp2) exit(1);
    int tam;
    printf("Qual o tamanho da hash? ");
    scanf("%d", &tam);
    TH_inicializa("HashA.bin", tam);
    FILE * fs = fopen(saida, "w");
    int tmp;
    while(fscanf(fp1, "%d", &tmp)==1) TH_insere("HashA.bin", "dadosA.bin", tam, tmp);
    while(fscanf(fp2,"%d",&tmp)==1){
        if (TH_busca("HashA.bin","dadosA.bin",tam,tmp)) fprintf(fs,"%d\n",tmp);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fs);
}

//// QUESTÃO 2 ////
void dif_sim(char* arq1, char* arq2, char* saida){
    FILE *fp1 = fopen(arq1,"r");
    FILE *fp2 = fopen(arq2,"r");
    if(!fp1 || !fp2) exit(1);
    int tam, i=0;
    printf("Qual o tamanho da hash? ");
    scanf("%d", &tam);
    TH_inicializa("HashA.bin", tam);
    int tmp;
    while(fscanf(fp1, "%d", &tmp)==1) TH_insere("HashA.bin", "dadosA.bin", tam, tmp);
    while(fscanf(fp2, "%d", &tmp)==1) TH_insere("HashA.bin", "dadosA.bin", tam, tmp);
    FILE * hash = fopen("HashA.bin", "rb");
    while(i<tam){
        //vendo cada idice da hash
        TNUM aux;
        int end;
        fread(&end, sizeof(int), 1, hash);
        if(end != -1){
            FILE * dados = fopen("dadosA.bin", "rb");
            fseek(dados, end, SEEK_SET); //a partir do inicio
            fread(&aux, sizeof(TNUM), 1, dados);
            if(aux.qtde == 1){
                FILE * fs = fopen(saida, "at");
                fprintf(fs, "%d\n", aux.num);
                fclose(fs);
            }
            while(aux.prox != -1){
                fseek(dados, aux.prox, SEEK_SET);
                fread(&aux, sizeof(TNUM), 1, dados);
                if(aux.qtde ==1){
                    FILE * fs = fopen(saida, "at");
                    fprintf(fs, "%d\n", aux.num);
                    fclose(fs);
                }

            }
            fclose(dados);
        }
        i++;
    }
    fclose(fp1);
    fclose(fp2);
    fclose(hash);
}


//// QUESTÃO 3 ////
void uniao(char* arq1, char* arq2, char* saida) {
    FILE *fp1 = fopen(arq1, "r");
    FILE *fp2 = fopen(arq2, "r");
    if (!fp1 || !fp2) exit(1);
    int tam, i = 0;
    printf("Qual o tamanho da hash? ");
    scanf("%d", &tam);
    TH_inicializa("HashA.bin", tam);
    int tmp;
    while (fscanf(fp1, "%d", &tmp) == 1) TH_insere("HashA.bin", "dadosA.bin", tam, tmp);
    while (fscanf(fp2, "%d", &tmp) == 1) TH_insere("HashA.bin", "dadosA.bin", tam, tmp);
    FILE *hash = fopen("HashA.bin", "rb");
    while (i < tam) {
        //vendo cada idice da hash
        TNUM aux;
        int end;
        fread(&end, sizeof(int), 1, hash);
        if (end != -1) {
            FILE *dados = fopen("dadosA.bin", "rb");
            fseek(dados, end, SEEK_SET); //a partir do inicio
            fread(&aux, sizeof(TNUM), 1, dados);
            FILE *fs = fopen(saida, "at");
            fprintf(fs, "%d\n", aux.num);
            fclose(fs);
            while (aux.prox != -1) {
                fseek(dados, aux.prox, SEEK_SET);
                fread(&aux, sizeof(TNUM), 1, dados);
                FILE *fs = fopen(saida, "at");
                fprintf(fs, "%d\n", aux.num);
                fclose(fs);
            }
            fclose(dados);
        }
        i++;
    }
    fclose(fp1);
    fclose(fp2);
    fclose(hash);
}

int main(){
    uniao("Arq1.txt", "Arq2.txt", "ArqSaida.txt");
    return 0;
}