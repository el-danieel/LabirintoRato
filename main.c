#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "pilha.h"
#define esquerda 0
#define cima 1
#define direita 2
#define baixo 3

int verif_checkpoint() {

}

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
    Coords checkpoints[qtd_checkpoints], exit, atual;

    ///ler
    fgetc(arquivo);
    for (i=0; i<14; i++) {
        for (j=0; j<10; j++) {
            labirinto[i][j] = fgetc(arquivo);
            if (labirinto[i][j] == 'R') {
                checkpoints[0].x = i; /// posição inicial do rato
                checkpoints[0].y = j; /// é o primeiro checkpoint
            }
            else if (labirinto[i][j] == 'S') {
                exit.x = i; /// coordenadas
                exit.y = j; /// da saida
            }
        }
    }
    fclose(arquivo); ///fim da leitura do arquivo

    atual.x = checkpoints[0].x; /// posicao inicial e atribuida
    atual.y = checkpoints[0].y; /// a posicao atual do rato, no comeco


    Pilha pd_movimentos;    /// pilha de movimentos
    pdInit(&pd_movimentos); /// empilha valores como '0' '1', que se referem aos movimentos como definidos no inicio
    srand(time(NULL));      /// iniciando geracao de numero aleatorio
    int i_checkpoints = 0;  /// contagem dos checkpoints (inicia no 0,
                            /// se o rato chegar no proximo é incrementado, assim por diante

    while(atual.x != exit.x && atual.y != exit.y) { /// execucao do labirinto
                                                    /// roda ate o rato achar a saida

        int randomDirecao; ///variavel que recebe a direcao aleatoria
        do {
            randomDirecao = rand() % 4;
        } while(randomDirecao == pdTop); ///gera outra direcao caso a gerada seja igual a ultima (empilhada)
        int goLEFT = verif_esquerda(labirinto, &atual);                     /// verifica cada direcao
            if (goLEFT == 1) checkpoints[i_checkpoints].dirEsquerda = 1;    /// disponivel a partir da
            else checkpoints[i_checkpoints].dirEsquerda = 0;                /// posicao atual do rato
        int goUP = verif_cima(labirinto, &atual);
            if (goUP == 1) checkpoints[i_checkpoints].dirCima = 1;
            else checkpoints[i_checkpoints].dirCima = 0;
        int goRIGHT = verif_direita(labirinto, &atual);
            if (goRIGHT == 1) checkpoints[i_checkpoints].dirDireita = 1;
            else checkpoints[i_checkpoints].dirDireita = 0;
        int goDOWN = verif_baixo(labirinto, &atual);
            if (goDOWN == 1) checkpoints[i_checkpoints].dirBaixo = 1;
            else checkpoints[i_checkpoints].dirBaixo = 0;
        int dir_anterior = goLEFT + goUP + goDOWN + goRIGHT;                /// se houverem 2 caminhos, o rato explora normal
        int retrocede = -1;                                                 /// se houver apenas 1, ele deve retroceder (desempilhar)
        if(dir_anterior == 1) {                 ///bloco desempilhando
            retrocede = pdPop(&pd_movimentos);
            switch(retrocede) {         /// cada case o rato retrocede de onde veio
                case esquerda:          /// cada while o rato retrocede até a posição inicial
                    while(atual.x != checkpoints[i_checkpoints].x && atual.y != checkpoints[i_checkpoints].y) {
                        atual.y++;
                        labirinto[atual.x][atual.y] = 'R';
                        labirinto[atual.x][atual.y-1] = '0';
                        system("cls");
                        printa_labirinto(labirinto, 14, 10);
                        sleep(1);
                    }
                    checkpoints[i_checkpoints].dirEsquerda = 0;
                break;
                case cima:
                    while(atual.x != checkpoints[i_checkpoints].x && atual.y != checkpoints[i_checkpoints].y) {
                        atual.x++;
                        labirinto[atual.x][atual.y] = 'R';
                        labirinto[atual.x-1][atual.y] = '0';
                        system("cls");
                        printa_labirinto(labirinto, 14, 10);
                        sleep(1);
                    }
                    checkpoints[i_checkpoints].dirCima = 0;

                break;
                case direita:
                    while(atual.x != checkpoints[i_checkpoints].x && atual.y != checkpoints[i_checkpoints].y) {
                        atual.y--;
                        labirinto[atual.x][atual.y] = 'R';
                        labirinto[atual.x][atual.y+1] = '0';
                        system("cls");
                        printa_labirinto(labirinto, 14, 10);
                        sleep(1);
                    }
                    checkpoints[i_checkpoints].dirDireita = 0;
                break;
                case baixo:
                    while(atual.x != checkpoints[i_checkpoints].x && atual.y != checkpoints[i_checkpoints].y) {
                        atual.x--;
                        labirinto[atual.x][atual.y] = 'R';
                        labirinto[atual.x+1][atual.y] = '0';
                        system("cls");
                        printa_labirinto(labirinto, 14, 10);
                        sleep(1);
                    }
                    checkpoints[i_checkpoints].dirBaixo = 0;
                break;
            }
        }                           /// fim bloco desempilhando
                                    /// se nao for desempilhar, rato explora como abaixo:
        else {
            switch (randomDirecao) {    /// switch com comandos para cada direção gerada
                case esquerda:
                    if(goLEFT == 1 && checkpoints[i_checkpoints].dirEsquerda == 1) {
                        while(labirinto[atual.x][atual.y-1] != 'X') {   /// se o caminho tiver livre, anda o maximo possivel
                            atual.y--;                                  /// na direcao gerada
                            labirinto[atual.x][atual.y] = 'R';
                            labirinto[atual.x][atual.y+1] = '0';
                            pdPush(&pd_movimentos, esquerda);           /// e empilha a direcao seguida
                            goLEFT = verif_esquerda(labirinto, &atual); /// a cada iteracao
                            goUP = verif_cima(labirinto, &atual);       /// conta as direcoes disponiveis na nova posicao
                            goRIGHT = verif_direita(labirinto, &atual); /// se houver mais q na posicao interior,
                            goDOWN = verif_baixo(labirinto, &atual);    /// eh um checkpoint.
                            int dir_atual = goLEFT + goUP + goDOWN + goRIGHT;
                            if(dir_atual > dir_anterior) {
                                i_checkpoints++;                        /// incrementacao do indice de checkpoint
                                checkpoints[i_checkpoints] = atual;     /// coordenada de checkpoint salva
                            }
                            system("cls");
                            printa_labirinto(labirinto, 14, 10);        /// limpa a tela e printa o labirinto
                            sleep(1);                                   /// delay de 1 segundo
                        }                                               /// mesma coisa em cada Case
                    }
                break;
                case cima:
                    if(goUP == 1 && checkpoints[i_checkpoints].dirCima == 1) {
                        while(labirinto[atual.x-1][atual.y] != 'X') {
                            atual.x--;
                            labirinto[atual.x][atual.y] = 'R';
                            labirinto[atual.x+1][atual.y] = '0';
                            pdPush(&pd_movimentos, cima);
                            goLEFT = verif_esquerda(labirinto, &atual);
                            goUP = verif_cima(labirinto, &atual);
                            goRIGHT = verif_direita(labirinto, &atual);
                            goDOWN = verif_baixo(labirinto, &atual);
                            int dir_atual = goLEFT + goUP + goDOWN + goRIGHT;
                            if(dir_atual > dir_anterior) {
                                i_checkpoints++;
                                checkpoints[i_checkpoints] = atual;
                            }
                            system("cls");
                            printa_labirinto(labirinto, 14, 10);
                            sleep(1);
                        }
                    }
                break;
                case direita:
                    if(goRIGHT == 1 && checkpoints[i_checkpoints].dirDireita == 1) {
                        while(labirinto[atual.x][atual.y+1] != 'X') {
                            atual.y++;
                            labirinto[atual.x][atual.y] = 'R';
                            labirinto[atual.x][atual.y-1] = '0';
                            pdPush(&pd_movimentos, direita);
                            goLEFT = verif_esquerda(labirinto, &atual);
                            goUP = verif_cima(labirinto, &atual);
                            goRIGHT = verif_direita(labirinto, &atual);
                            goDOWN = verif_baixo(labirinto, &atual);
                            int dir_atual = goLEFT + goUP + goDOWN + goRIGHT;
                            if(dir_atual > dir_anterior) {
                                i_checkpoints++;
                                checkpoints[i_checkpoints] = atual;
                            }
                            system("cls");
                            printa_labirinto(labirinto, 14, 10);
                            sleep(1);
                        }
                    }
                break;
                case baixo:
                    if(goDOWN == 1 && checkpoints[i_checkpoints].dirBaixo == 1) {
                        while(labirinto[atual.x+1][atual.y] != 'X') {
                            atual.x++;
                            labirinto[atual.x][atual.y] = 'R';
                            labirinto[atual.x-1][atual.y] = '0';
                            pdPush(&pd_movimentos, baixo);
                            goLEFT = verif_esquerda(labirinto, &atual);
                            goUP = verif_cima(labirinto, &atual);
                            goRIGHT = verif_direita(labirinto, &atual);
                            goDOWN = verif_baixo(labirinto, &atual);
                            int dir_atual = goLEFT + goUP + goDOWN + goRIGHT;
                            if(dir_atual > dir_anterior) {
                                i_checkpoints++;
                                checkpoints[i_checkpoints] = atual;
                            }
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
