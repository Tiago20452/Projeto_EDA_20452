#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Antena.h"
#include "Dados.h"


// Função para verificar se já existe uma antena na posição
int verificaPosicaoAntena(ED* ed, int linha, int coluna) {
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        if (atual->linha == linha && atual->coluna == coluna) {
            return 0; // Posição já ocupada
        }
        atual = atual->prox;
    }
    return 1; // Posição disponível
}

// Função para inserir uma nova antena, se a posição estiver disponível
void insereAntena(ED* ed, char freq, int linha, int coluna) {
    if (!verificaPosicaoAntena(ed, linha, coluna)) {
        printf("Erro: Ja existe uma antena em (%d, %d).\n", linha, coluna);
        return;
    }

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

// Função para remover uma antena com uma frequência específica na posição
int removerAntena(ED* ed, char freq, int linha, int coluna) {
    Antena* atual = ed->cabeca;
    Antena* anterior = NULL;

    while (atual != NULL) {
        if (atual->linha == linha && atual->coluna == coluna && atual->frequencia == freq) {
            if (anterior == NULL) {
                ed->cabeca = atual->prox;
            }
            else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return 1; // Antena removida com sucesso
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0; // Antena não encontrada
}

// Função para inserir uma antena manualmente
void inserirAntenaManual(ED* ed) {
    char freq;
    int linha, coluna;

    // Ler frequência
    printf("Insira a frequência da antena (caractere): ");
    scanf_s(" %c", &freq, 1);

    // Ler coordenadas
    printf("Insira a linha da antena: ");
    scanf_s("%d", &linha);

    printf("Insira a coluna da antena: ");
    scanf_s("%d", &coluna);

    // Chamar função de inserção
    insereAntena(ed, freq, linha, coluna);
}
