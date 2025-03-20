#include <stdio.h>
#include <stdlib.h>
#include "Dados.h"
#include "Antena.h"
#include "LocalNefasto.h"
#include "ListaAntenas.h"

// --- Implementações ---
// 
// Funções Static (não declaradas no .h)

// Verifica se um local nefasto já existe na lista
static int localExiste(ED_LocaisNefastos* locais, int linha, int coluna) {
    LocalNefasto* atual = locais->cabeca;
    while (atual != NULL) {
        if (atual->linha == linha && atual->coluna == coluna) return 1;
        atual = atual->prox;
    }
    return 0;
}

// Adiciona um local nefasto à lista
static void adicionarLocalNefasto(ED_LocaisNefastos* locais, int linha, int coluna) {
    if (localExiste(locais, linha, coluna)) return;

    LocalNefasto* novo = (LocalNefasto*)malloc(sizeof(LocalNefasto));
    if (novo == NULL) {
        perror("Erro ao alocar memória para LocalNefasto");
        exit(EXIT_FAILURE);
    }

    novo->linha = linha;
    novo->coluna = coluna;
    novo->prox = locais->cabeca;
    locais->cabeca = novo;
}


// Função principal
void calcularLocaisNefastos(ED* ed, ED_LocaisNefastos* locaisNefastos, int max_linhas, int max_colunas) {
    if (ed == NULL || locaisNefastos == NULL) return;

    Antena* atual = ed->cabeca;
    ED* mapaFrequencias[256] = { 0 }; // Agrupa por frequência (ASCII)

    // Passo 1: Agrupar antenas por frequência
    while (atual != NULL) {
        char freq = atual->frequencia;
        if (mapaFrequencias[freq] == NULL) {
            mapaFrequencias[freq] = criarED();
        }
        insereAntena(mapaFrequencias[freq], freq, atual->linha, atual->coluna);
        atual = atual->prox;
    }

    // Passo 2: Calcular locais nefastos para cada par de antenas
    for (int freq = 0; freq < 256; freq++) {
        if (mapaFrequencias[freq] == NULL) continue;

        Antena* a1 = mapaFrequencias[freq]->cabeca;
        while (a1 != NULL) {
            Antena* a2 = a1->prox; // Evita pares duplicados (a1, a2) e (a2, a1)
            while (a2 != NULL) {
                // Diferença entre as coordenadas
                int dx = a2->coluna - a1->coluna;
                int dy = a2->linha - a1->linha;

                // Calcular L1 e L2
                int L1_linha = a1->linha + 2 * dy;
                int L1_coluna = a1->coluna + 2 * dx;

                int L2_linha = a2->linha - 2 * dy;
                int L2_coluna = a2->coluna - 2 * dx;

                // Validação: Coordenadas dentro da matriz (0 <= x < max_linhas, 0 <= y < max_colunas)
                if (L1_linha >= 0 && L1_linha < max_linhas && L1_coluna >= 0 && L1_coluna < max_colunas) {
                    adicionarLocalNefasto(locaisNefastos, L1_linha, L1_coluna);
                }

                if (L2_linha >= 0 && L2_linha < max_linhas && L2_coluna >= 0 && L2_coluna < max_colunas) {
                    adicionarLocalNefasto(locaisNefastos, L2_linha, L2_coluna);
                }

                a2 = a2->prox;
            }
            a1 = a1->prox;
        }
    }

    // Liberar memória das listas temporárias
    for (int i = 0; i < 256; i++) {
        if (mapaFrequencias[i] != NULL) {
            destruirED(mapaFrequencias[i]);
        }
    }
}

// Listagem de locais nefastos 
void listarLocaisNefastos(const ED_LocaisNefastos* locais) {
    if (locais == NULL || locais->cabeca == NULL) {
        printf("Nenhum local nefasto encontrado.\n");
        return;
    }

    LocalNefasto* atual = locais->cabeca;
    printf("=== Locais Nefastos ===\n");
    while (atual != NULL) {
        printf("Local nefasto em (%d, %d)\n", atual->linha, atual->coluna);
        atual = atual->prox;
    }
    printf("=======================\n");
}

// Listagem de locais nefastos com formato de matriz
void listarLocaisNefastosFormatado(const ED_LocaisNefastos* locais, int max_linhas, int max_colunas) {
    if (locais == NULL || locais->cabeca == NULL) {
        printf("Nenhum local nefasto encontrado.\n");
        return;
    }

    // Alocar dinamicamente a matriz
    char** matriz = (char**)malloc(max_linhas * sizeof(char*));
    for (int i = 0; i < max_linhas; i++) {
        matriz[i] = (char*)malloc(max_colunas * sizeof(char));
        for (int j = 0; j < max_colunas; j++) {
            matriz[i][j] = '.';  // Inicializa com '.'
        }
    }

    // Preencher a matriz com locais nefastos ('#')
    LocalNefasto* atual = locais->cabeca;
    while (atual != NULL) {
        matriz[atual->linha][atual->coluna] = '#';
        atual = atual->prox;
    }

    // Imprimir a matriz formatada
    printf("=== Mapa de Locais Nefastos ===\n");
    for (int i = 0; i < max_linhas; i++) {
        for (int j = 0; j < max_colunas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
    printf("==============================\n");

    // Liberar memória
    for (int i = 0; i < max_linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}
