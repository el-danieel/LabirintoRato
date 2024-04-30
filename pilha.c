#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void Init(Pilha *P) {
    /**
    INICIANDO A PILHA
    ►  O valor do topo varia entre 0 e MAX-1
    ►  A pilha está vazia ao iniciar
    ►  O valor inicial do topo é -1
    ►  O valor é passado por referência para garantir a alteração
       da variável no programa principal
    */
    P->topo = -1; //P é uma variável de pilha e a seta -> acessa o topo e o altera
    // -> = altera (P->topo)
    // . = lê      (P.topo)
}

int IsEmpty(Pilha P) {
    //Teste de pilha vazia
    return (P.topo == -1); //Com a pilha vazia, o topo é igual a -1. Logo, caso a comparação seja verdadeira,
                           //vai retornar verdadeiro (1). Caso contrário, retorna falso (0)
}

int IsFull(Pilha P) {
    //Teste de pilha cheia
    //Compara o topo atual da pilha com seu limite (99). Caso o topo seja 99,
    //a comparação é verdadeira e o retorno será (1). Caso contrário, o retorno será (0)
    return (P.topo == MAX-1);
}

void Push(Pilha *P, int x){
    /**
    ► É necessário verificar se há espaço na pilha
    ► O próximo elemento fica na posição topo+1
    ► O tratamento de erros força o encerramento do programa
    */
    if(IsFull(*P)) {
        printf("Estouro da pilha!\n");
        exit(1); //Provoca a saída do programa
    }
    P->itens[++(P->topo)] = x; //incrementa o topo e guarda 'x' na nova posição
                               //itens e topo estão com -> pois tem seus valores alterados
}

int Top(Pilha *P) {
    /**
    ► Essa função NÃO altera o estado da pilha
    ► Apenas retorna o valor do elemento do topo da pilha
    */
    if(IsEmpty(*P)) {
        printf("A pilha está vazia!\n");
        return -1;
    }
    return P->itens[P->topo];
}

int Pop(Pilha *P) {
    if(IsEmpty(*P)) {
        printf("A pilha está vazia!\n");
        exit(1);
        }
    return P->itens[P->topo--];
}
