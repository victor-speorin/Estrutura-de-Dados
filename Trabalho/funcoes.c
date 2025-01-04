#include "TR.c"
#include "TARVBM.c"

void retornaCEP(int cep, int t, char **arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(*arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (x->chaves[i].cep == cep) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

void retornaLAT(char *latitude, int t, char **arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(*arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].latitude, latitude)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

void retornaLO(char *longitude, int t, char **arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(*arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].latitude, longitude)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

void retornaBAIRRO(char *bairro, int t, char **arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(*arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].bairro, bairro)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

void retornaTIPO(int tipo, int t, char **arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(*arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    char aux[30];
    if (tipo == 1) strcpy(aux,"APARTMENT");
    else if (tipo == 2) strcpy(aux,"HOME");
    else if (tipo == 3) strcpy(aux,"RESIDENTIAL_ALLOTMENT_LAND");
    else if (tipo == 4) strcpy(aux,"COMMERCIAL_PROPERTY");
    else if (tipo == 5) strcpy(aux,"OFFICE");
    else if (tipo == 6) strcpy(aux,"COMMERCIAL_BUILDING");
    else if (tipo == 7) strcpy(aux,"CONDOMINIUM");
    else if (tipo == 8) strcpy(aux,"BUSINESS");
    else if (tipo == 9) strcpy(aux,"PENTHOUSE");
    else if (tipo == 10) strcpy(aux,"VILLAGE_HOUSE");
    else if (tipo == 11) strcpy(aux,"SHED_DEPOSIT_WAREHOUSE");
    else if (tipo == 12) strcpy(aux,"ALLOTMENT_LAND");
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].tipo, aux)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

void retornaM2(double m2, int t, char **arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(*arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (x->chaves[i].preco_total / x->chaves[i].preco_m2 == m2) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

void retornaRUA(char *rua, int t, char **arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(*arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].rua, rua)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}