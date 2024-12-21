/*
função que, dadas duas árvores deste tipo, testa se estas árvores são iguais. A
função retorna um se elas são iguais e zero, caso contrário. A função deve
obedecer ao seguinte protótipo: int igual (TARVB* a1, TARVB* a2)
*/
#include "TARVB.c"

int igual (TARVB* a1, TARVB* a2){
    if (!a1 && !a2) return 1;
    if (!a1 || !a2) return 0;
    if (a1->nchaves != a2->nchaves) return 0;
    for (int i=0;i<a1->nchaves;i++) if (a1->chave[i] != a2->chave[i]) return 0;
    for (int j=0;j<=a1->nchaves;j++) return igual(a1->filho[j],a2->filho[j]);
    return 1;
}

int main(void){
    TARVB *arvore = TARVB_Inicializa();
    TARVB *segunda = TARVB_Inicializa();
    int t, x;
    printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
    scanf("%d", &t);
    if(t < 2) t = 2;
    int num = 0, from, to;
    while(num != -1){
        printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
        scanf("%d", &num);
        if(num == -9){
            scanf("%d", &from);
            arvore = TARVB_Retira(arvore, from, t);
            TARVB_Imprime(arvore);
        }
        else if(num == -1){
            printf("\n");
            TARVB_Imprime(arvore);
            break;
        }
        else if(!num){
            printf("\n");
            TARVB_Imprime(arvore);
        }
        else arvore = TARVB_Insere(arvore, num, t);
        printf("\n\n");
    }
    t = 0;
    x = 0;;
    printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
    scanf("%d", &t);
    if(t < 2) t = 2;
    num = 0, from, to;
    while(num != -1){
        printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
        scanf("%d", &num);
        if(num == -9){
            scanf("%d", &from);
            segunda = TARVB_Retira(segunda, from, t);
            TARVB_Imprime(segunda);
        }
        else if(num == -1){
            printf("\n");
            TARVB_Imprime(segunda);
            break;
        }
        else if(!num){
            printf("\n");
            TARVB_Imprime(segunda);
        }
        else segunda = TARVB_Insere(segunda, num, t);
        printf("\n\n");
    }
    int resp = igual(arvore,segunda);
    if(resp)printf("As arvores SAO IGUAIS!");
    else printf("As arvores NAO SAO iguais");
    TARVB_Libera(arvore);
    TARVB_Libera(segunda);
    return 0;
}