#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Antena.h"
#include "Dados.h"


// Fun��o para verificar se j� existe uma antena na posi��o
int verificaPosicaoAntena(ED* ed, int linha, int coluna) {
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        if (atual->linha == linha && atual->coluna == coluna) {
            return 0; // Posi��o j� ocupada
        }
        atual = atual->prox;
    }
    return 1; // Posi��o dispon�vel
}

// Fun��o para inserir uma nova antena, se a posi��o estiver dispon�vel
void insereAntena(ED* ed, char freq, int linha, int coluna) {
    if (!verificaPosicaoAntena(ed, linha, coluna)) {
        printf("Erro: Ja existe uma antena em (%d, %d).\n", linha, coluna);
        return;
    }

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

// Fun��o para remover uma antena com uma frequ�ncia espec�fica na posi��o
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
    return 0; // Antena n�o encontrada
}

// Fun��o para inserir uma antena manualmente
void inserirAntenaManual(ED* ed) {
    char freq;
    int linha, coluna;

    // Ler frequ�ncia
    printf("Insira a frequ�ncia da antena (caractere): ");
    scanf_s(" %c", &freq, 1);

    // Ler coordenadas
    printf("Insira a linha da antena: ");
    scanf_s("%d", &linha);

    printf("Insira a coluna da antena: ");
    scanf_s("%d", &coluna);

    // Chamar fun��o de inser��o
    insereAntena(ed, freq, linha, coluna);
}
