/*
Desenvolva um procedimento que receba o nome de um arquivo texto e retire deste texto
palavras consecutivas repetidas. O seu programa deve retornar, no arquivo de saída, informado
como parâmetro dessa função, a resposta desta questão. Por exemplo, se o conteúdo de um arquivo
texto for: "Isto e um texto texto repetido repetido repetido . Com as repeticoes
repeticoes fica fica sem sem sentido . Sem elas elas elas melhora melhora um um
pouco .", a saída do seu programa será um arquivo com o seguinte texto: "Isto e um texto
repetido . Com as repeticoes fica sem sentido . Sem elas melhora um um pouco ."
- void RetRepet(char *ArqEnt, char *ArqSaida).
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void RetRepet(char *ArqEnt, char *ArqSaida){
    FILE *fp1 = fopen(ArqEnt,"r"), *fp2 = fopen(ArqEnt,"r");
    FILE *fs = fopen(ArqSaida,"w");
    if (!fs || !fp1 || !fp2) exit(1);
    char agr[50], prox[50];
    int x = fscanf(fp1,"%s",agr), y = fscanf(fp2,"%s",prox);
    y = fscanf(fp2,"%s",prox);
    while (x==1){
        if (y!=1){
            fprintf(fs,"%s",agr);
            break;
        }
        if (strcmp(agr,prox)!=0) fprintf(fs,"%s ",agr);
        x = fscanf(fp1,"%s",agr);
        y = fscanf(fp2,"%s",prox);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fs);
}

int main(){
    RetRepet("Ex1","Saida1");
    return 0;
}