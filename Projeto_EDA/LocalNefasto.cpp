/*!
 *  @file LocalNefasto.cpp
 *  @author Tiago Afonso
 *  @date 2025-03-20
 *  @project Listas Ligadas Antenas
 *
 *  Resolu��o e implementa��o de Fun��es para manipula��o de uma Lista de Locais Nefastos
 */

#include <stdio.h>
#include <stdlib.h>
#include "Dados.h"
#include "Antena.h"
#include "LocalNefasto.h"
#include "ListaAntenas.h"

// --- Implementa��es ---
// 
// Fun��es Static (n�o declaradas no .h)

// Verifica se um local nefasto j� existe na lista
static int localExiste(ED_LocaisNefastos* locais, int linha, int coluna) {
    LocalNefasto* atual = locais->cabeca;
    while (atual != NULL) {
        if (atual->linha == linha && atual->coluna == coluna) return 1;
        atual = atual->prox;
    }
    return 0;
}

// Adiciona um local nefasto � lista
static void adicionarLocalNefasto(ED_LocaisNefastos* locais, int linha, int coluna) {
    if (localExiste(locais, linha, coluna)) return;

    LocalNefasto* novo = (LocalNefasto*)malloc(sizeof(LocalNefasto));
    if (novo == NULL) {
        perror("Erro ao alocar mem�ria para LocalNefasto");
        exit(EXIT_FAILURE);
    }

    novo->linha = linha;
    novo->coluna = coluna;
    novo->prox = locais->cabeca;
    locais->cabeca = novo;
}


/**
 * Fun��o principal para calcular os locais nefastos com base nas antenas existentes.
 *
 * O efeito nefasto ocorre em posi��es espec�ficas alinhadas com pares de antenas
 * da mesma frequ�ncia, onde uma antena est� a uma dist�ncia duas vezes maior que a outra.
 *
 */
void calcularLocaisNefastos(ED* ed, ED_LocaisNefastos* locaisNefastos, int max_linhas, int max_colunas) {
    if (ed == NULL || locaisNefastos == NULL) return; // Verifica��o de seguran�a para evitar erros

    Antena* atual = ed->cabeca;
    ED* mapaFrequencias[256] = { 0 }; // Array para armazenar listas de antenas por frequ�ncia (ASCII)

    // Passo 1: Agrupar antenas por frequ�ncia
    while (atual != NULL) {
        char freq = atual->frequencia;
        if (mapaFrequencias[freq] == NULL) {
            mapaFrequencias[freq] = criarED(); // Cria uma nova lista para armazenar antenas dessa frequ�ncia
        }
        insereAntena(mapaFrequencias[freq], freq, atual->linha, atual->coluna); // Insere a antena na lista correta
        atual = atual->prox;
    }

    // Passo 2: Calcular locais nefastos para cada par de antenas de mesma frequ�ncia
    for (int freq = 0; freq < 256; freq++) {
        if (mapaFrequencias[freq] == NULL) continue; // Se n�o houver antenas dessa frequ�ncia, pula para a pr�xima

        Antena* a1 = mapaFrequencias[freq]->cabeca;
        while (a1 != NULL) {
            Antena* a2 = a1->prox; // Evita pares duplicados (a1, a2) e (a2, a1)
            while (a2 != NULL) {
                // Diferen�a entre as coordenadas das duas antenas
                int dx = a2->coluna - a1->coluna;
                int dy = a2->linha - a1->linha;

                // Calcular as duas poss�veis posi��es com efeito nefasto
                int L1_linha = a1->linha + 2 * dy;
                int L1_coluna = a1->coluna + 2 * dx;

                int L2_linha = a2->linha - 2 * dy;
                int L2_coluna = a2->coluna - 2 * dx;

                // Valida��o: Garante que os locais nefastos calculados est�o dentro dos limites da matriz
                if (L1_linha >= 0 && L1_linha < max_linhas && L1_coluna >= 0 && L1_coluna < max_colunas) {
                    adicionarLocalNefasto(locaisNefastos, L1_linha, L1_coluna);
                }

                if (L2_linha >= 0 && L2_linha < max_linhas && L2_coluna >= 0 && L2_coluna < max_colunas) {
                    adicionarLocalNefasto(locaisNefastos, L2_linha, L2_coluna);
                }

                a2 = a2->prox; // Avan�a para o pr�ximo par de antenas
            }
            a1 = a1->prox; // Avan�a para a pr�xima antena na lista
        }
    }

    // Passo 3: Liberar mem�ria das listas tempor�rias usadas para agrupamento de antenas
    for (int i = 0; i < 256; i++) {
        if (mapaFrequencias[i] != NULL) {
            destruirED(mapaFrequencias[i]);
        }
    }
}


/**
 * Fun��o para listar todos os locais nefastos armazenados na estrutura ED_LocaisNefastos.
 *
 * Percorre a lista ligada de locais nefastos e imprime suas coordenadas na consola.
 * Caso n�o haja locais armazenados, exibe uma mensagem informando que nenhum foi encontrado.
 *
 */
void listarLocaisNefastos(const ED_LocaisNefastos* locais) {
    // Verifica se a lista de locais nefastos est� vazia
    if (locais == NULL || locais->cabeca == NULL) {
        printf("Nenhum local nefasto encontrado.\n");
        return;
    }

    LocalNefasto* atual = locais->cabeca; // Ponteiro para percorrer a lista ligada
    printf("=== Locais Nefastos ===\n");

    // Percorre a lista e imprime cada local nefasto
    while (atual != NULL) {
        printf("Local nefasto em (%d, %d)\n", atual->linha, atual->coluna);
        atual = atual->prox; // Avan�a para o pr�ximo n� da lista
    }

    printf("=======================\n");
}


/**
 * Fun��o para listar os locais nefastos em formato de matriz.
 *
 * Cria uma matriz de caracteres (com dimens�es especificadas) e preenche os locais nefastos representados
 * por '#' nas posi��es correspondentes. Todos os outros locais da matriz s�o inicialmente preenchidos com o caractere '.'.
 * Ap�s preencher a matriz, a fun��o imprime o mapa de locais nefastos na consola.
 * Caso n�o haja locais nefastos, exibe uma mensagem informando que nenhum local foi encontrado.
 *
 */
void listarLocaisNefastosFormatado(const ED_LocaisNefastos* locais, int max_linhas, int max_colunas) {
    // Verifica se a estrutura de locais � v�lida e se cont�m locais
    if (locais == NULL || locais->cabeca == NULL) {
        printf("Nenhum local nefasto encontrado.\n");
        return;  // Se n�o houver locais nefastos, exibe mensagem e retorna
    }

    // Aloca dinamicamente a matriz de caracteres para armazenar a representa��o do mapa
    char** matriz = (char**)malloc(max_linhas * sizeof(char*));  // Aloca o vetor de ponteiros para as linhas
    for (int i = 0; i < max_linhas; i++) {
        matriz[i] = (char*)malloc(max_colunas * sizeof(char));  // Aloca cada linha da matriz
        for (int j = 0; j < max_colunas; j++) {
            matriz[i][j] = '.';  // Inicializa cada posi��o da matriz com o caractere '.'
        }
    }

    // Preenche a matriz com os locais nefastos representados por '#'
    LocalNefasto* atual = locais->cabeca;  // Acessa o primeiro local da lista
    while (atual != NULL) {
        // Marca o local nefasto na posi��o correspondente da matriz
        matriz[atual->linha][atual->coluna] = '#';
        atual = atual->prox;  // Avan�a para o pr�ximo local na lista
    }

    // Imprime a matriz formatada, representando o mapa de locais nefastos
    printf("=== Mapa de Locais Nefastos ===\n");
    for (int i = 0; i < max_linhas; i++) {
        for (int j = 0; j < max_colunas; j++) {
            printf("%c", matriz[i][j]);  // Imprime cada caractere da matriz
        }
        printf("\n");  // Quebra de linha ao final de cada linha da matriz
    }
    printf("==============================\n");

    // Libera a mem�ria alocada para a matriz
    for (int i = 0; i < max_linhas; i++) {
        free(matriz[i]);  // Liberta cada linha da matriz
    }
    free(matriz);  // Liberta o vetor de ponteiros para as linhas
}

