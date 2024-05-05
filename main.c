#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "pilha.h"
#define TAM_MAX 20
#define ESQUERDA 0
#define CIMA 1
#define DIREITA 2
#define BAIXO 3

int verif_direcao(char **Lab, int x, int y, int direcao) {
    if(direcao == ESQUERDA) y--;
    else if (direcao == CIMA) x--;
    else if (direcao == DIREITA) y++;
    else x++;
    if(Lab[x][y] != 'X' && Lab[x][y] != '#') return 1;
    else return 0;
}

void printa_labirinto(char **Lab, int Linhas, int Colunas) { ///printa o labirinto.
    int i, j;
    for (i=0; i<Linhas; i++) {
        for (j=0; j<Colunas; j++) {
            printf("%c", Lab[i][j]);
        }
        printf("\n");
    }
    sleep(1);
}

void rato_anda(char **labirinto, Coords *atual, Coords *init, Coords *saida, int direcao, int linhas, int colunas) {
    int x_anterior = atual->x, y_anterior = atual->y;
    if(direcao == ESQUERDA) atual->y--;
    else if(direcao == CIMA) atual->x--;
    else if(direcao == DIREITA) atual->y++;
    else atual->x++;
    verif_saida(atual->x, atual->y, saida->x, saida->y);
        if(verif_checkpoint(labirinto, atual->x, atual->y) == 1) {
            labirinto[atual->x][atual->y] = 'C';
            printf("\nO RATO ACHOU UM CHECKPOINT!\n");
            sleep(1);
        }
        if (labirinto[x_anterior][y_anterior] == 'C') labirinto[x_anterior][y_anterior] = 'C';
        else if (labirinto[x_anterior][y_anterior] == labirinto[init->x][init->y]) labirinto[x_anterior][y_anterior] = '0';
        else labirinto[x_anterior][y_anterior] = '#';
        if (labirinto[atual->x][atual->y] != 'C') labirinto[atual->x][atual->y] = 'R';

        system("cls");
        printf("ESQUERDA = %i\n", ESQUERDA);
        printf("CIMA = %i\n", CIMA);
        printf("DIREITA = %i\n", DIREITA);
        printf("BAIXO = %i\n", BAIXO);
        printf("\nO RATO ANDOU PARA %i!\n", direcao);
        printa_labirinto(labirinto, linhas, colunas);

}

void rato_volta(char **labirinto, Coords *atual, int direcao, int linhas, int colunas) {
    int x_anterior = atual->x, y_anterior = atual->y;
    if(direcao == ESQUERDA) atual->y++;
    else if(direcao == CIMA) atual->x++;
    else if(direcao == DIREITA) atual->y--;
    else atual->x--;
    if(labirinto[atual->x][atual->y] == 'C') labirinto[atual->x][atual->y] = 'C'; ///para manter o C no mapa
    else labirinto[atual->x][atual->y] = 'R';
    if (labirinto[x_anterior][y_anterior] == 'C') labirinto[x_anterior][y_anterior] = 'C';
    else labirinto[x_anterior][y_anterior] = '#';
    system("cls");
    printf("ESQUERDA = %i\n", ESQUERDA);
    printf("CIMA = %i\n", CIMA);
    printf("DIREITA = %i\n", DIREITA);
    printf("BAIXO = %i\n", BAIXO);
    printf("\nO RATO VOLTOU PARA %i!\n", direcao);
    printa_labirinto(labirinto, linhas, colunas);
}

int verif_checkpoint(char **labirinto, int x, int y) {
    int caminho_livre = 0, i;
    for(i = 0; i < 4; i++) {
        if(verif_direcao(labirinto, x, y, i)) caminho_livre++;
    }
    if (caminho_livre > 2) return 1;
    else return 0;
}

void verif_saida(int xAtual, int yAtual, int xSaida, int ySaida) {
    if(xAtual == xSaida && yAtual == ySaida) {
        printf("\nO RATO ACHOU A SAIDA!\n");
        return;
    }
}
int main()
{
    /// APRESENTACAO DO PROGRAMA
    printf("================================================================\n\n");
    printf("               Bem-vindo(a) ao labirinto do rato!               \n\n");
    printf("================================================================\n\n");

    printf("Para iniciar, vamos pedir para que voce insira um arquivo .txt na\n");
    printf("pasta onde esta salvo o projeto. Indique na primeira linha a quantidade\n");
    printf("de linhas e colunas, e nas proximas mostre para nos o seu labirinto,\n");
    printf("utilizando das seguintes regras: \n\n");
    printf("X - Parede \n");
    printf("0 - Caminho Livre \n");
    printf("S -  Saida do Labirinto\n\n");

    printf("================================================================\n\n");

    char arquivo[100];
    printf("Digite abaixo nome do arquivo abaixo. (com a terminologia .txt)\n");
    scanf("%s", arquivo);
    system("cls");
    /// ENCERRA APRESENTACAO DO PROGRAMA

    ///ABERTURA DO ARQUIVO
    FILE *arquivoF;
    char Linha[TAM_MAX];
    char *result;

    arquivoF = fopen(arquivo, "r"); ///abre o arquivo
    if(arquivoF == NULL) {
        printf("Erro! Não consegui abrir o arquivo de leitura");
        exit(1);
    }

    int i, linhas = 0, colunas = 0; /// Numero de linhas e de colunas da matriz
    int qtSaidas = 0; /// Quantidade de saidas encontradas
    result = fgets(Linha, TAM_MAX, arquivoF); /// Le a primeira linha (0, contem qtd de linhas e colunas)
    int erro = sscanf(Linha, "%d %d\n", &linhas, &colunas); /// tenta ler os valores da primeira linha. /// se erro, retorna != 2

    ///INICIO DAS VALIDACOES
    if(erro != 2) {
        printf("Erro ao identificar o numero de linhas e colunas do labirinto.\n");
        exit(1);
    }
    if(linhas > TAM_MAX || colunas > TAM_MAX){  /// se tiver mais linha ou coluna q o permitido
        printf("O numero de linhas e de colunas nao e valido.\n");
        exit(1);
    }
    char **labirinto = (char **)malloc(linhas * sizeof(char *));
    for (i = 0; i < linhas; i++) {
        labirinto[i] = (char *)malloc(colunas * sizeof(char));
    } ///matriz do labirinto
    int k = 0; /// Contador de linhas no loop
    Coords saida; ///vai receber a coordenada de saida do labirinto

    ///LOOP LENDO LINHA POR LINHA E FAZENDO AS VALIDAÇOES
    while (!feof(arquivoF)) {
        result = fgets(Linha, colunas+2, arquivoF); /// +2 por começar em 0 e por causa do \n
        int j;

        if(k == 0 || k == (linhas-1)) { /// se for a ultima ou primeira linha

                                        /// Substitui \n do final da linha por caractere nulo
            if (Linha[(strlen(Linha)) - 1] == '\n') Linha[(strlen(Linha)) - 1] = '\0';

                                        /// Vendo se o numero de caracteres da linha bate com a quantidade exigida
            if(strlen(Linha) != colunas){
                printf("O numero de caracteres na linha %d do labirinto nao bate. Verifique o arquivo.\n", i+1);
                exit(1);
            }
                                            /// Ve se a saída está numa quina (inacessivel ao rato)
            if(Linha[0] == 'S' || Linha[strlen(Linha)-1] == 'S') {
                printf("A saida do labirinto nao pode estar em uma quina.");
                exit(1);
            }
                /// Vendo se existe algum caminho livre nas extremidades, o que nao deveria
            for(j = 0; j < colunas; j++){
                if(Linha[j] == '0'){
                    printf("Nao podem ter caminhos livres nas extremidades, somente a(s) saida(s) representadas por 'S'");
                    exit(1);
                }
                if(Linha[j] != 'X' && Linha[j] != 'S' && Linha[j] != '0'){
                    printf("Foi encontrado um caracter invalido no labirinto. Verifique o arquivo.");
                    exit(1);
                }
                if(Linha[j] == 'S') qtSaidas++;
            }
        }
        else { ///Se nao for extremidade, exige que apenas o primeiro e o ultimo caracteres sejam X

                /// Substitui \n por caracter nulo
            if (Linha[(strlen(Linha)) - 1] == '\n') Linha[(strlen(Linha)) - 1] = '\0';
                /// Vendo se o numero de caracteres bate com o numero de colunas exigido
            if(strlen(Linha) != colunas){
                printf("O numero de caracteres na linha %d do labirinto nao bate. Verifique o arquivo.\n", i+1);
                exit(1);
            }
                // Vendo se existem caminhos livres nas extremidades da linha, novamente
            if(Linha[0] == '0' || Linha[colunas-1] == '0'){
                printf("Nao podem ter caminhos livres nas extremidades, somente a(s) saida(s) representadas por 'S'");
                exit(1);
            }

            for(j = 0; j < colunas; j++) {
                if(Linha[j] == 'S' && (j != 0 && j < colunas-1)){
                    printf("Foi encontrada uma saida no meio do labirinto. Elas devem estar na extremidade do labirinto.");
                    exit(1);
                }
                if(Linha[j] != 'X' && Linha[j] != 'S' && Linha[j] != '0'){
                    printf("Foi encontrado um caracter invalido no labirinto. Verifique o arquivo.");
                    exit(1);
                }
            }

                /// Aumentando o numero de saidas
            if(Linha[0] == 'S') {
                saida.x = k;
                saida.y = 0;
                qtSaidas++;
            }
            if(Linha[colunas-1] == 'S') qtSaidas++;
        }
        for (int j = 0; j < colunas; j++) {
            labirinto[k][j] = result[j];
        }
        k++;
    }
    ///FIM DO LOOP

    /// Se o numero de linhas lidas nao for igual ao numero de linhas informado no arquivo, retorna erro
    if(linhas != i){
        printf("O numero de linhas fornecidas pelo labirinto nao bate com a quantidade de linhas encontradas.");
        exit(1);
    }
    ///FIM DAS VALIDACOES

    ///PRINTA O LABIRINTO
    Coords init, atual;
    printa_labirinto(labirinto, linhas, colunas);
    printf("Insira a linha inicial do rato (1 a %i): ", linhas-2); scanf("%i", &init.x); ///a ultima eh a 13, q eh so X
    if(init.x <= 0 || init.x >= linhas) {
        printf("Linha fora do limite. Reiniciar o programa");
        exit(1);
    }
    printf("Insira a coluna inicial do rato: (1 a %i): ", colunas-2); scanf("%i", &init.y);
    if(init.y <= 0 || init.y >= colunas || labirinto[init.x][init.y] == 'X' || labirinto[init.x][init.y] == 'S') {
        printf("Coluna inválida ou rato posicionado em parede/saída. Reiniciar o programa");
        exit(1);
    }

    atual.x = init.x;
    atual.y = init.y;

    Pilha pd_movimentos; /// PILHA COM OS MOVIMENTOS DO RATO
    pdInit(&pd_movimentos);
    srand(time(NULL));
    int qtd_movimentos=0; /// INDICE DE MOVIMENTOS, USADO PARA RETROCEDER A QUANTIDADE CERTA


    while(1) {
        int randomDirecao, caminho_livre = 0, i;
        randomDirecao = rand() % 4; /// DIRECAO ALEATORIA
        for(i = 0; i < 4; i++) {
            if(verif_direcao(labirinto, atual.x, atual.y, i)) caminho_livre++; ///VEFIFICA CAMINHOS LIVRES
        }
        if(atual.x != init.x && atual.y != init.y && caminho_livre>=2) { ///VERIFICA CHECKPOINT NA POSICAO ATUAL ANTES DO LOOP
                labirinto[atual.x][atual.y] = 'C';
                qtd_movimentos = 0;
        }

        tipoPilha retrocede = -1;
        /// DESEMPILHANDO
        if(caminho_livre == 0) { ///SE NAO TIVER PARA ONDE IR, DESEMPILHA E RETROCEDE
            while(qtd_movimentos != 0) {
                if(pdIsEmpty(pd_movimentos) == 0) retrocede = pdPop(&pd_movimentos);
                rato_volta(labirinto, &atual, retrocede, linhas, colunas);
                qtd_movimentos--;
            }
        }
        /// EMPILHANDO
        else {
            if(verif_direcao(labirinto, atual.x, atual.y, randomDirecao)) {
                while(verif_direcao(labirinto, atual.x, atual.y, randomDirecao)) {
                    qtd_movimentos++;
                    rato_anda(labirinto, &atual, &init, &saida, randomDirecao, linhas, colunas);
                    if(atual.x == saida.x && atual.y == saida.y) break; ///encerra se estiver na saida
                    if(labirinto[atual.x][atual.y] == 'C') qtd_movimentos = 0;
                    pdPush(&pd_movimentos, randomDirecao);
                }
                if(atual.x == saida.x && atual.y == saida.y) break; ///encerra se estiver na saida
            }
            if(atual.x == saida.x && atual.y == saida.y) break; ///encerra se estiver na saida
        }
        if(atual.x == saida.x && atual.y == saida.y) break; ///encerra se estiver na saida
    }
    for (int i = 0; i < linhas; i++) {
        free(labirinto[i]);
    }
    free(labirinto);
    system("cls");
    printf("Caminho percorrido a partir da posicao inicial [%i][%i]: \n", init.x, init.y);
    printf("ESQUERDA = %i\n", ESQUERDA);
    printf("CIMA = %i\n", CIMA);
    printf("DIREITA = %i\n", DIREITA);
    printf("BAIXO = %i\n", BAIXO);
    while(!pdIsEmpty(pd_movimentos)) {
        printf("%i <- ", pdPop(&pd_movimentos));
    }
    return 0;
}
