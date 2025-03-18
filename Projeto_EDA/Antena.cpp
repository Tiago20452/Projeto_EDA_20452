#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Antena.h"
#include "Dados.h"

// Carrega as antenas de um ficheiro de texto
void carregarAntenasDeFicheiro(ED* ed, const char* nomeFicheiro) {
    FILE* arquivo = NULL;
    errno_t err = fopen_s(&arquivo, nomeFicheiro, "r");
    if (err != 0 || arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char buffer[1024]; // Buffer est�tico para ler linhas
    int linhaAtual = 0;

    // L� cada linha do arquivo at� atingir o final (EOF)
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {

        // Remove o caractere de nova linha (\n) ou \r\n (Windows)
        size_t comprimento = strlen(buffer);
        if (comprimento > 0 && buffer[comprimento - 1] == '\n') {
            buffer[comprimento - 1] = '\0';
            comprimento--;
        }
        if (comprimento > 0 && buffer[comprimento - 1] == '\r') {
            buffer[comprimento - 1] = '\0';
            comprimento--;
        }

        // Processa cada caractere da linha
        for (int coluna = 0; coluna < comprimento; coluna++) {
            char caractere = buffer[coluna];
            if (caractere != '.') { // � uma antena
                inserirAntena(ed, caractere, linhaAtual, coluna);
            }
        }

        linhaAtual++;
    }

    fclose(arquivo);
}

// Insere uma antena no in�cio da lista
void inserirAntena(ED* ed, char freq, int linha, int coluna) {
    Antena* novaAntena = (Antena*)malloc(sizeof(Antena));
    if (novaAntena == NULL) {
        perror("Erro ao alocar mem�ria para Antena");
        exit(EXIT_FAILURE);
    }

    novaAntena->frequencia = freq;
    novaAntena->linha = linha;
    novaAntena->coluna = coluna;
    novaAntena->prox = ed->cabeca; // Insere no in�cio
    ed->cabeca = novaAntena;
}

// Listar Antenas de forma decrescente por linha
void listarAntenas(const ED* ed) {
    // Passo 1: Contar o n�mero de antenas
    int numAntenas = 0;
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        numAntenas++;
        atual = atual->prox;
    }

    // Passo 2: Criar um array de ponteiros para Antena
    Antena** arrayAntenas = (Antena**)malloc(numAntenas * sizeof(Antena*));
    if (arrayAntenas == NULL) {
        perror("Erro ao alocar mem�ria");
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

            // Ordena por linha (prioridade m�xima)
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

    // Passo 6: Liberar mem�ria do array
    free(arrayAntenas);
}

