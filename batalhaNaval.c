#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs() (valor absoluto)

// Define as dimensões do tabuleiro
#define LINHAS 10
#define COLUNAS 10

// Função para inicializar o tabuleiro com 0 (não afetado)
void inicializar_tabuleiro_habilidades(int tabuleiro[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            tabuleiro[i][j] = 0; // 0 representa área não afetada
        }
    }
}

// Função para exibir o tabuleiro de habilidades
// (Similar à função de exibir tabuleiro do Nível Aventureiro)
void exibir_tabuleiro_habilidades(int tabuleiro[LINHAS][COLUNAS]) {
    printf("Tabuleiro de Habilidades (%dx%d):\n", LINHAS, COLUNAS);
    printf("   "); // Espaço para alinhar com os índices das colunas
    for (int j = 0; j < COLUNAS; j++) {
        printf("%d ", j); // Imprime índices das colunas (X)
    }
    printf("\n");

    for (int i = 0; i < LINHAS; i++) {
        printf("%2d ", i); // Imprime índices das linhas (Y), com 2 dígitos para alinhar
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Aplica a habilidade em formato de Cone.
 * O cone se expande para baixo a partir do vértice (ponto_x, ponto_y).
 * 'altura' define o número de linhas que o cone ocupa.
 * A largura da base do cone será 2 * (altura - 1) + 1.
 */
void aplicar_habilidade_cone(int tabuleiro[LINHAS][COLUNAS], int ponto_x_vertice, int ponto_y_vertice, int altura) {
    printf("Aplicando Habilidade CONE: Vértice (X:%d, Y:%d), Altura: %d\n", ponto_x_vertice, ponto_y_vertice, altura);
    for (int i = 0; i < altura; i++) { // i é a distância vertical do vértice (0 para a linha do vértice)
        int y_atual = ponto_y_vertice + i;

        // Verifica se a linha atual está dentro do tabuleiro
        if (y_atual >= 0 && y_atual < LINHAS) {
            // Para cada linha do cone, a largura aumenta. 'i' também é a "metade da largura" a partir do centro.
            for (int offset_x = -i; offset_x <= i; offset_x++) {
                int x_atual = ponto_x_vertice + offset_x;

                // Verifica se a coluna atual está dentro do tabuleiro
                if (x_atual >= 0 && x_atual < COLUNAS) {
                    tabuleiro[y_atual][x_atual] = 1; // 1 representa área afetada
                }
            }
        }
    }
}

/**
 * Aplica a habilidade em formato de Cruz.
 * (centro_x, centro_y) é o ponto central da cruz.
 * 'meio_comp_h' é a metade do comprimento do braço horizontal (ex: se 2, o braço tem 2+1+2 = 5 células).
 * 'meio_comp_v' é a metade do comprimento do braço vertical.
 */
void aplicar_habilidade_cruz(int tabuleiro[LINHAS][COLUNAS], int centro_x, int centro_y, int meio_comp_h, int meio_comp_v) {
    printf("Aplicando Habilidade CRUZ: Centro (X:%d, Y:%d), MeioCompH: %d, MeioCompV: %d\n", centro_x, centro_y, meio_comp_h, meio_comp_v);
    // Braço horizontal
    if (centro_y >= 0 && centro_y < LINHAS) {
        for (int offset_x = -meio_comp_h; offset_x <= meio_comp_h; offset_x++) {
            int x_atual = centro_x + offset_x;
            if (x_atual >= 0 && x_atual < COLUNAS) {
                tabuleiro[centro_y][x_atual] = 1;
            }
        }
    }
    // Braço vertical
    if (centro_x >= 0 && centro_x < COLUNAS) {
        for (int offset_y = -meio_comp_v; offset_y <= meio_comp_v; offset_y++) {
            int y_atual = centro_y + offset_y;
            if (y_atual >= 0 && y_atual < LINHAS) {
                tabuleiro[y_atual][centro_x] = 1;
            }
        }
    }
}

/**
 * Aplica a habilidade em formato de Octaedro (Losango/Diamante).
 * Afeta células cuja distância de Manhattan do (centro_x, centro_y) é menor ou igual ao 'raio'.
 * Distância de Manhattan: |dx| + |dy|
 */
void aplicar_habilidade_octaedro(int tabuleiro[LINHAS][COLUNAS], int centro_x, int centro_y, int raio) {
    printf("Aplicando Habilidade OCTAEDRO: Centro (X:%d, Y:%d), Raio: %d\n", centro_x, centro_y, raio);
    for (int y_atual = 0; y_atual < LINHAS; y_atual++) {
        for (int x_atual = 0; x_atual < COLUNAS; x_atual++) {
            if (abs(y_atual - centro_y) + abs(x_atual - centro_x) <= raio) {
                tabuleiro[y_atual][x_atual] = 1;
            }
        }
    }
}
// Versão otimizada para Octaedro (evita varrer o tabuleiro todo)
void aplicar_habilidade_octaedro_otimizado(int tabuleiro[LINHAS][COLUNAS], int centro_x, int centro_y, int raio) {
    printf("Aplicando Habilidade OCTAEDRO (Otimizado): Centro (X:%d, Y:%d), Raio: %d\n", centro_x, centro_y, raio);
    for (int offset_y = -raio; offset_y <= raio; offset_y++) {
        int y_atual = centro_y + offset_y;
        if (y_atual >= 0 && y_atual < LINHAS) {
            int raio_restante_x = raio - abs(offset_y);
            for (int offset_x = -raio_restante_x; offset_x <= raio_restante_x; offset_x++) {
                int x_atual = centro_x + offset_x;
                if (x_atual >= 0 && x_atual < COLUNAS) {
                    tabuleiro[y_atual][x_atual] = 1;
                }
            }
        }
    }
}


int main() {
    // Declaração do tabuleiro de habilidades 10x10
    // Coordenadas: tabuleiro[Y][X], onde Y é a linha e X é a coluna.
    int tabuleiro_habilidades[LINHAS][COLUNAS];

    // Inicializa o tabuleiro com áreas não afetadas (0)
    inicializar_tabuleiro_habilidades(tabuleiro_habilidades);

    printf("👑 Bem-vindo ao Nível Mestre da Batalha Naval! 👑\n\n");
    printf("Demonstrando Habilidades Especiais no tabuleiro %dx%d.\n", LINHAS, COLUNAS);
    printf("Legenda: 0 = Não Afetado, 1 = Área Afetada pela Habilidade\n\n");

    // Aplicar Habilidade Cone
    // Vértice em (X=2, Y=1), altura 3
    // Y=1: (2,1)
    // Y=2: (1,2),(2,2),(3,2)
    // Y=3: (0,3),(1,3),(2,3),(3,3),(4,3)
    aplicar_habilidade_cone(tabuleiro_habilidades, 2, 1, 3);
    exibir_tabuleiro_habilidades(tabuleiro_habilidades); // Exibe após cada habilidade para clareza

    // Aplicar Habilidade Cruz
    // Centro em (X=6, Y=4), meio_comp_h=2 (total 5), meio_comp_v=1 (total 3)
    // Horizontal em Y=4: (4,4) a (8,4)
    // Vertical em X=6: (6,3) a (6,5)
    // Para não sobrescrever tanto o cone, vamos mudar a posição da cruz.
    // Centro em (X=7, Y=7), meio_comp_h=2, meio_comp_v=1
    inicializar_tabuleiro_habilidades(tabuleiro_habilidades); // Limpa para a próxima habilidade (ou pode acumular)
    printf("\nLimpando tabuleiro para a próxima habilidade...\n");
    aplicar_habilidade_cruz(tabuleiro_habilidades, 7, 7, 2, 1);
    exibir_tabuleiro_habilidades(tabuleiro_habilidades);

    // Aplicar Habilidade Octaedro
    // Centro em (X=4, Y=5), raio=2
    inicializar_tabuleiro_habilidades(tabuleiro_habilidades); // Limpa para a próxima habilidade
    printf("\nLimpando tabuleiro para a próxima habilidade...\n");
    // aplicar_habilidade_octaedro(tabuleiro_habilidades, 4, 5, 2); // Versão não otimizada
    aplicar_habilidade_octaedro_otimizado(tabuleiro_habilidades, 4, 5, 2); // Versão otimizada
    exibir_tabuleiro_habilidades(tabuleiro_habilidades);

    // Demonstração com todas as habilidades acumuladas (sem limpar o tabuleiro entre elas)
    printf("\n--- Demonstração com todas as habilidades ACUMULADAS ---\n");
    inicializar_tabuleiro_habilidades(tabuleiro_habilidades);
    aplicar_habilidade_cone(tabuleiro_habilidades, 2, 0, 3);      // Vértice X=2,Y=0 (mais acima)
    aplicar_habilidade_cruz(tabuleiro_habilidades, 7, 3, 2, 1);      // Centro X=7,Y=3
    aplicar_habilidade_octaedro_otimizado(tabuleiro_habilidades, 4, 7, 2); // Centro X=4,Y=7
    exibir_tabuleiro_habilidades(tabuleiro_habilidades);


    printf("🎉 Demonstração das Habilidades Especiais no Nível Mestre concluída! 🎉\n");

    return 0;
}