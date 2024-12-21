/*
Implemente um algoritmo que receba como parâmetro de entrada, o nome de um arquivo
texto, cujo conteúdo são o nome do aluno e as duas notas dos alunos do curso, uma em cada linha, e
que ordene o arquivo de saída em ordem crescente pela média do aluno. Isto é, se eu tiver como
entrada o arquivo: "P C/10.0/10.0-J J/3.0/4.0-G G/7.0/7.0-A A/0.5/1.5-I I/5.0/6.0", a
saída será um arquivo com o seguinte texto: "A A/1.0-J J/3.5-I I/5.5-G G/7.0-P C/10.0" -
void media(char *ArqEnt, char *ArqSaida).
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct aluno{
    char nome[50];
    float n1;
    float n2;
    float media;
}TA;

int compara(const void *a, const void *b){
    TA* pa = (TA*)a;
    TA* pb = (TA*)b;

    if(pa->media < pb->media) return -1;
    else return 1;
}

void media(char *ArqEnt, char *ArqSaida){
    FILE *fp = fopen(ArqEnt,"r");
    FILE *fs = fopen(ArqSaida,"w");
    if (!fp || !fs) exit(1);
    TA aluno;
    int x = 0;
    while(!feof(fp)){
        fscanf(fp,"%50[^/]/%f/%f", aluno.nome,&aluno.n1,&aluno.n2);
        x++;
    }
    rewind(fp);
    TA *vet = (TA*)malloc(sizeof(TA)*x);
    for (int i=0;i<x;i++){
        fscanf(fp,"%50[^/]/%f/%f", aluno.nome,&aluno.n1,&aluno.n2);
        vet[i].n1 = aluno.n1;
        vet[i].n2 = aluno.n2;
        vet[i].media = (aluno.n1 + aluno.n2)/2;
        strcpy(vet[i].nome, aluno.nome);
    }
    qsort(vet,x,sizeof(TA),compara);
    for (int i=0;i<x;i++) fprintf(fs,"nome: %s / media: %.1f\n", vet[i].nome,vet[i].media);
    fclose(fp);
    fclose(fs);
    free(vet);
}

int main(){
    media("Ex2","Saida2");
    return 0;
}