#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"
#define esquerda 0
#define cima 1
#define direita 2
#define baixo 3

int verif_checkpoint() {

}

int verif_esquerda(char Lab[][9], Coords *atual) {
    if(Lab[atual->x][atual->y-1] == '0') return 1;
    else return 0;
}
int verif_cima(char Lab[][9], Coords *atual) {
    if(Lab[atual->x-1][atual->y] == '0') return 1;
    else return 0;
}
int verif_direita(char Lab[][9], Coords *atual) {
    if(Lab[atual->x][atual->y+1] == '0') return 1;
    else return 0;
}
int verif_baixo(char Lab[][9], Coords *atual) {
    if(Lab[atual->x+1][atual->y] == '0') return 1;
    else return 0;
}
void printa_labirinto(char Lab[][9], int Linhas, int Colunas) {
    int i, j;
    for (i=0; i<Linhas; i++) {
        for (j=0; j<Colunas; j++) {
            printf("%c",Lab[i][j]);
        }
    }
}
void achou_saida() {
    printf(".");
}
int main()
{
    FILE *arquivo;
    arquivo = fopen("labirinto.txt", "r"); ///abre o arquivo
    if(arquivo == NULL) {
        printf("Erro! Não consegui abrir o arquivo de leitura");
        return;
    }
    char labirinto[14][9];

    int i, j;
    Coords checkpoint, exit, atual;
    ///ler
    for (i=0; i<14; i++) {
        fgetc(arquivo);
        for (j=0; j<9; j++) {
            labirinto[i][j] = fgetc(arquivo);
            if (labirinto[i][j] == 'R') {
                checkpoint.x = i;
                checkpoint.y = j;
            }
            else if (labirinto[i][j] == 'S') {
                exit.x = i;
                exit.y = j;
            }
        }
    }
    fclose(arquivo);

    ///printar
    printa_labirinto(labirinto, 14, 9);

    atual.x = checkpoint.x;
    atual.y = checkpoint.y;

    Pilha teste;
    pdInit(&teste);
    pdPush(&teste, 2);
    printf("\n%i\n", pdTop(teste));

    printf("\n%i\n", verif_esquerda(labirinto, &atual));
    printf("\n%i\n", verif_cima(labirinto, &atual));
    printf("\n%i\n", verif_direita(labirinto, &atual));
    printf("\n%i\n", verif_baixo(labirinto, &atual));


    /*while(atual.x != exit.x && atual.y != exit.y) {
        ///ordem: ESQUERDA -> CIMA -> DIREITA -> BAIXO
        if(labirinto[atual.x][atual.y-1] == '0') { ///VERIFICA SE DÁ PRA IR PRA ESQUERDA
            //Push(&p_movimentos, esquerda);
            atual.y--;
            labirinto[atual.x][atual.y] = 'R';
            labirinto[atual.x][atual.y+1] = '0';
        }
        else if(labirinto[atual.x-1][atual.y] == '0') { ///VERIFICA SE DÁ PRA IR PRA CIMA
            //Push(&p_movimentos, cima);
            atual.x--;
            labirinto[atual.x][atual.y] = 'R';
            labirinto[atual.x+1][atual.y] = '0';
        }
        else if(labirinto[atual.x][atual.y+1] == '0') { ///VERIFICA SE DÁ PRA IR PRA DIREITA
            //Push(&p_movimentos, direita);
            atual.y++;
            labirinto[atual.x][atual.y] = 'R';
            labirinto[atual.x][atual.y-1] = '0';
        }
        else if(labirinto[atual.x+1][atual.y] == '0') { ///VERIFICA SE DÁ PRA IR PRA BAIXO
            //Push(&p_movimentos, baixo);
            atual.x++;
            labirinto[atual.x][atual.y] = 'R';
            labirinto[atual.x-1][atual.y] = '0';
        }
        else if(labirinto[atual.x+1][atual.y] == 'S') {
            achou_saida();
        }
    }*/
    return 0;
}
