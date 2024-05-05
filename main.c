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

int verif_esquerda(char **Lab, Coords *atual) {                                     /// verificar se o bloco à esquerda é caminho livre ou parede
    if(Lab[atual->x][atual->y-1] != 'X' && Lab[atual->x][atual->y-1] != '#') return 1;  /// retorna 1 se for caminho livre
    else return 0;                                                                      /// retorna 0 se for parede
}                                                                                       /// se aplica para os outros também
int verif_cima(char **Lab, Coords *atual) {
    if(Lab[atual->x-1][atual->y] != 'X' && Lab[atual->x-1][atual->y] != '#') return 1;
    else return 0;
}
int verif_direita(char **Lab, Coords *atual) {
    if(Lab[atual->x][atual->y+1] != 'X' && Lab[atual->x][atual->y+1] != '#') return 1;
    else return 0;
}
int verif_baixo(char **Lab, Coords *atual) {
    if(Lab[atual->x+1][atual->y] != 'X' && Lab[atual->x+1][atual->y] != '#') return 1;
    else return 0;
}

void verif_saida(char **Lab, Coords *atual, Coords *init, Pilha *pd) {
    if(Lab[atual->x][atual->y] == 'S') {
        printf("\nO RATO ACHOU A SAIDA!\n");
        printf("Caminho seguido pelo rato a partir da posição inicial Linha[%i] Coluna[%i]\n", init->x, init->y);
        while(!pdIsEmpty) {
            int caminho = pdPop(&pd);
            switch(caminho) {
                case ESQUERDA:
                    printf("ESQUERDA <- ");
                break;
                case CIMA:
                    printf("CIMA <- ");
                    break;
                case DIREITA:
                    printf("DIREITA <- ");
                    break;
                case BAIXO:
                    printf("BAIXO <- ");
                break;
            }

        }
    }
    exit(1);
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
            if(Linha[0] == 'S') qtSaidas++;
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


    Pilha pd_movimentos;    /// pilha de movimentos
    pdInit(&pd_movimentos); /// empilha valores como '0' '1', que se referem aos movimentos como definidos no inicio
    srand(time(NULL));      /// iniciando geracao de numero aleatorio
    int qtd_movimentos=0;  /// contagem dos checkpoints (inicia no 0,
                            /// se o rato chegar no proximo é incrementado, assim por diante

    while(labirinto[atual.x][atual.y] != 'S') {                         /// roda ate o rato achar a saida

        int randomDirecao;                                              /// variavel que recebe a direcao aleatoria
        randomDirecao = rand() % 4;
        int goLEFT = verif_esquerda(labirinto, &atual);                 /// verifica cada direcao
        int goUP = verif_cima(labirinto, &atual);                       /// disponivel a partir da
        int goRIGHT = verif_direita(labirinto, &atual);                 /// posicao atual do rato
        int goDOWN = verif_baixo(labirinto, &atual);
        int dir_anterior = goLEFT + goUP + goDOWN + goRIGHT;                /// se houverem 2 caminhos, o rato explora normal
        if(atual.x != init.x && atual.y != init.y && dir_anterior>=2) {
                labirinto[atual.x][atual.y] = 'C';
                qtd_movimentos = 0;
        }
        tipoPilha retrocede = -1;                                                 /// se houver apenas 1, ele deve retroceder (desempilhar)
        if(dir_anterior == 0) {
            while(qtd_movimentos != 0) {
                if(pdIsEmpty(pd_movimentos) == 0) retrocede = pdPop(&pd_movimentos);
                switch(retrocede) {
                    case ESQUERDA:
                        atual.y++;
                        if(labirinto[atual.x][atual.y] == 'C') labirinto[atual.x][atual.y] = 'C'; ///para manter o C no mapa
                        else labirinto[atual.x][atual.y] = 'R';
                        if (labirinto[atual.x][atual.y-1] == 'C') labirinto[atual.x][atual.y-1] = 'C';
                        else labirinto[atual.x][atual.y-1] = '#';
                        system("cls");
                        printf("\nO RATO VOLTOU PARA DIREITA!\n");
                        printa_labirinto(labirinto, linhas, colunas);
                        qtd_movimentos--;
                    break;
                    case CIMA:
                        atual.x++;
                        if(labirinto[atual.x][atual.y] == 'C') labirinto[atual.x][atual.y] = 'C'; ///para manter o C no mapa
                        else labirinto[atual.x][atual.y] = 'R';
                        if (labirinto[atual.x-1][atual.y] == 'C') labirinto[atual.x-1][atual.y] = 'C';
                        else labirinto[atual.x-1][atual.y] = '#';
                        system("cls");
                        printf("\nO RATO VOLTOU PARA BAIXO!\n");
                        printa_labirinto(labirinto, linhas, colunas);
                        qtd_movimentos--;
                    break;
                    case DIREITA:
                        atual.y--;
                        if(labirinto[atual.x][atual.y] == 'C') labirinto[atual.x][atual.y] = 'C'; ///para manter o C no mapa
                        else labirinto[atual.x][atual.y] = 'R';
                        if (labirinto[atual.x][atual.y+1] == 'C') labirinto[atual.x][atual.y+1] = 'C';
                        else labirinto[atual.x][atual.y+1] = '#';
                        system("cls");
                        printf("\nO RATO VOLTOU PARA ESQUERDA!\n");
                        printa_labirinto(labirinto, linhas, colunas);
                        qtd_movimentos--;
                    break;
                    case BAIXO:
                        atual.x--;
                        if(labirinto[atual.x][atual.y] == 'C') labirinto[atual.x][atual.y] = 'C'; ///para manter o C no mapa
                        else labirinto[atual.x][atual.y] = 'R';
                        if (labirinto[atual.x+1][atual.y] == 'C') labirinto[atual.x+1][atual.y] = 'C';
                        else labirinto[atual.x+1][atual.y] = '#';
                        system("cls");
                        printf("\nO RATO VOLTOU PARA CIMA!\n");
                        printa_labirinto(labirinto, linhas, colunas);
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
                            if(verif_cima(labirinto, &atual) || verif_baixo(labirinto, &atual)) {
                                    labirinto[atual.x][atual.y] = 'C';
                                    qtd_movimentos = 1;
                                    printf("\nO RATO ACHOU UM CHECKPOINT!\n");
                                    sleep(1);
                            }
                            atual.y--;
                            if(labirinto[atual.x][atual.y] == 'S') {
                                printf("\nO RATO ACHOU A SAIDA!\n");
                                exit(1);
                            }
                            if (labirinto[atual.x][atual.y+1] == 'C') labirinto[atual.x][atual.y+1] = 'C';
                            else if (labirinto[atual.x][atual.y+1] == labirinto[init.x][init.y]) labirinto[atual.x][atual.y+1] = '0';
                            else labirinto[atual.x][atual.y+1] = '#';
                            labirinto[atual.x][atual.y] = 'R';
                            pdPush(&pd_movimentos, ESQUERDA);
                            system("cls");
                            printf("\nO RATO ANDOU PARA ESQUERDA!\n");
                            printa_labirinto(labirinto, linhas, colunas);
                        }
                    }
                break;
                case CIMA:
                    if(goUP == 1) {
                        while(labirinto[atual.x-1][atual.y] != 'X' && labirinto[atual.x-1][atual.y] != '#') {
                            qtd_movimentos++;
                            if(verif_esquerda(labirinto, &atual) || verif_direita(labirinto, &atual)) {
                                    labirinto[atual.x][atual.y] = 'C';
                                    qtd_movimentos = 1;
                                    printf("\nO RATO ACHOU UM CHECKPOINT!\n");
                            }
                            atual.x--;
                            if(labirinto[atual.x][atual.y] == 'S') {
                                printf("\nO RATO ACHOU A SAIDA!\n");
                                exit(1);
                            }
                            labirinto[atual.x][atual.y] = 'R';
                            if (labirinto[atual.x+1][atual.y] == 'C') labirinto[atual.x+1][atual.y] = 'C';
                            else if (labirinto[atual.x+1][atual.y] == labirinto[init.x][init.y]) labirinto[atual.x+1][atual.y] = '0';
                            else labirinto[atual.x+1][atual.y] = '#';
                            pdPush(&pd_movimentos, CIMA);
                            system("cls");
                            printf("\nO RATO ANDOU PARA CIMA!\n");
                            printa_labirinto(labirinto, linhas, colunas);
                        }
                    }
                break;
                case DIREITA:
                    if(goRIGHT == 1) {
                        while(labirinto[atual.x][atual.y+1] != 'X' && labirinto[atual.x][atual.y+1] != '#'){
                            qtd_movimentos++;
                            if(verif_cima(labirinto, &atual) || verif_baixo(labirinto, &atual)) {
                                    labirinto[atual.x][atual.y] = 'C';
                                    qtd_movimentos = 1;
                                    printf("\nO RATO ACHOU UM CHECKPOINT!\n");
                            }
                            atual.y++;
                            if(labirinto[atual.x][atual.y] == 'S') {
                                printf("\nO RATO ACHOU A SAIDA!\n");
                                exit(1);
                            }
                            labirinto[atual.x][atual.y] = 'R';
                            if (labirinto[atual.x][atual.y-1] == 'C') labirinto[atual.x][atual.y-1] = 'C';
                            else if (labirinto[atual.x][atual.y-1] == labirinto[init.x][init.y]) labirinto[atual.x][atual.y-1] = '0';
                            else labirinto[atual.x][atual.y-1] = '#';
                            pdPush(&pd_movimentos, DIREITA);
                            system("cls");
                            printf("\nO RATO ANDOU PARA DIREITA!\n");
                            printa_labirinto(labirinto, linhas, colunas);
                        }
                    }
                break;
                case BAIXO:
                    if(goDOWN == 1) {
                        while(labirinto[atual.x+1][atual.y] != 'X' && labirinto[atual.x+1][atual.y] != '#') {
                            qtd_movimentos++;
                            if(verif_esquerda(labirinto, &atual) || verif_direita(labirinto, &atual)) {
                                    labirinto[atual.x][atual.y] = 'C';
                                    qtd_movimentos = 1;
                                    printf("\nO RATO ACHOU UM CHECKPOINT!\n");
                            }
                            atual.x++;
                            if(labirinto[atual.x][atual.y] == 'S') {
                                printf("\nO RATO ACHOU A SAIDA!\n");
                                exit(1);
                            }
                            labirinto[atual.x][atual.y] = 'R';
                            if (labirinto[atual.x-1][atual.y] == 'C') labirinto[atual.x-1][atual.y] = 'C';
                            else if (labirinto[atual.x-1][atual.y] == labirinto[init.x-1][init.y]) labirinto[atual.x][atual.y] = '0';
                            else labirinto[atual.x-1][atual.y] = '#';
                            pdPush(&pd_movimentos, BAIXO);
                            system("cls");
                            printf("\nO RATO ANDOU PARA BAIXO!\n");
                            printa_labirinto(labirinto, linhas, colunas);
                        }
                    }
                break;
            }
        }
    }
    for (int i = 0; i < linhas; i++) {
        free(labirinto[i]);
    }
    free(labirinto);
    return 0;
}
