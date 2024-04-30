#define MAX 100
typedef int tipoPilha;
typedef struct {
    tipoPilha topo; ///define o �ndice do tipo da pilha
    int itens[MAX]; ///vetor com os itens da pilha
} Pilha;

typedef struct {
    int x, y, visited;
} Coords;

void Init(Pilha *); ///inicializa a pilha

int IsEmpty(Pilha); ///teste de pilha vazia

int IsFull(Pilha); ///teste de pilha cheia

void Push(Pilha *, int); ///insere valor no topo da pilha

int Top(Pilha *); ///retorna o topo da pilha, sem alter�-lo

int Pop(Pilha *P); ///retorna o topo da pilha, removendo-o da pilha
