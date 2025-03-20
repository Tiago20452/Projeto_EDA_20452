#include <stdio.h>
#include <stdlib.h>
#include "Dados.h"
#include "Antena.h"
#include "LocalNefasto.h"
#include "ListaAntenas.h"

// --- Implementações ---

// Função auxiliar (não declarada no .h)
static int localExiste(ED_LocaisNefastos* locais, int linha, int coluna) {
    LocalNefasto* atual = locais->cabeca;
    while (atual != NULL) {
        if (atual->linha == linha && atual->coluna == coluna) return 1;
        atual = atual->prox;
    }
    return 0;
}

// Função auxiliar (não declarada no .h)
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
void calcularLocaisNefastos(ED* ed, ED_LocaisNefastos* locaisNefastos) {
    Antena* atual = ed->cabeca;
    ED* mapaFrequencias[256] = { 0 };

    // Agrupa antenas por frequência
    while (atual != NULL) {
        char freq = atual->frequencia;
        if (mapaFrequencias[freq] == NULL) {
            mapaFrequencias[freq] = criarED();
        }
        insereAntena(mapaFrequencias[freq], freq, atual->linha, atual->coluna); // Nome corrigido
        atual = atual->prox;
    }

    // Cálculo dos pontos nefastos
    for (int i = 0; i < 256; i++) {
        if (mapaFrequencias[i] == NULL) continue;

        Antena* a1 = mapaFrequencias[i]->cabeca;
        while (a1 != NULL) {
            Antena* a2 = a1->prox;
            while (a2 != NULL) {
                int dx = a2->coluna - a1->coluna;
                int dy = a2->linha - a1->linha;

                int p1_linha = a1->linha + 2 * dy;
                int p1_coluna = a1->coluna + 2 * dx;

                int p2_linha = a2->linha - 2 * dy;
                int p2_coluna = a2->coluna - 2 * dx;

                adicionarLocalNefasto(locaisNefastos, p1_linha, p1_coluna);
                adicionarLocalNefasto(locaisNefastos, p2_linha, p2_coluna);

                a2 = a2->prox;
            }
            a1 = a1->prox;
        }
    }

    // Liberar memória
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