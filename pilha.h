typedef int tipoNodo;
struct nodo {
    tipoNodo item;
    struct nodo *prox;
};
typedef struct nodo *Ptr;
typedef tipoNodo tipoPilha;
typedef Ptr Pilha;

typedef struct {
    int x, y, dirEsquerda, dirCima, dirDireita, dirBaixo;
} Coords;

void pdInit(Pilha *); ///inicializa a pilha dinâmica,

int pdIsEmpty(Pilha); ///teste de pilha vazia

void pdPush(Pilha *, tipoPilha); ///insere valor no topo da pilha

int pdTop(Pilha); ///retorna o topo da pilha, sem alterá-lo

int pdPop(Pilha *); ///retorna o topo da pilha, removendo-o da pilha
