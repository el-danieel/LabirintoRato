#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void iniciar() {
    FILE *arquivo;
    arquivo = fopen("labirinto.txt", "r"); ///abre o arquivo
    if(arquivo == NULL) {
        printf("Erro! Não consegui abrir o arquivo de leitura");
        return;
    }
    char labirinto[14][9], linha[9];

    int i, j, posicao_inicial[2], saida[2];
    ///ler
    for (i=0; i<14; i++) {
        fgets(linha,126, arquivo);
        for (j=0; j<9; j++) {
            labirinto[i][j] = linha[j];
            if (labirinto[i][j] == 'R') {
                posicao_inicial[0] = i;
                posicao_inicial[1] = j;
            }
            else if (labirinto[i][j] == 'S') {
                saida[0] = i;
                saida[1] = j;
            }
        }
    }
    fclose(arquivo);

    ///printar
    for (i=0; i<14; i++) {
        for (j=0; j<9; j++) {
            printf("%c",labirinto[i][j]);
        }
        printf("\n");
    }

    srand(time(NULL));
    int pos_atual[2];
    pos_atual[0] = posicao_inicial[0];
    pos_atual[1] = posicao_inicial[1];

    int movimento = rand() % 4;
    switch(movimento) {

    case 0: ///esquerda
        if(labirinto[pos_atual[0]][pos_atual[1]-1] == '0') {
            labirinto[pos_atual[0]][pos_atual[1]-1] = 'R';
            labirinto[pos_atual[0]][pos_atual[1]] = '0';
        }
    break;
    case 1: ///cima
        if(labirinto[pos_atual[0]-1][pos_atual[1]] == '0') {
            labirinto[pos_atual[0]-1][pos_atual[1]] = 'R';
            labirinto[pos_atual[0]][pos_atual[1]] = '0';
        }
    break;
    case 2: ///direita
        if(labirinto[pos_atual[0]][pos_atual[1]+1] == '0') {
            labirinto[pos_atual[0]][pos_atual[1]+1] = 'R';
            labirinto[pos_atual[0]][pos_atual[1]] = '0';
        }
    break;
    case 3: ///baixo
        if(labirinto[pos_atual[0]+1][pos_atual[1]] == '0') {
            labirinto[pos_atual[0]+1][pos_atual[1]] = 'R';
            labirinto[pos_atual[0]][pos_atual[1]] = '0';
        }
    break;
    }
    printf("\n");

    for (i=0; i<14; i++) {
        for (j=0; j<9; j++) {
            printf("%c",labirinto[i][j]);
        }
        printf("\n");
    }

}

int main()
{
    iniciar();
    return 0;
}
