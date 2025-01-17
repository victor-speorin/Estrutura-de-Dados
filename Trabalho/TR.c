#include "TR.h"

void substituir_virgula_por_ponto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}

void TABM_libera(TABM *a){
    free(a);
}

void TABM_escreve(char* arquivo, TABM* no, int t) {
    FILE* fp = fopen(arquivo, "wb");
    if (!fp) exit(1); // Saia do programa em caso de erro na abertura
    fwrite(no, sizeof(TABM), 1, fp);
    fclose(fp);
}

void TABMtoTABM(TABM *origem, TABM *destino, int t) {
    destino->folha = origem->folha;
    destino->nchaves = origem->nchaves;
    strcpy(destino->prox, origem->prox);
    for (int i = 0; i < origem->nchaves; i++) {
        destino->chaves[i].id = origem->chaves[i].id;
        strcpy(destino->chaves[i].bairro, origem->chaves[i].bairro);
        strcpy(destino->chaves[i].tipo, origem->chaves[i].tipo);
        strcpy(destino->chaves[i].rua, origem->chaves[i].rua);
        destino->chaves[i].numero = origem->chaves[i].numero;
        destino->chaves[i].preco_total = origem->chaves[i].preco_total;
        destino->chaves[i].preco_m2 = origem->chaves[i].preco_m2;
        strcpy(destino->chaves[i].descricao, origem->chaves[i].descricao);
        destino->chaves[i].cep = origem->chaves[i].cep;
        strcpy(destino->chaves[i].latitude, origem->chaves[i].latitude);
        strcpy(destino->chaves[i].longitude, origem->chaves[i].longitude);
    }
    for (int i = 0; i < 2 * t; i++) {
        strcpy(destino->filhos[i], origem->filhos[i]);
    }
}

TABM *TABM_cria_no(int t){
    TABM *novo = (TABM*)malloc(sizeof(TABM));
    novo->nchaves = 0;
    novo->folha = 1;
    strcpy(novo->prox, "prox");
    /*
    novo->chaves = (TR*)malloc(sizeof(TR) * (t*2)-1);
    novo->filhos = (char**)malloc(sizeof(char**) * t * 2);
    for(int i = 0; i < 2 * t; i++){
        novo->filhos[i] = (char*)malloc(sizeof(char) * 30);
    }
    */
    return novo;
}

void TABM_cria(int t, char **arq, int *c){
    sprintf(*arq, "Arqs/%03d.bin", (*c));
    TABM resp = *TABM_cria_no(t);
    resp.folha = 1;
    resp.nchaves = 0;
    resp.prox;
    strcpy(resp.prox, "Arqs/Prox");
    for(int i = 0; i < (t*2)-1; i++) {
        strcpy(resp.chaves[i].bairro, "Nulos");
    }
    for(int i = 0; i < (t*2); i++) strcpy(resp.filhos[i], "Nada");
    TABM_escreve(*arq, &resp, t);
    (*c)++;
}


TABM *arq2TABM(char *arq, int t){
    FILE *fp = fopen(arq, "rb");
    if(!fp) return NULL;
    TABM *resp = TABM_cria_no(t);
    fread(resp, sizeof(TABM), 1, fp);
    fclose(fp);
    return resp;
}

TR TRtoTR(TR aux, TR T) {
    aux.id = T.id;
    strcpy(aux.bairro, T.bairro);
    strcpy(aux.tipo, T.tipo);
    strcpy(aux.rua, T.rua);
    aux.numero = T.numero;
    aux.preco_total = T.preco_total;
    aux.preco_m2 = T.preco_m2;
    strcpy(aux.descricao, T.descricao);
    aux.cep = T.cep;
    strcpy(aux.latitude, T.latitude);
    strcpy(aux.longitude, T.longitude);
    return aux;
}

void TABM_imprime_chaves(char *raiz, int t){
    TABM *a = arq2TABM(raiz, t);
    if(!a->folha){
        TABM_imprime_chaves(a->filhos[0], t);
    }
    else {
        int c = 0;
        while(a){
            int i;
            printf("no %d:\n", c);
            for(i = 0; i < a->nchaves; i++) printf("%ld\t%s\n", a->chaves[i].id, a->chaves[i].latitude);
            printf("\n");
            a = arq2TABM(a->prox, t);
            c++;
        }
        printf("\n");
    }
}

void imp(char* raiz,int andar, int t){
    FILE* fp = fopen(raiz,"rb");
    if(fp){
        TABM * a = TABM_cria_no(t);
        fread(a,sizeof(TABM),1,fp);
        int i,j;
        for(i = 0; i < a->nchaves; i++){
            imp(a->filhos[i],andar+1,t);
            for(j = 0; j<= andar; j++) printf("\t");
            printf("%ld\n", a->chaves[i].id);
        }
        imp(a->filhos[i],andar+1,t);
        fclose(fp);
        TABM_libera(a);
    }
    return;
}

void TABM_imprime(char** raiz,int t){
    printf("\n\n\n");
    imp(*raiz,0,t);
}

char *TABM_busca(char *arq, long id, int t){
    TABM a = *arq2TABM(arq, t);
    if(a.nchaves == 0) return "NULL";
    int i = 0;
    while((i < a.nchaves) && (id > a.chaves[i].id)) i++;
    if((i < a.nchaves) && (a.folha) && (id == a.chaves[i].id)) return arq;
    if(a.folha) return "NULL";
    if(a.chaves[i].id == id) i++;
    if(i > a.nchaves) i = a.nchaves;
    return TABM_busca(a.filhos[i], id, t);
}

void funcauxbusca(char *raiz, long id, int t){
    char tmp[20];
    strcpy(tmp, TABM_busca(raiz, id, t));
    printf("\n\t%s", tmp);
    TABM a = *arq2TABM(tmp, t);
    printf("\t\n%s", a.chaves[0].rua);
}

void copia_no(TABM *x, char *arq, int t){
    FILE *fp = fopen(arq, "wb+");
    if(!fp) exit(1);
    TABM aux;
    TABMtoTABM(x, &aux, t);
    fwrite(&aux, sizeof(TABM), 1, fp);
    fclose(fp);
}

TABM *divisao(TABM *x, int i, TABM *y, int t, int *cont){
    TABM *z = TABM_cria_no(t);
    char *z_nome_arq = (char*)malloc(sizeof(char) * 6);
    TABM_cria(t, &z_nome_arq, cont);
    z->folha = y->folha;
    int j;
    if(!y->folha){
        z->nchaves = t-1;
        for(j = 0; j < t-1; j++) z->chaves[j] = y->chaves[j+t];
        for(j = 0; j < t; j++){
            strcpy(z->filhos[j], y->filhos[j + t]);
            strcpy(y->filhos[j+t], "NULL");
        }
    }
    else{
        z->nchaves = t;
        for(j = 0; j < t; j++) {
            z->chaves[j] = y->chaves[j + t - 1];
        }
        strcpy(z->prox, y->prox);
        strcpy(y->prox, z_nome_arq);
    }
    y->nchaves = t-1;
    for(j = x->nchaves; j >=i; j--) strcpy(x->filhos[j+1],x->filhos[j]);
    strcpy(x->filhos[i],z_nome_arq);
    for(j = x->nchaves; j >= i; j--) x->chaves[j] = x->chaves[j-1];
    x->chaves[i-1] = y->chaves[t-1];
    x->nchaves++;
    FILE *fz = fopen(z_nome_arq, "wb+");
    TABM aux;
    TABMtoTABM(z, &aux, t);
    fwrite(&aux, sizeof(TABM), 1, fz);
    fclose(fz);
    free(z_nome_arq);
    TABM_libera(z);
    return x;
}

TABM *insere_nao_completo(TABM *x, TR *r, int t, int *cont){
    int i = x->nchaves-1;
    if(x->folha){
        while((i>=0) && (r->id < x->chaves[i].id)){
            x->chaves[i+1] = x->chaves[i];
            i--;
        }
        x->chaves[i+1] = *r;
        x->nchaves++;
        return x;
    }
    while((i>=0) && (r->id < x->chaves[i].id)) i--;
    i++;
    TABM *z = TABM_cria_no(t);
    z = arq2TABM(x->filhos[i], t);
    if(z->nchaves == ((2*t)-1)){
        FILE *fp = fopen(x->filhos[i],"wb");
        x = divisao(x, (i+1), z, t, cont);
        if(r->id > x->chaves[i].id) i++;
        TABM aux;
        TABMtoTABM(z,&aux,t);
        fwrite(&aux,sizeof(TABM),1,fp);
        fclose(fp);
    }
    z = arq2TABM(x->filhos[i], t);
    z = insere_nao_completo(z, r, t, cont);
    copia_no(z, x->filhos[i], t);
    TABM_libera(z);
    return x;
}


void contachaves(char *arq, int t){
    TABM *a = arq2TABM(arq, t);
    if(!a->folha){
        contachaves(a->filhos[0], t);
    }
    else {
        int c = 0;
        while(a){
            c = c + a->nchaves;
            printf("\t%s", a->prox);
            a = arq2TABM(a->prox, t);
        }
        printf("%d\n", c);
    }
}

char* TABM_insere(TR *residencia, int t, char **raiz, int *cont) {
    FILE *fp = fopen(*raiz, "rb+");
    if (!fp) {
        TABM_cria(t, raiz, cont);
        TABM *T = TABM_cria_no(t);
        TABM_escreve(*raiz, T, t);
        T->chaves[0] = *residencia;
        T->nchaves = 1;
        TABM aux;
        TABMtoTABM(T, &aux, t);
        TABM_escreve(*raiz, &aux, t);
        TABM_libera(T);
        return *raiz;
    }

    char test[20];
    strcpy(test, TABM_busca(*raiz, residencia->id, t));
    if (strcmp(test, "NULL") != 0) {
        TABM a = *arq2TABM(test, t);
        int i;
        for (i = 0; a.chaves[i].id != residencia->id; i++);
        a.chaves[i] = TRtoTR(a.chaves[i], *residencia);
        TABM_escreve(test, &a, t);
        return *raiz;
    }
    TABM *T = arq2TABM(*raiz, t);

    if (T->nchaves == (2 * t) - 1) {
        char *S_arq = (char *)malloc(sizeof(char) * 30);
        TABM_cria(t, &S_arq, cont);
        TABM *S = arq2TABM(S_arq, t);
        S->nchaves = 0;
        S->folha = 0;
        strcpy(S->filhos[0], *raiz);
        S = divisao(S, 1, T, t, cont);
        TABM aux_3;
        TABMtoTABM(T, &aux_3, t);
        TABM_escreve(*raiz, &aux_3, t);
        S = insere_nao_completo(S, residencia, t, cont);
        TABM aux;
        TABMtoTABM(S, &aux, t);
        TABM_escreve(S_arq, &aux, t);

        TABM_libera(T);
        TABM_libera(S);
        strcpy(*raiz, S_arq);
        free(S_arq);
        return *raiz;
    }
    T = insere_nao_completo(T, residencia, t, cont);
    TABM aux;
    TABMtoTABM(T, &aux, t);
    TABM_escreve(*raiz, &aux, t);
    TABM_libera(T);
    return *raiz;
}

TLSE_TR *TLSE_TR_insere(TLSE_TR *l, TR *r){
    TLSE_TR *novo = (TLSE_TR*)malloc(sizeof(TLSE_TR));
    novo->info = r;
    novo->prox = l;
    l = novo;
    return l;
}

TLSE_TR *ledados(char *arq, TLSE_TR *l) {
    FILE *fp = fopen(arq, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    char tmp[200];
    if (fgets(tmp, sizeof(tmp), fp) != NULL) {
        printf("Cabeçalho: %s\n", tmp); // Leitura do cabeçalho
    }
    //ID;BAIRRO;TIPO;RUA;NUMERO;PRECO;R$/m2;DESC;CEP;latitude;longitude
    while (1){
        TR *tr = (TR*)malloc(sizeof(TR));
        char preco[20], precom2[20], id[16];
        if(fscanf(fp, "%15[^;];%30[^;];%30[^;];%50[^;];%d;%19[^;];%19[^;];%2499[^;];%d;%19[^;];%19[^\n]\n", id, tr->bairro, tr->tipo, tr->rua, &tr->numero, preco, precom2, tr->descricao, &tr->cep, tr->latitude, tr->longitude) != 11) break;
        substituir_virgula_por_ponto(preco);
        substituir_virgula_por_ponto(precom2);
        tr->preco_total = atof(preco);
        tr->preco_m2 = atof(precom2);
        tr->id = atol(&id[1]);
        l = TLSE_TR_insere(l, tr);
    }
    fclose(fp);
    return l;
}

void TLSE_TR_imprime(TLSE_TR *l){
    TLSE_TR *p = l;
    while(p){
        printf("%ld\n", p->info->id);
        p = p->prox;
    }
}

void TLSE_TR_libera(TLSE_TR *l){
    TLSE_TR *p = l, *tmp;
    while(p){
        tmp = p;
        p = p->prox;
        free(tmp->info);
        free(tmp);
    }
}

char *remocao(char *no, long id, int t){
    TABM *a = arq2TABM(no, t);
    char busca[20];
    strcpy(busca, TABM_busca(no, id, t));
    if((!a) || (strcmp(busca, "NULL") == 0)) return no; // Verificacao precisa acontecer em toda chamada
    int i;
    for(i = 0; i < a->nchaves && a->chaves[i].id < id; i++);
    if((i < a->nchaves) && (id == a->chaves[i].id) && (a->folha)){
        printf("\nCASO 1\n");
        int j;
        for(j=i; j<a->nchaves - 1; j++) a->chaves[j] = a->chaves[j+1];
        a->nchaves--;
        if(!a->nchaves) {
            TABM_libera(a);
            remove(no);
        }
        else{
            TABM_escreve(no, a, t);
        }
        return no;
    }
    if((i < a->nchaves) && (id == a->chaves[i].id)) i++;
    TABM y = *arq2TABM(a->filhos[i], t), z, tmp;
    z.nchaves = 0; // verificacao para z n existe
    if(y.nchaves == t-1){ // CASOS 3A e 3B
        if(i < a->nchaves){
            tmp = *arq2TABM(a->filhos[i+1], t);
            if((i < a->nchaves) && (tmp.nchaves >= t)){ // CASO 3A dir
                printf("\nCASO 3A: i menor que nchaves\n");
                TABMtoTABM(&tmp, &z, t);
                if(!y.folha){
                    y.chaves[t-1] = TRtoTR(y.chaves[t-1], a->chaves[i]);
                    a->chaves[i] = TRtoTR(a->chaves[i], z.chaves[0]);
                }
                else{
                    a->chaves[i].id = z.chaves[0].id + 1;
                    y.chaves[t-1] = TRtoTR(y.chaves[t-1], z.chaves[0]);
                }
                y.nchaves++;
                int j;
                for(j=0; j < z.nchaves - 1; j++)
                    z.chaves[j] = TRtoTR(z.chaves[j], z.chaves[j+1]);
                strcpy(y.filhos[y.nchaves], z.filhos[0]);
                for(j=0; j < z.nchaves; j++)
                    strcpy(z.filhos[j], z.filhos[j+1]);
                z.nchaves--;
                TABM_escreve(no, a, t);
                TABM_escreve(a->filhos[i], &y, t);
                TABM_escreve(a->filhos[i+1], &z, t);
                strcpy(a->filhos[i], remocao(a->filhos[i], id, t));
                FILE *fpaux = fopen(a->filhos[i], "rb");
                if(!fpaux){
                    strcpy(a->filhos[i], "NULL");
                    TABM_escreve(no, a, t);
                }
                else fclose(fpaux);
                return no;
            }
        }
        if(i > 0){
            tmp = *arq2TABM(a->filhos[i-1], t);
            if((i > 0) && (z.nchaves == 0) && (tmp.nchaves >=t)){ //CASO 3A esq
                printf("\nCASO 3A: i igual a nchaves\n");
                TABMtoTABM(&tmp, &z, t);
                int j;
                for(j = y.nchaves; j>0; j--)
                    y.chaves[j] = TRtoTR(y.chaves[j], y.chaves[j-1]);
                for(j = y.nchaves+1; j>0; j--)
                    strcpy(y.filhos[j], y.filhos[j-1]);
                if(!y.folha){
                    y.chaves[0] = TRtoTR(y.chaves[0], a->chaves[i-1]);
                    a->chaves[i-1] = TRtoTR(a->chaves[i-1], z.chaves[z.nchaves - 1]);
                }
                else{
                    a->chaves[i-1] = TRtoTR(a->chaves[i-1], z.chaves[z.nchaves - 1]);
                    y.chaves[0] = TRtoTR(y.chaves[0], z.chaves[z.nchaves-1]);
                }
                y.nchaves++;
                strcpy(y.filhos[0], z.filhos[z.nchaves]);
                z.nchaves--;
                TABM_escreve(no, a, t);
                TABM_escreve(a->filhos[i], &y, t);
                TABM_escreve(a->filhos[i-1], &z, t);
                strcpy(a->filhos[i], remocao(a->filhos[i], id, t));
                FILE *fpaux = fopen(a->filhos[i], "rb");
                if(!fpaux){
                    strcpy(a->filhos[i], "NULL");
                    TABM_escreve(no, a, t);
                }
                else fclose(fpaux);
            }
        }
        if (z.nchaves == 0) {
            if(i < a->nchaves){
                tmp = *arq2TABM(a->filhos[i + 1], t);
                if((i < a->nchaves) && (tmp.nchaves == t-1)){
                    printf("\nCASO 3B: i menor que nchaves\n");
                    TABMtoTABM(&tmp, &z, t);
                    if(!y.folha){
                        y.chaves[t-1] = TRtoTR(y.chaves[t-1], a->chaves[i]);
                        y.nchaves++;
                    }
                    int j = 0;
                    while(j < t-1){
                        if(!y.folha) y.chaves[t+j] = TRtoTR(y.chaves[t+j], z.chaves[j]);
                        else y.chaves[t+j-1] = TRtoTR(y.chaves[t+j-1], z.chaves[j]);
                        y.nchaves++;
                        j++;
                    }
                    strcpy(y.prox, z.prox);
                    if(!y.folha){
                        for(j=0; j<t; j++){
                            strcpy(y.filhos[t+j], z.filhos[j]);
                            strcpy(z.filhos[j], "NULL");
                        }
                    }
                    remove(a->filhos[i+1]);
                    for(j=i; j < a->nchaves-1; j++){
                        a->chaves[j] = TRtoTR(a->chaves[j], a->chaves[j+1]);
                        strcpy(a->filhos[j+1], a->filhos[j+2]);
                    }
                    strcpy(a->filhos[a->nchaves], "NULL");
                    a->nchaves--;
                    if(!a->nchaves){
                        remove(no);
                        strcpy(no, a->filhos[0]);
                    }
                    TABM_escreve(no, a, t);
                    TABM_escreve(a->filhos[i], &y, t);
                    strcpy(no, remocao(no, id, t));
                    FILE *aux = fopen(a->filhos[i], "rb");
                    if(!aux){
                        strcpy(a->filhos[i], "NULL");
                        TABM_escreve(no, a, t);
                    } else fclose(aux);
                    return no;
                }
            }
            if((i > 0) && (z.nchaves == 0)){
                tmp = *arq2TABM(a->filhos[i-1], t);
                if((i > 0) && (tmp.nchaves == t-1)){
                    TABMtoTABM(&tmp, &z, t);
                    if(!y.folha){
                        if(i == a->nchaves) z.chaves[t-1] = TRtoTR(z.chaves[t-1], a->chaves[i-1]);
                    } else z.chaves[t-1] = TRtoTR(z.chaves[t-1], a->chaves[i]);
                    z.nchaves++;
                }
                int j = 0;
                while(j < t-1){
                    if(!y.folha) z.chaves[t+j] = TRtoTR(z.chaves[t+j], y.chaves[j]);
                    else z.chaves[t+j-1] = TRtoTR(z.chaves[t+j-1], y.chaves[j]);
                    z.nchaves++;
                    j++;
                }
                strcpy(z.prox, y.prox);
                if(!z.folha){
                    for(j = 0; j < t; j++){
                        strcpy(z.filhos[t+j], y.filhos[j]);
                        strcpy(y.filhos[j], "NULL");
                    }
                }
                remove(a->filhos[i]);
                strcpy(a->filhos[a->nchaves], "NULL");
                a->nchaves--;
                if(!a->nchaves){
                    remove(no);
                    strcpy(no,a->filhos[0]);
                }
                else{
                    TABM_escreve(no, a, t);
                    if(strcmp(a->filhos[i-1], "NULL") != 0) {
                        TABM_escreve(a->filhos[i-1], &z, t);
                        i--;
                        strcpy(a->filhos[i], remocao(a->filhos[i], id, t));
                        FILE *aux = fopen(a->filhos[i], "rb");
                        if(!aux){
                            strcpy(a->filhos[i], "NULL");
                            TABM_escreve(no, a, t);
                        } else fclose(aux);
                    }
                }
                return no;
            }
        }
    }
}

void le_dados(char * arquivo, char ** raiz, int t, int* cont){
    FILE * fp = fopen(arquivo, "r");
    if(!fp) exit(1);
    TR *tr = (TR*)malloc(sizeof(TR));
    char tmp[70];
    char preco[20], precom2[20], id[16];
    fgets(tmp, sizeof(tmp), fp);
    printf("%s\n", tmp);
    while(fscanf(fp, "%15[^;];%30[^;];%30[^;];%50[^;];%d;%19[^;];%19[^;];%2499[^;];%d;%19[^;];%19[^\n]\n", id, tr->bairro, tr->tipo, tr->rua, &tr->numero, preco, precom2, tr->descricao, &tr->cep, tr->latitude, tr->longitude) == 11){
        substituir_virgula_por_ponto(preco);
        substituir_virgula_por_ponto(precom2);
        tr->preco_total = atof(preco);
        tr->preco_m2 = atof(precom2);
        tr->id = atol(&id[1]);
        strcpy((*raiz),TABM_insere(tr, t, raiz, cont));
        TABM *a = arq2TABM(*raiz, t);
        // TABM_imprime(raiz, t);
    }
    fclose(fp);
    free(tr);
    return;
}

// Retorna todas as residências de mesmo CEP
void retornaCEP(int cep, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (x->chaves[i].cep == cep) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências de mesma latitude
void retornaLAT(char *latitude, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].latitude, latitude)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências de mesma longitude
void retornaLO(char *longitude, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].longitude, longitude)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências situadas no mesmo bairro
void retornaBAIRRO(char *bairro, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].bairro, bairro)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências de mesmo tipo
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

// Retorna todas residências com mesma quantidade de metros quadrados
void retornaM2(double m2, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if ((x->chaves[i].preco_total / x->chaves[i].preco_m2) == m2) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências na mesma rua
void retornaRUA(char *rua, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].rua, rua)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Remove todos imoveis dentro de uma faixa de preço
void removeImoveisPorPreco(double precoMin, double precoMax, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL; // lista pra armazenar os imoveis que serao removidos

    // vai ate o cara mais a esquerda
    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            // ve se o preco ta na faixa
            if (x->chaves[i].preco_total >= precoMin && x->chaves[i].preco_total <= precoMax) {
                printf("Marcando para remoção: imóvel ID: %ld, Preço Total: %.2f\n", x->chaves[i].id, x->chaves[i].preco_total);

                // bota o imovel na lista de remoções
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    // percorre a lista de remocoes removendo os imoveis
    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p =p->prox;
    }
    TLSE_TR *u = listaRemocoes;
    while(u){
        if (!TABM_busca(arq,u->info->id,t)) printf("o %ld id foi retirado corretamente.", u->info->id);
        else printf("o %ld id NAO foi retirado corretamente.", u->info->id);
    }
    TLSE_TR_libera(listaRemocoes);

}


// Alterando preço total de uma residencia
void alteraPrecoTotal(long int id, double novoPrecoTotal, int t, char *arq) {
    char resp[20];
    int i;
    strcpy(resp, TABM_busca(arq, id, t));
    if(strcmp(resp, "NULL") == 0){
        printf("ID %ld nao encontrado\n", id);
        return;
    }
    TABM *x = arq2TABM(resp, t);
    for(i = 0; (i < x->nchaves) && (x->chaves[i].id != id); i++);
    x->chaves[i].preco_total = novoPrecoTotal;
    TABM_escreve(resp, x, t);
    printf("\nPreco alterado com sucesso\n");
    return;
}


// Alterando preço por m2
void alteraPrecoPorM2(long int id, double novoPrecoM2, int t, char *arq) {
    char resp[20];
    int i;
    strcpy(resp, TABM_busca(arq, id, t));
    if (strcmp(resp, "NULL") == 0) {
        printf("ID %ld nao encontrado\n", id);
        return;
    }
    TABM *x = arq2TABM(resp, t);
    for (i = 0; (i < x->nchaves) && (x->chaves[i].id != id); i++);
    x->chaves[i].preco_m2 = novoPrecoM2;
    TABM_escreve(resp, x, t);
    return;
}

// Alterando descrições
void alteraDescricao(long int id, char *novaDescricao, int t, char *arq) {
    char resp[20];
    int i;
    strcpy(resp, TABM_busca(arq, id, t));
    if (strcmp(resp, "NULL") == 0) {
        printf("ID %ld nao encontrado\n", id);
        return;
    }
    TABM *x = arq2TABM(resp, t);
    for (i = 0; (i < x->nchaves) && (x->chaves[i].id != id); i++);
    strcpy(x->chaves[i].descricao, novaDescricao);
    TABM_escreve(resp, x, t);
    return;
}


void retiraPorTipo(char *tipo, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].tipo, tipo) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Tipo: %s\n", x->chaves[i].id, x->chaves[i].tipo);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }
    char tmp[20];
    TLSE_TR *p = listaRemocoes;
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }
    TLSE_TR *u = listaRemocoes;
    while(u){
        if (!TABM_busca(arq,u->info->id,t)) printf("o %ld id foi retirado corretamente.", u->info->id);
        else printf("o %ld id NAO foi retirado corretamente.", u->info->id);
    }
    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis do tipo %s.\n", tipo);
}


void retiraPorCEP(int cep, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (x->chaves[i].cep == cep) {
                printf("Marcando para remoção: imóvel ID: %ld, CEP: %d\n", x->chaves[i].id, x->chaves[i].cep);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis com CEP %d.\n", cep);
}


void retiraPorRua(char *rua, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].rua, rua) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Rua: %s\n", x->chaves[i].id, x->chaves[i].rua);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis na rua %s.\n", rua);
}


void retiraPorLatitude(char *latitude, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].latitude, latitude) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Latitude: %s\n", x->chaves[i].id, x->chaves[i].latitude);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis com latitude %s.\n", latitude);
}


void retiraPorLongitude(char *longitude, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].longitude, longitude) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Longitude: %s\n", x->chaves[i].id, x->chaves[i].longitude);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis com longitude %s.\n", longitude);
}


void retiraPorBairro(char *bairro, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].bairro, bairro) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Bairro: %s\n", x->chaves[i].id, x->chaves[i].bairro);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis no bairro %s.\n", bairro);
}


void procuraqto (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"quarto")){
        resp = strstr(aux2.descricao,"quarto");
    }
    else if (strstr(aux2.descricao,"Quarto")){
        resp = strstr(aux2.descricao,"Quarto");
    }
    else if (strstr(aux2.descricao,"QUARTO")){
        resp = strstr(aux2.descricao,"QUARTO");
    }
    else if (strstr(aux2.descricao,"quartos")){
        resp = strstr(aux2.descricao,"quartos");
    }
    else if (strstr(aux2.descricao,"Quartos")){
        resp = strstr(aux2.descricao,"Quartos");
    }
    else if (strstr(aux2.descricao,"QUARTOS")){
        resp = strstr(aux2.descricao,"QUARTOS");
    }
    char *respajustada = NULL;
    if (resp) {
        respajustada = resp - 2;
        int y = atoi(respajustada);
        if (y) printf("\n\ta residencia de id %ld tem %d quarto(s)", id, y);
    }
}

void procurabanheiro (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"banheiro")){
        resp = strstr(aux2.descricao,"banheiro");
    }
    else if (strstr(aux2.descricao,"Banheiro")){
        resp = strstr(aux2.descricao,"Banheiro");
    }
    else if (strstr(aux2.descricao,"BANHEIRO")){
        resp = strstr(aux2.descricao,"BANHEIRO");
    }
    else if (strstr(aux2.descricao,"banheiros")){
        resp = strstr(aux2.descricao,"banheiros");
    }
    else if (strstr(aux2.descricao,"Banheiros")){
        resp = strstr(aux2.descricao,"Banheiros");
    }
    else if (strstr(aux2.descricao,"BANHEIROS")){
        resp = strstr(aux2.descricao,"BANHEIROS");
    }
    char *respajustada = NULL;
    if (resp) {
        respajustada = resp - 2;
        int y = atoi(respajustada);
        if (y) printf("\n\ta residencia de id %ld tem %d banheiro(s)", id, y);
    }
}

void procuradorm (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"dormitório")){
        resp = strstr(aux2.descricao,"dormitório");
    }
    else if (strstr(aux2.descricao,"Dormitório")){
        resp = strstr(aux2.descricao,"Dormitório");
    }
    else if (strstr(aux2.descricao,"DORMITÓRIO")){
        resp = strstr(aux2.descricao,"DORMITÓRIO");
    }
    else if (strstr(aux2.descricao,"dormitórios")){
        resp = strstr(aux2.descricao,"dormitórios");
    }
    else if (strstr(aux2.descricao,"Dormitórios")){
        resp = strstr(aux2.descricao,"Dormitórios");
    }
    else if (strstr(aux2.descricao,"DORMITÓRIOS")){
        resp = strstr(aux2.descricao,"DORMITÓRIOS");
    }
    char *respajustada = NULL;
    if (resp) {
        respajustada = resp - 2;
        int y = atoi(respajustada);
        if (y) printf("\n\ta residencia de id %ld tem %d dormitorio(s)", id, y);
    }
}

void procuravaga (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"vaga")){
        resp = strstr(aux2.descricao,"vaga");
    }
    else if (strstr(aux2.descricao,"Vaga")){
        resp = strstr(aux2.descricao,"vaga");
    }
    else if (strstr(aux2.descricao,"VAGA")){
        resp = strstr(aux2.descricao,"VAGA");
    }
    else if (strstr(aux2.descricao,"vagas")){
        resp = strstr(aux2.descricao,"vagas");
    }
    else if (strstr(aux2.descricao,"Vagas")){
        resp = strstr(aux2.descricao,"Vagas");
    }
    else if (strstr(aux2.descricao,"VAGAS")){
        resp = strstr(aux2.descricao,"VAGAS");
    }
    char *respajustada = NULL;
    if (resp) {
        respajustada = resp - 2;
        int y = atoi(respajustada);
        if (y) printf("\n\ta residencia de id %ld tem %d vaga(s) para voce colocar seu(s) carro(s)", id, y);
    }
}

void procurasuite (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"suíte")){
        resp = strstr(aux2.descricao,"suíte");
    }
    else if (strstr(aux2.descricao,"Suíte")){
        resp = strstr(aux2.descricao,"Suíte");
    }
    else if (strstr(aux2.descricao,"SUÍTE")){
        resp = strstr(aux2.descricao,"SUÍTE");
    }
    else if (strstr(aux2.descricao,"suítes")){
        resp = strstr(aux2.descricao,"suítes");
    }
    else if (strstr(aux2.descricao,"Suítes")){
        resp = strstr(aux2.descricao,"Suítes");
    }
    else if (strstr(aux2.descricao,"SUÍTES")){
        resp = strstr(aux2.descricao,"SUÍTES");
    }
    char *respajustada = NULL;
    if (resp) {
        respajustada = resp - 2;
        int y = atoi(respajustada);
        if (y) printf("\n\ta residencia de id %ld tem %d suite(s)", id, y);
    }
}

void procuraamb (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"ambiente")){
        resp = strstr(aux2.descricao,"ambiente");
    }
    else if (strstr(aux2.descricao,"Ambiente")){
        resp = strstr(aux2.descricao,"Ambiente");
    }
    else if (strstr(aux2.descricao,"AMBIENTE")){
        resp = strstr(aux2.descricao,"AMBIENTE");
    }
    else if (strstr(aux2.descricao,"ambientes")){
        resp = strstr(aux2.descricao,"ambientes");
    }
    else if (strstr(aux2.descricao,"Ambientes")){
        resp = strstr(aux2.descricao,"Ambientes");
    }
    else if (strstr(aux2.descricao,"AMBIENTES")){
        resp = strstr(aux2.descricao,"AMBIENTES");
    }
    char *respajustada = NULL;
    if (resp) {
        respajustada = resp - 2;
        int y = atoi(respajustada);
        if (y) printf("\n\ta residencia de id %ld tem %d ambientes(s)", id, y);
    }
}

void procurametro (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"metrô")){
        printf("\n\ta residencia de id %ld fica proxima ao metro no bairro %s", id, aux2.bairro);
    }
    else if (strstr(aux2.descricao,"Metrô")){
        printf("\n\ta residencia de id %ld fica proxima ao metro no bairro %s", id, aux2.bairro);
    }
    else if (strstr(aux2.descricao,"METRÔ")){
        printf("\n\ta residencia de id %ld fica proxima ao metro no bairro %s", id, aux2.bairro);
    }
    else if (strstr(aux2.descricao,"metrôs")){
        printf("\n\ta residencia de id %ld fica proxima ao metro no bairro %s", id, aux2.bairro);
    }
    else if (strstr(aux2.descricao,"Metrôs")){
        printf("\n\ta residencia de id %ld fica proxima ao metro no bairro %s", id, aux2.bairro);
    }
    else if (strstr(aux2.descricao,"METRÔS")){
        printf("\n\ta residencia de id %ld fica proxima ao metro no bairro %s", id, aux2.bairro);
    }
}

void procurap24 (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"portaria 24 horas")){
        printf("\n\ta residencia de id %ld tem portaria 24 horas", id);
    }
}

void procuravenda (int t,char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strstr(x->chaves[i].descricao,"vende")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"Vende")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"VENDE")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"venda")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"Venda")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"VENDA")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
        }
        x =  arq2TABM(x->prox,t);
    }
    if (!resp) return;
    TLSE_TR *y = resp, *z;
    double maior = resp->info->preco_total, menor = resp->info->preco_total, troca;
    y = y->prox;
    while (y){
        if (y->info->preco_total > maior){
            maior = y->info->preco_total;
            z = y;
        }
        y = y->prox;
    }
    printf("\n\to imovel a venda mais caro eh o de id %ld, localizado no bairro %s, rua %s e numero %d, e vale %.2lf reais, com um metro quadrado no valor de %.2lf.",z->info->id,z->info->bairro,z->info->rua,z->info->numero,z->info->preco_total, z->info->preco_m2);
    y=resp->prox;
    while (y){
        if (y->info->preco_total < menor){
            menor = y->info->preco_total;
            z = y;
        }
        y = y->prox;
    }
    printf("\n\to imovel a venda mais barato eh o de id %ld, localizado no bairro %s, rua %s e numero %d, e vale %.2f reais, com um metro quadrado no valor de %.2f.",z->info->id,z->info->bairro,z->info->rua,z->info->numero,z->info->preco_total, z->info->preco_m2);
}

void procuraaluga (int t,char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strstr(x->chaves[i].descricao,"aluguel")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"Aluguel")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"ALUGUEL")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"alugar")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"Alugar")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"ALUGAR")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
        }
        x =  arq2TABM(x->prox,t);
    }
    if (!resp) return;
    TLSE_TR *y = resp, *z;
    double maior = resp->info->preco_total, menor = resp->info->preco_total, troca;
    y = y->prox;
    while (y){
        if (y->info->preco_total > maior){
            maior = y->info->preco_total;
            z = y;
        }
        y = y->prox;
    }
    printf("\n\to imovel alugando mais caro eh o de id %ld, localizado no bairro %s, rua %s e numero %d, e vale %.2lf reais, com um metro quadrado no valor de %.2lf.",z->info->id,z->info->bairro,z->info->rua,z->info->numero,z->info->preco_total, z->info->preco_m2);
    y=resp->prox;
    while (y){
        if (y->info->preco_total < menor){
            menor = y->info->preco_total;
            z = y;
        }
        y = y->prox;
    }
    printf("\n\to imovel alugando mais barato eh o de id %ld, localizado no bairro %s, rua %s e numero %d, e vale %.2f reais, com um metro quadrado no valor de %.2f.",z->info->id,z->info->bairro,z->info->rua,z->info->numero,z->info->preco_total, z->info->preco_m2);
}
