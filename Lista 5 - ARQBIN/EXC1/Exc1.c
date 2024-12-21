/*
Escreva um programa em C que leia dois arquivos binários “a.bin” e “b.bin” contendo
palavras distintas descritas por 10 caracteres e produza um terceiro arquivo c.bin. No arquivo
“c.bin”, cada um de seus registros contém um par ordenado de palavras, onde a primeira palavra é
proveniente de “a.bin” e a segunda de “b.bin”. Como resultado do processamento, o arquivo
“c.bin” deve conter todos os pares ordenados formados por palavras dos dois arquivos de entrada
(o resultado é o produto cartesiano dos dois conjuntos). Obs.: o processamento deve ser feito em
memória secundária.
*/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
void pares_ordenados(char* ArqA, char* ArqB, char* ArqC){
    FILE* fa = fopen(ArqA, "rb");
    FILE* fb = fopen(ArqB,"rb");
    FILE* fc = fopen(ArqC, "wb");
    if (!fa || !fb || !fc) exit(1);
    char a[10], b[10];
    int v1 = fread(a,sizeof(char),10,fa);
    int v2 = fread(b,sizeof(char),10,fb);
    while (v1 && v2){
        fwrite(a,sizeof(char),10,fc);
        fwrite(b,sizeof(char),10,fc);
        putc('\n',fc);
        v1 = fread(a,sizeof(char),10,fa);
        v2 = fread(b,sizeof(char),10,fb);
    }
    fclose(fa);
    fclose(fb);
    fclose(fc);
}

int main(){
    pares_ordenados("EXC1/ArqA.bin","EXC1/ArqB.bin","EXC1/ArqC.bin");
    return 0;
}