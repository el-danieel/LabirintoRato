#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void pdInit(Pilha *Topo) {
    *Topo = NULL;
}

int pdIsEmpty(Pilha Topo) {
    return (Topo == NULL);
}

void pdPush(Pilha *Topo, tipoPilha x){
    Pilha N;
    if((N=(Pilha)malloc(sizeof(struct nodo)))== NULL){
        puts("Erro na alocação de memória\n");
        exit(1);
    }
    N->item = x;
    N->prox = *Topo;
    *Topo = N;
}

tipoPilha pdTop(Pilha Topo) {
    if(pdIsEmpty(Topo)){
        puts("Erro: Pilha Vazia\n");
        exit(1);
    }
    return Topo->item;
}

int pdPop(Pilha *Topo) {
    Pilha N;
    tipoPilha x = pdTop(*Topo);
    N = *Topo;
    *Topo = N->prox;
    free(N);
    return x;
}
