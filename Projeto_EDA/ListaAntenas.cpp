#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaAntenas.h"
#include "Antena.h"
#include "Dados.h"

// Cria uma nova lista ligada vazia
ED* criarED() {
    ED* ed = (ED*)malloc(sizeof(ED));
    if (ed == NULL) {
        perror("Erro ao alocar memória para ED");
        exit(EXIT_FAILURE);
    }
    ed->cabeca = NULL;
    return ed;
}

// Liberta toda a memória da lista ligada
void destruirED(ED* ed) {
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        Antena* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(ed);
}

// Carrega as antenas de um ficheiro de texto
void carregarAntenasDeFicheiro(ED* ed, const char* nomeFicheiro, int* max_linhas, int* max_colunas) {
    FILE* arquivo = NULL;
    errno_t err = fopen_s(&arquivo, nomeFicheiro, "r");
    if (err != 0 || arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char buffer[1024];
    int linhaAtual = 0;
    *max_colunas = 0;

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        size_t comprimento = strlen(buffer);
        if (comprimento > 0 && buffer[comprimento - 1] == '\n') {
            buffer[comprimento - 1] = '\0';
            comprimento--;
        }

        // Atualiza o número máximo de colunas
        if (comprimento > *max_colunas) {
            *max_colunas = comprimento;
        }

        // Processa cada caractere
        for (int coluna = 0; coluna < comprimento; coluna++) {
            if (buffer[coluna] != '.') {
                insereAntena(ed, buffer[coluna], linhaAtual, coluna);
            }
        }

        linhaAtual++;
    }

    *max_linhas = linhaAtual; // Número total de linhas
    fclose(arquivo);
}

// Listar Antenas de forma decrescente por linha
void listarAntenas(const ED* ed) {
    // Passo 1: Contar o número de antenas
    int numAntenas = 0;
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        numAntenas++;
        atual = atual->prox;
    }

    // Passo 2: Criar um array de ponteiros para Antena
    Antena** arrayAntenas = (Antena**)malloc(numAntenas * sizeof(Antena*));
    if (arrayAntenas == NULL) {
        perror("Erro ao alocar memória");
        return;
    }

    // Passo 3: Preencher o array com as antenas da lista
    atual = ed->cabeca;
    for (int i = 0; i < numAntenas; i++) {
        arrayAntenas[i] = atual;
        atual = atual->prox;
    }

    // Passo 4: Ordenar o array por linha e coluna
    qsort(arrayAntenas, numAntenas, sizeof(Antena*),
        [](const void* a, const void* b) -> int {
            Antena* antenaA = *(Antena**)a;
            Antena* antenaB = *(Antena**)b;

            // Ordena por linha (prioridade máxima)
            if (antenaA->linha != antenaB->linha) {
                return antenaA->linha - antenaB->linha;
            }

            // Se linha igual, ordena por coluna
            return antenaA->coluna - antenaB->coluna;
        });

    // Passo 5: Imprimir as antenas ordenadas
    printf("=== Lista de Antenas (Ordenadas) ===\n");
    for (int i = 0; i < numAntenas; i++) {
        printf("Antena '%c' em (%d, %d)\n",
            arrayAntenas[i]->frequencia,
            arrayAntenas[i]->linha,
            arrayAntenas[i]->coluna);
    }
    printf("====================================\n");

    // Passo 6: Liberar memória do array
    free(arrayAntenas);
}

// Lista as antenas de forma formatada
void listarAntenasFormatado(const ED* ed, int max_linhas, int max_colunas) {
    if (ed == NULL || ed->cabeca == NULL) {
        printf("Nenhuma antena encontrada.\n");
        return;
    }

    // Alocar dinamicamente uma matriz de caracteres (array de strings)
    char** matriz = (char**)malloc(max_linhas * sizeof(char*));
    if (matriz == NULL) {
        perror("Erro ao alocar memória para a matriz");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < max_linhas; i++) {
        matriz[i] = (char*)malloc((max_colunas + 1) * sizeof(char)); // +1 para '\0'
        if (matriz[i] == NULL) {
            perror("Erro ao alocar memória para uma linha da matriz");
            exit(EXIT_FAILURE);
        }
        // Preencher a linha com '.' e terminar com '\0'
        for (int j = 0; j < max_colunas; j++) {
            matriz[i][j] = '.';
        }
        matriz[i][max_colunas] = '\0';
    }

    // Percorrer a lista de antenas e marcar suas posições na matriz
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        if (atual->linha >= 0 && atual->linha < max_linhas &&
            atual->coluna >= 0 && atual->coluna < max_colunas) {
            matriz[atual->linha][atual->coluna] = atual->frequencia;
        }
        atual = atual->prox;
    }

    // Imprimir a matriz formatada
    printf("=== Mapa de Antenas ===\n");
    for (int i = 0; i < max_linhas; i++) {
        printf("%s\n", matriz[i]);
        free(matriz[i]);
    }
    free(matriz);
    printf("=======================\n");
}
