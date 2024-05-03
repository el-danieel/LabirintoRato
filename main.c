#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "pilha.h"
#define ESQUERDA 0
#define CIMA 1
#define DIREITA 2
#define BAIXO 3

int verif_esquerda(char Lab[][10], Coords *atual) { /// verificar se o bloco à esquerda é caminho livre ou parede
    if(Lab[atual->x][atual->y-1] == '0') return 1;  /// retorna 1 se for caminho livre
    else return 0;                                  /// retorna 0 se for parede
}                                                   /// se aplica para os outros também
int verif_cima(char Lab[][10], Coords *atual) {
    if(Lab[atual->x-1][atual->y] == '0') return 1;
    else return 0;
}
int verif_direita(char Lab[][10], Coords *atual) {
    if(Lab[atual->x][atual->y+1] == '0') return 1;
    else return 0;
}
int verif_baixo(char Lab[][10], Coords *atual) {
    if(Lab[atual->x+1][atual->y] == '0') return 1;
    else return 0;
}
void printa_labirinto(char Lab[][10], int Linhas, int Colunas) { ///printa o labirinto.
    int i, j;
    for (i=0; i<Linhas; i++) {
        for (j=0; j<Colunas; j++) {
            putchar(Lab[i][j]);
        }
    }
}
int main()
{
    FILE *arquivo;                                              ///inicio da leitura do arquivo
    arquivo = fopen("labirinto.txt", "r"); ///abre o arquivo
    if(arquivo == NULL) {
        printf("Erro! Não consegui abrir o arquivo de leitura");
    }
    char labirinto[14][10];

    int i, j, qtd_checkpoints = 4;
    Coords init, exit, atual;

    ///ler
    fgetc(arquivo);
    for (i=0; i<14; i++) {
        for (j=0; j<10; j++) {
            labirinto[i][j] = fgetc(arquivo);
            if (labirinto[i][j] == 'R') {
                init.x = i; /// posição inicial do rato
                init.y = j;
            }
            else if (labirinto[i][j] == 'S') {
                exit.x = i; /// coordenadas
                exit.y = j; /// da saida
            }
        }
    }
    fclose(arquivo); ///fim da leitura do arquivo

    atual.x = init.x; /// posicao inicial e atribuida
    atual.y = init.y; /// a posicao atual do rato, no comeco


    Pilha pd_movimentos;    /// pilha de movimentos
    pdInit(&pd_movimentos); /// empilha valores como '0' '1', que se referem aos movimentos como definidos no inicio
    srand(time(NULL));      /// iniciando geracao de numero aleatorio
    int qtd_movimentos=0;  /// contagem dos checkpoints (inicia no 0,
                            /// se o rato chegar no proximo é incrementado, assim por diante

    while(atual.x != exit.x && atual.y != exit.y) { /// execucao do labirinto
                                                    /// roda ate o rato achar a saida

        int randomDirecao; ///variavel que recebe a direcao aleatoria
        randomDirecao = rand() % 4; ///gera outra direcao caso a gerada seja igual a ultima (empilhada)
        int goLEFT = verif_esquerda(labirinto, &atual);                     /// verifica cada direcao
        int goUP = verif_cima(labirinto, &atual);                           /// disponivel a partir da
        int goRIGHT = verif_direita(labirinto, &atual);                     /// posicao atual do rato
        int goDOWN = verif_baixo(labirinto, &atual);
        int dir_anterior = goLEFT + goUP + goDOWN + goRIGHT;                /// se houverem 2 caminhos, o rato explora normal
        tipoPilha retrocede = -1;                                                 /// se houver apenas 1, ele deve retroceder (desempilhar)
        if(dir_anterior == 0) {
            while(qtd_movimentos != 0) {
                if(pdIsEmpty(pd_movimentos) == 0) retrocede = pdPop(&pd_movimentos);
                switch(retrocede) {
                    case ESQUERDA:
                        atual.y++;
                        labirinto[atual.x][atual.y] = 'R';
                        if(labirinto[atual.x][atual.y-1] == 'I')  labirinto[atual.x][atual.y-1] = 'I';
                        else if (labirinto[atual.x][atual.y-1] == 'C') labirinto[atual.x][atual.y-1] = 'C';
                        else labirinto[atual.x][atual.y-1] = '#';
                        system("cls");
                        printa_labirinto(labirinto, 14, 10);
                        sleep(1);
                        qtd_movimentos--;
                    break;
                    case CIMA:
                        atual.x++;
                        labirinto[atual.x][atual.y] = 'R';
                        if(labirinto[atual.x-1][atual.y] == 'I')  labirinto[atual.x-1][atual.y] = 'I';
                        else if (labirinto[atual.x-1][atual.y] == 'C') labirinto[atual.x-1][atual.y] = 'C';
                        else labirinto[atual.x-1][atual.y] = '#';
                        system("cls");
                        printa_labirinto(labirinto, 14, 10);
                        sleep(1);
                        qtd_movimentos--;
                    break;
                    case DIREITA:
                        atual.y--;
                        labirinto[atual.x][atual.y] = 'R';
                        if(labirinto[atual.x][atual.y+1] == 'I')  labirinto[atual.x][atual.y+1] = 'I';
                        else if (labirinto[atual.x][atual.y+1] == 'C') labirinto[atual.x][atual.y+1] = 'C';
                        else labirinto[atual.x][atual.y+1] = '#';
                        system("cls");
                        printa_labirinto(labirinto, 14, 10);
                        sleep(1);
                        qtd_movimentos--;
                    break;
                    case BAIXO:
                        atual.x--;
                        labirinto[atual.x][atual.y] = 'R';
                        if(labirinto[atual.x+1][atual.y] == 'I')  labirinto[atual.x+1][atual.y] = 'I';
                        else if (labirinto[atual.x+1][atual.y] == 'C') labirinto[atual.x+1][atual.y] = 'C';
                        else labirinto[atual.x+1][atual.y] = '#';
                        system("cls");
                        printa_labirinto(labirinto, 14, 10);
                        sleep(1);
                        qtd_movimentos--;
                    break;
                }
            }
        }                           /// fim bloco desempilhando
                                    /// se nao for desempilhar, rato explora como abaixo:
        else {
            switch (randomDirecao) {    /// switch com comandos para cada direção gerada
                case ESQUERDA:
                    if(goLEFT == 1) {
                        while(labirinto[atual.x][atual.y-1] != 'X' && labirinto[atual.x][atual.y-1] != '#') {
                            qtd_movimentos++;
                            if(atual.x == init.x && atual.y == init.y) labirinto[atual.x][atual.y] = 'I';
                            if(verif_cima(labirinto, &atual) || verif_baixo(labirinto, &atual)) {
                                    labirinto[atual.x][atual.y] = 'C';
                                    qtd_movimentos = 1;
                            }
                            atual.y--;
                            labirinto[atual.x][atual.y] = 'R';
                            if(labirinto[atual.x][atual.y+1] == 'I')  labirinto[atual.x][atual.y+1] = 'I';
                            else if (labirinto[atual.x][atual.y+1] == 'C') labirinto[atual.x][atual.y+1] = 'C';
                            else labirinto[atual.x][atual.y+1] = '#';
                            pdPush(&pd_movimentos, ESQUERDA);
                            system("cls");
                            printa_labirinto(labirinto, 14, 10);
                            sleep(1);
                        }
                    }
                break;
                case CIMA:
                    if(goUP == 1) {
                        while(labirinto[atual.x-1][atual.y] != 'X' && labirinto[atual.x-1][atual.y] != '#') {
                            qtd_movimentos++;
                            if(atual.x == init.x && atual.y == init.y) labirinto[atual.x][atual.y] = 'I';
                            if(verif_esquerda(labirinto, &atual) || verif_direita(labirinto, &atual)) {
                                    labirinto[atual.x][atual.y] = 'C';
                                    qtd_movimentos = 1;
                            }
                            atual.x--;
                            labirinto[atual.x][atual.y] = 'R';
                            if(labirinto[atual.x+1][atual.y] == 'I') labirinto[atual.x+1][atual.y] = 'I';
                            else if (labirinto[atual.x+1][atual.y] == 'C') labirinto[atual.x+1][atual.y] = 'C';
                            else labirinto[atual.x+1][atual.y] = '#';
                            pdPush(&pd_movimentos, CIMA);
                            system("cls");
                            printa_labirinto(labirinto, 14, 10);
                            sleep(1);
                        }
                    }
                break;
                case DIREITA:
                    if(goRIGHT == 1) {
                        while(labirinto[atual.x][atual.y+1] != 'X' && labirinto[atual.x][atual.y+1] != '#'){
                            qtd_movimentos++;
                            if(atual.x == init.x && atual.y == init.y) labirinto[atual.x][atual.y] = 'I';
                            if(verif_cima(labirinto, &atual) || verif_baixo(labirinto, &atual)) { /// DEFINIÇÃO DE CHECKPOINT APENAS A CADA ITERAÇÃO
                                    labirinto[atual.x][atual.y] = 'C';                            /// SEM ITERAÇÃO, SEM CHECKPOINT
                                    qtd_movimentos = 1;                                           /// TA BUGANDO NA LINHA 6, COLUNA 7
                            }                                                                     /// POIS ELE NAO ANDAR JA Q A PROXIMA EH PAREDE
                            atual.y++;                                                            /// FAZER VERIFICACAO DE CHECKPOINT ANTES DA ITERACAO
                            labirinto[atual.x][atual.y] = 'R';                                    /// (SE EH Q EH POSSIVEL) AMANHA VEJO ISSO !
                            if(labirinto[atual.x][atual.y-1] == 'I')  labirinto[atual.x][atual.y-1] = 'I';
                            else if (labirinto[atual.x][atual.y-1] == 'C') labirinto[atual.x][atual.y-1] = 'C';
                            else labirinto[atual.x][atual.y-1] = '#';
                            pdPush(&pd_movimentos, DIREITA);
                            system("cls");
                            printa_labirinto(labirinto, 14, 10);
                            sleep(1);
                        }
                    }
                break;
                case BAIXO:
                    if(goDOWN == 1) {
                        while(labirinto[atual.x+1][atual.y] != 'X' && labirinto[atual.x+1][atual.y] != '#') {
                            qtd_movimentos++;
                            if(atual.x == init.x && atual.y == init.y) labirinto[atual.x][atual.y] = 'I';
                            if(verif_esquerda(labirinto, &atual) || verif_direita(labirinto, &atual)) {
                                    labirinto[atual.x][atual.y] = 'C';
                                    qtd_movimentos = 1;
                            }
                            atual.x++;
                            labirinto[atual.x][atual.y] = 'R';
                            if(labirinto[atual.x-1][atual.y] == 'I')  labirinto[atual.x-1][atual.y] = 'I';
                            else if (labirinto[atual.x-1][atual.y] == 'C') labirinto[atual.x-1][atual.y] = 'C';
                            else labirinto[atual.x-1][atual.y] = '#';
                            pdPush(&pd_movimentos, BAIXO);
                            system("cls");
                            printa_labirinto(labirinto, 14, 10);
                            sleep(1);
                        }
                    }
                break;
            }
        }
    }
    return 0;
}
