/*
Considere o grafo a seguir, que representa seguidores no
Instagram. Cada pessoa tem nome e idade (nome é o id do
vértice). Uma aresta (v1, v2) significa que v1 segue v2 no
Instagram.

Q1- Quantas pessoas uma determinada pessoa segue? int numero_seguidos(TGrafo *g, char *nome);

Q2- Quem são os seguidores de uma determinada pessoa? (função imprime os nomes dos seguidores, caso a flag imprime seja
    True, e retorna quantidade de seguidores) int seguidores(TGrafo *vertice, char *nome, int imprime);

Q3- Quem é a pessoa mais popular? (tem mais seguidores) TGrafo *mais_popular(TGrafo *g);

Q4- 4. Quais são as pessoas que só seguem pessoas mais velhas do que ela própria? (função imprime os nomes das pessoas, caso a
    flag imprime seja True, e retorna quantidade de pessoas) int segue_mais_velho(TGrafo *g, int imprime);
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct vizinhos_p{
    char nome[10];
    struct vizinhos_p* prox_viz;
}TVIZP;

typedef struct grafo_p{
    char nome[10];
    int idade;
    struct grafo_p* prox;
    TVIZP* vizinhos;
}TGP;
//----------------------------------------------------------
//          Funções gerais
//----------------------------------------------------------

TGP* insere(TGP* g, char* n, int idade) {
    if (!g) {
        TGP* novo = (TGP*)malloc(sizeof(TGP));
        novo->idade = idade;
        strcpy(novo->nome, n);
        novo->prox = NULL;
        novo->vizinhos = NULL;
        return novo;
    }
    g->prox = insere(g->prox, n, idade);
    return g;
}


TGP* busca(TGP* g, char* nome){
    if(!g) return NULL;
    if(strcmp(g->nome,nome) == 0 ) return g;
    return busca(g->prox,nome);
}

void libera_aresta(TVIZP* v){
    if(!v) return;
    libera_aresta(v->prox_viz);
    free(v);
}

void libera(TGP* g) {
    if (!g) return;
    libera(g->prox);
    libera_aresta(g->vizinhos);
    free(g);
}


TGP* cria_aresta(TGP* g, char* x, char* y) {
    TGP* src = busca(g, x);
    if (!src) {
        printf("Vertice %s não encontrado.\n", x);
        return g;
    }
    TVIZP* novo = (TVIZP*)malloc(sizeof(TVIZP));
    if (!novo) {
        printf("Erro ao alocar memória para a aresta.\n");
        return g;
    }
    strcpy(novo->nome, y);
    novo->prox_viz = src->vizinhos;
    src->vizinhos = novo;
    return g;
}

void imp_rec(TGP *g){
    if(g){
        printf("\n\t%s: ", g->nome);
        TVIZP *v = g->vizinhos;
        while(v){
            printf(" %s -->", v->nome);
            v = v->prox_viz;
        }
        printf("\n");
        imp_rec(g->prox);
    }
}
//--------------------------------------------------------
//      Funções para Q1
//--------------------------------------------------------

int numero_seguidos(TGP *g, char *nome){
    TGP *aux = busca(g,nome);
    if (!aux) return 0;
    int seguindo = 0;
    TVIZP *aux2 = aux->vizinhos;
    while (aux2){
        seguindo++;
        aux2 = aux2 -> prox_viz;
    }
    return seguindo;
}

//-------------------------------------------------------
//      Funções para Q2
//-------------------------------------------------------

int seguidores(TGP *vertice, char *nome, int imprime){
    int x = 0;
    while (vertice){
        TVIZP *aux = vertice->vizinhos;
        while(aux){
            if (strcmp(aux->nome,nome)==0){
                x++;
                printf("\t%s\n", vertice->nome);
                break;
            }
            else aux = aux->prox_viz;
        }
        vertice = vertice->prox;
    }
    return x;
}

//-------------------------------------------------------
//      Funções para Q3
//-------------------------------------------------------

int seguidores2(TGP *vertice, char *nome, int imprime){
    int x = 0;
    while (vertice){
        TVIZP *aux = vertice->vizinhos;
        while(aux){
            if (strcmp(aux->nome,nome)==0){
                x++;
                break;
            }
            else aux = aux->prox_viz;
        }
        vertice = vertice->prox;
    }
    return x;
}

TGP *mais_popular(TGP *g){
    if (!g) return NULL;
    int y = seguidores2(g,g->nome,0),x;
    TGP *resp = g;
    g=g->prox;
    while (g){
        x = seguidores2(g,g->nome,0);
        if (x>y) {
            y = x;
            resp = g;
        }
        g = g->prox;
    }
    return resp;
}

//-------------------------------------------------------
//      Funções para Q4
//-------------------------------------------------------

int segue_mais_velho(TGP *g, int imprime){
    if (!g) return 0;
    int x = 0;
    TGP *gaux = g;
    TVIZP *aux = NULL;
    while (g){
        aux = g->vizinhos;
        while (aux){
            TGP *y = busca(gaux, aux->nome);
            if(y && y->idade <= g->idade){
                break;
            }
            else aux = aux->prox_viz;
            if (!aux){
                printf("\t%s\n", g->nome);
                x++;
            }
        }
        g = g->prox;
    }
    return x;
}

//---------------------------------------------------------
int main(void){
    int opcao,ver,id,a,b;
    char n[10], x[10], y[10];
    TGP* grafo = NULL, *resp = NULL;
    do{
        printf("\n\t0 - Sair\n\t1 - Criar perfil\n\t2 - Seguir alguem\n\t3 - Imprimir Instagram\n\t4 - Verficar quantas pessoas alguem segue\n\t5 - Verificar quem sao os seguidores\n\t6 - Verificar quem eh a pessoa mais popular\n\t7 - Verificar quem sao as pessoas que so seguem outras mais velhas que ela");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                printf("\n\tDigite o nome da pessoa que esta criando o perfil: ");
                scanf("%s", n);
                printf("\n");
                printf("\n\tDigite a idade da pessoa que esta criando o perfil: ");
                scanf("%d", &id);
                grafo = insere(grafo,n,id);
                break;

            case 2:
                printf("\n\tDigite a pessoa que vai seguir alguem: ");
                scanf("%s", x);
                printf("\n");
                printf("\n\tDigite quem a pessoa quer seguir: ");
                scanf("%s", y);
                printf("\n");
                grafo = cria_aresta(grafo,x,y);
                break;

            case 3:
                printf("\n\tO grafo eh: ");
                imp_rec(grafo);
                printf("\n");
                break;

            case 4:
                printf("\n\tDigite a pessoa que voce quer saber quantas outras ela segue: ");
                scanf("%s", x);
                printf("\n");
                a = numero_seguidos(grafo,x);
                printf("\n\tEsta pessoa segue %d pessoa(s): ",a);
                printf("\n");
                break;

            case 5:
                printf("\n\tDigite a pessoa que voce quer saber quem sao os seguidores: ");
                scanf("%s", x);
                printf("\n");
                printf("\n\tOs seguidores sao: ");
                a = seguidores(grafo,x,0);
                printf("\n\t o que totaliza %d seguidores", a);
                printf("\n");
                break;

            case 6:
                resp = mais_popular(grafo);
                printf("\n");
                if(resp) printf("\ta pessoa mais popular eh o(a) %s com %d seguidores\t", resp->nome, seguidores(grafo,resp->nome,0));
                break;

            case 7:
                printf("\n\t a(s) pessoa(s) que so segue(m) outras mais velhas que ela sao:\n");
                b = segue_mais_velho(grafo,0);
                if (b) printf("\to que totaliza %d pessoas", b);
                break;

            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    libera(grafo);
    libera(resp);
    return 0;
}