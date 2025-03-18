#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Antena.h"
#include "Dados.h"

void carregarAntenasDeFicheiro(ED* ed, const char* nomeFicheiro) {
    FILE* arquivo = NULL;
    errno_t err = fopen_s(&arquivo, nomeFicheiro, "r");
    if (err != 0 || arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char buffer[1024]; // Buffer estático para ler linhas
    int linhaAtual = 0;

    // Lê cada linha do arquivo até atingir o final (EOF)
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
            if (caractere != '.') { // É uma antena
                inserirAntena(ed, caractere, linhaAtual, coluna);
            }
        }

        linhaAtual++;
    }

    fclose(arquivo);
}


ED* criarED() {
    ED* ed = (ED*)malloc(sizeof(ED));
    if (ed == NULL) {
        perror("Erro ao alocar memória para ED");
        exit(EXIT_FAILURE);
    }
    ed->cabeca = NULL;
    return ed;
}

// Libera toda a memória da lista ligada
void destruirED(ED* ed) {
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        Antena* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(ed);
}

// Insere uma antena no início da lista
void inserirAntena(ED* ed, char freq, int linha, int coluna) {
    Antena* novaAntena = (Antena*)malloc(sizeof(Antena));
    if (novaAntena == NULL) {
        perror("Erro ao alocar memória para Antena");
        exit(EXIT_FAILURE);
    }

    novaAntena->frequencia = freq;
    novaAntena->linha = linha;
    novaAntena->coluna = coluna;
    novaAntena->prox = ed->cabeca; // Insere no início
    ed->cabeca = novaAntena;
}

// Lista todas as antenas da ED
void listarAntenas(const ED* ed) {
    Antena* atual = ed->cabeca;
    printf("=== Lista de Antenas ===\n");
    while (atual != NULL) {
        printf("Antena '%c' em (%d, %d)\n",
            atual->frequencia,
            atual->linha,
            atual->coluna);
        atual = atual->prox;
    }
    printf("========================\n");
}

