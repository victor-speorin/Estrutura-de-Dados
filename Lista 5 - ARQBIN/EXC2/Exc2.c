/*
Escreva um programa em C que receba como entrada um arquivo binário de clientes
“clientes.bin” e, sem ler todos os registros para memória, permita a consulta dos dados de um
cliente em função do seu CPF. Considere que o formato de cada registro é dado pelos seguintes
campos: nome – char (40), CPF – char(11), conta_corrente (int), agencia
(int), saldo (float).
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

void CPF(char* ArqEnt){
    FILE *fp = fopen(ArqEnt,"rb");
    TP p;
    int ver, r;
    char cpf[11];
    do{
        r = fread(&p,sizeof(TP),1,fp);
        printf("\tqual cpf deseja buscar?");
        scanf("%s",cpf);
        while (r==1){
            if (strcmp(p.cpf,cpf)==0){
                printf("\to cliente do cpf %s tem: \n", cpf);
                printf("\tnome: %s\n", p.nome);
                printf("\tconta corrente: %d\n", p.conta_corrente);
                printf("\tagencia: %d\n", p.agencia);
                printf("\tsaldo: %.2f\n", p.saldo);
                break;
            }
            r = fread(&p,sizeof(TP),1,fp);
        }
        if (r!=1) {
            printf("\tesse cliente nao consta em nossa base de dados,\n\tdeseja buscar outro?\n\tDigite 1 para sim e 0 para nao: ");
            scanf("%d",&ver);
        }
        else{
            printf("\tdeseja buscar outro cliente? Digite 1 para sim e 0 para nao: ");
            scanf("%d",&ver);
        }
        rewind(fp);
    }while(ver == 1);
    fclose(fp);
}

void cria_binario(char* Arq_Saida){
    FILE* fs = fopen(Arq_Saida,"wb");
    if(!fs) exit(1);
    int ver = 1, indice = 1;
    TP pessoa;
    do{
        pessoa.indice = indice;
        printf("\tDigite o nome:\n ");
        scanf("%s[/^]",pessoa.nome);
        printf("\tDigite o CPF:\n ");
        scanf("%s",pessoa.cpf);
        printf("\tDigite o numero da conta corrente:\n ");
        scanf("%d",&pessoa.conta_corrente);
        printf("\tDigite o numero da agenica:\n ");
        scanf("%d",&pessoa.agencia);
        printf("\tDigite o saldo da conta:\n");
        scanf("%f",&pessoa.saldo);
        fwrite(&pessoa,sizeof(TP),1,fs);
        printf("\tDeseja inserir mais uma pessoa? Digite 1 para sim e 0 para nao:\n ");
        scanf("%d",&ver);
        indice++;
        if(!ver) break;
    }while(ver == 1);
    fclose(fs);
}

int main(){
    cria_binario("EXC2/clientes.bin");
    FILE *fp = fopen("EXC2/clientes.bin", "rb");
    if(!fp) exit(1);
    CPF("EXC2/clientes.bin");
    fclose(fp);
    return 0;
}
