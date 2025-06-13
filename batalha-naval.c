#include <stdio.h>

#define TAB_SIZE 10
#define SHIP_SIZE 3
#define SKILL_SIZE 5  // Tamanho fixo das matrizes de habilidade

// Funções auxiliares para posicionar navios (simplificadas do desafio anterior)
void posiciona_navio_horizontal(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna) {
    for(int i = 0; i < SHIP_SIZE; i++) {
        tab[linha][coluna+i] = 3;
    }
}
void posiciona_navio_vertical(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna) {
    for(int i = 0; i < SHIP_SIZE; i++) {
        tab[linha+i][coluna] = 3;
    }
}

// Cria matriz de habilidade "Cone" (apontando para baixo)
// O "cone" tem o topo no centro da linha 0 e se alarga até a linha SKILL_SIZE-1
void cria_habilidade_cone(int cone[SKILL_SIZE][SKILL_SIZE]) {
    for(int i=0; i<SKILL_SIZE; i++) {
        for(int j=0; j<SKILL_SIZE; j++) {
            // Define largura do cone na linha i (quanto maior i, mais largo)
            int meio = SKILL_SIZE/2;
            // Condição para cone: coluna j dentro da faixa [meio - i, meio + i]
            if(j >= meio - i && j <= meio + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade "Cruz"
// Linha e coluna centrais são afetadas
void cria_habilidade_cruz(int cruz[SKILL_SIZE][SKILL_SIZE]) {
    int meio = SKILL_SIZE / 2;
    for(int i=0; i<SKILL_SIZE; i++) {
        for(int j=0; j<SKILL_SIZE; j++) {
            // Se i == meio (linha central) ou j == meio (coluna central) => área de efeito
            if(i == meio || j == meio)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade "Octaedro" (losango)
// Ponto central no meio da matriz, distância manhattan <= meio
void cria_habilidade_octaedro(int octaedro[SKILL_SIZE][SKILL_SIZE]) {
    int meio = SKILL_SIZE / 2;
    for(int i=0; i<SKILL_SIZE; i++) {
        for(int j=0; j<SKILL_SIZE; j++) {
            // Distancia manhattan ao centro <= meio (losango)
            int dist = abs(i - meio) + abs(j - meio);
            if(dist <= meio)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Sobrepõe a matriz de habilidade ao tabuleiro, marcando as posições afetadas (com 5)
// ponto_origem_linha e ponto_origem_coluna são coordenadas no tabuleiro onde o centro da matriz de habilidade vai ficar
void aplica_habilidade(int tab[TAB_SIZE][TAB_SIZE], int habilidade[SKILL_SIZE][SKILL_SIZE], int ponto_origem_linha, int ponto_origem_coluna) {
    int meio = SKILL_SIZE / 2;
    for(int i=0; i<SKILL_SIZE; i++) {
        for(int j=0; j<SKILL_SIZE; j++) {
            if(habilidade[i][j] == 1) {
                // Calcula a posição correspondente no tabuleiro
                int linha_tab = ponto_origem_linha - meio + i;
                int col_tab = ponto_origem_coluna - meio + j;

                // Verifica limites do tabuleiro
                if(linha_tab >= 0 && linha_tab < TAB_SIZE && col_tab >= 0 && col_tab < TAB_SIZE) {
                    // Não sobreescreve navio (3) — só marca área de efeito se posição for água (0)
                    if(tab[linha_tab][col_tab] == 0)
                        tab[linha_tab][col_tab] = 5;
                }
            }
        }
    }
}

// Função para imprimir o tabuleiro com caracteres claros
void imprime_tabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro (0=agua,3=navio,5=area de habilidade):\n");
    for(int i=0; i<TAB_SIZE; i++) {
        for(int j=0; j<TAB_SIZE; j++) {
            char c;
            if(tab[i][j] == 0) c = '.';
            else if(tab[i][j] == 3) c = 'N';  // Navio
            else if(tab[i][j] == 5) c = '*';  // Área habilidade
            else c = '?';

            printf("%c ", c);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE] = {0};

    // Posiciona dois navios fixos (horizontal e vertical) para teste
    posiciona_navio_horizontal(tabuleiro, 1, 2);
    posiciona_navio_vertical(tabuleiro, 5, 0);

    // Matrizes de habilidade
    int cone[SKILL_SIZE][SKILL_SIZE];
    int cruz[SKILL_SIZE][SKILL_SIZE];
    int octaedro[SKILL_SIZE][SKILL_SIZE];

    // Cria as matrizes dinamicamente
    cria_habilidade_cone(cone);
    cria_habilidade_cruz(cruz);
    cria_habilidade_octaedro(octaedro);

    // Define os pontos de origem das habilidades no tabuleiro
    int origem_cone_linha = 3, origem_cone_coluna = 7;
    int origem_cruz_linha = 7, origem_cruz_coluna = 2;
    int origem_octaedro_linha = 6, origem_octaedro_coluna = 6;

    // Aplica as habilidades ao tabuleiro
    aplica_habilidade(tabuleiro, cone, origem_cone_linha, origem_cone_coluna);
    aplica_habilidade(tabuleiro, cruz, origem_cruz_linha, origem_cruz_coluna);
    aplica_habilidade(tabuleiro, octaedro, origem_octaedro_linha, origem_octaedro_coluna);

    // Exibe o tabuleiro final
    imprime_tabuleiro(tabuleiro);

    return 0;
}
