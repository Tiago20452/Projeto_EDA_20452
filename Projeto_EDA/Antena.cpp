/*!
 *  @file Antena.cpp
 *  @author Tiago Afonso
 *  @date 2025-03-17
 *  @project Listas Ligadas Antenas
 * 
 * Resolução e implementação de funções para manipulação de Antenas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Antena.h"
#include "Dados.h"

 /**
 * Função para verificar se já existe uma antena numa determinada posição.
 *
 * Percorre a lista ligada de antenas e verifica se alguma delas já está
 * na posição especificada (linha, coluna).
 * 
 */
int verificaPosicaoAntena(ED* ed, int linha, int coluna) {

    // Ponteiro auxiliar para percorrer a lista de antenas
    Antena* atual = ed->cabeca;

    // Percorre a lista ligada até encontrar uma correspondência ou chegar ao final
    while (atual != NULL) {

        // Verifica se a antena atual está na mesma posição especificada
        if (atual->linha == linha && atual->coluna == coluna) {
            return 0; // Retorna 0 indicando que a posição já está ocupada
        }
        atual = atual->prox; // Avança para a próxima antena na lista
    }

    return 1; // Retorna 1 indicando que a posição está disponível
}


/**
 * Função para inserir uma nova antena na lista ligada, caso a posição esteja disponível.
 *
 * Primeiro, verifica se já existe uma antena na posição especificada.
 * Se a posição estiver ocupada, exibe uma mensagem de erro e retorna.
 * Caso contrário, aloca memória para uma nova antena e a insere no início da lista.
 * 
 */
void insereAntena(ED* ed, char freq, int linha, int coluna) {

    // Verifica se a posição já está ocupada por outra antena
    if (!verificaPosicaoAntena(ed, linha, coluna)) {
        printf("Erro: Ja existe uma antena em (%d, %d).\n", linha, coluna);
        return; // Sai da função sem inserir a nova antena
    }

    // Aloca memória para a nova antena
    Antena* novaAntena = (Antena*)malloc(sizeof(Antena));
    if (novaAntena == NULL) {
        perror("Erro ao alocar memoria para Antena");
        exit(EXIT_FAILURE); // Termina o programa em caso de erro de alocação
    }

    // Inicializa os valores da nova antena
    novaAntena->frequencia = freq;
    novaAntena->linha = linha;
    novaAntena->coluna = coluna;

    // Insere a nova antena no início da lista ligada
    novaAntena->prox = ed->cabeca;
    ed->cabeca = novaAntena;
}


/**
 * Função para remover uma antena com uma frequência específica numa determinada posição.
 *
 * Percorre a lista ligada de Antenas para encontrar a antena que corresponde à
 * frequência e coordenadas especificadas. Se encontrada, remove a antena da lista e
 * libera a memória associada a ela.
 *
 */
int removerAntena(ED* ed, char freq, int linha, int coluna) {

    Antena* atual = ed->cabeca;  // Ponteiro para percorrer a lista
    Antena* anterior = NULL;      // Ponteiro para manter referência ao nó anterior

    // Percorre a lista até encontrar a antena ou chegar ao final
    while (atual != NULL) {

        // Verifica se a antena atual corresponde aos critérios de remoção
        if (atual->linha == linha && atual->coluna == coluna && atual->frequencia == freq) {

            // Se a antena a ser removida for a primeira da lista
            if (anterior == NULL) {
                ed->cabeca = atual->prox;  // Atualiza a cabeça da lista
            }
            else {
                anterior->prox = atual->prox;  // Salta o nó a ser removido
            }

            free(atual);  // Liberta a memória da antena removida
            return 1;  // Retorna 1 indicando remoção bem-sucedida
        }

        // Avança para o próximo nó, mantendo o anterior registrado
        anterior = atual;
        atual = atual->prox;
    }

    return 0; // Retorna 0 caso a antena não tenha sido encontrada na lista
}


// Função para inserir uma antena manualmente
void inserirAntenaManual(ED* ed) {
    char freq;
    int linha, coluna;

    // Ler frequência
    printf("Insira a frequencia da antena (caractere) a acrescentar: ");
    scanf_s(" %c", &freq, 1);

    // Ler coordenadas
    printf("Insira a linha da antena: ");
    scanf_s("%d", &linha);

    printf("Insira a coluna da antena: ");
    scanf_s("%d", &coluna);

    // Chamar função de inserção
    insereAntena(ed, freq, linha, coluna);
}

// Função para remover uma antena manualmente
void removerAntenaManual(ED* ed) {
    char freq;
    int linha, coluna;

    // Ler frequência
    printf("Insira a frequencia da antena (caractere) a remover: ");
    scanf_s(" %c", &freq, 1);

    // Ler coordenadas
    printf("Insira a linha da antena: ");
    scanf_s("%d", &linha);

    printf("Insira a coluna da antena: ");
    scanf_s("%d", &coluna);

    // Chamar função de remoção
    removerAntena(ed, freq, linha, coluna);
}
