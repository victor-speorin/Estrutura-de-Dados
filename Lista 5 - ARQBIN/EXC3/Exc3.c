/*
Escreva um programa em C que receba o arquivo de clientes do exercício Q2 e produza um
arquivo binário de índices “indices.bin”, onde a sequência dos índices descreve os registros do
arquivo de clientes ordenados pelo saldo.
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct pessoa{
    char nome[40];
    char cpf[11];
    int conta_corrente;
    int agencia;
    float saldo;
    int indice;
}TP;

void saldo(char* ArqEnt){

}


int main(void){
    FILE *fp = fopen("clientes.bin", "rb");
    if(!fp) exit(1);
    saldo("clientes.bin");
    fclose(fp);
    return 0;
}
