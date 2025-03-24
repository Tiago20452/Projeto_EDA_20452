/*!
 *  @file Antena.cpp
 *  @author Tiago Afonso
 *  @date 2025-03-17
 *  @project Listas Ligadas Antenas
 * 
 * Resolu��o e implementa��o de fun��es para manipula��o de Antenas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Antena.h"
#include "Dados.h"

 /**
 * Fun��o para verificar se j� existe uma antena numa determinada posi��o.
 *
 * Percorre a lista ligada de antenas e verifica se alguma delas j� est�
 * na posi��o especificada (linha, coluna).
 * 
 */
int verificaPosicaoAntena(ED* ed, int linha, int coluna) {

    // Ponteiro auxiliar para percorrer a lista de antenas
    Antena* atual = ed->cabeca;

    // Percorre a lista ligada at� encontrar uma correspond�ncia ou chegar ao final
    while (atual != NULL) {

        // Verifica se a antena atual est� na mesma posi��o especificada
        if (atual->linha == linha && atual->coluna == coluna) {
            return 0; // Retorna 0 indicando que a posi��o j� est� ocupada
        }
        atual = atual->prox; // Avan�a para a pr�xima antena na lista
    }

    return 1; // Retorna 1 indicando que a posi��o est� dispon�vel
}


/**
 * Fun��o para inserir uma nova antena na lista ligada, caso a posi��o esteja dispon�vel.
 *
 * Primeiro, verifica se j� existe uma antena na posi��o especificada.
 * Se a posi��o estiver ocupada, exibe uma mensagem de erro e retorna.
 * Caso contr�rio, aloca mem�ria para uma nova antena e a insere no in�cio da lista.
 * 
 */
void insereAntena(ED* ed, char freq, int linha, int coluna) {

    // Verifica se a posi��o j� est� ocupada por outra antena
    if (!verificaPosicaoAntena(ed, linha, coluna)) {
        printf("Erro: Ja existe uma antena em (%d, %d).\n", linha, coluna);
        return; // Sai da fun��o sem inserir a nova antena
    }

    // Aloca mem�ria para a nova antena
    Antena* novaAntena = (Antena*)malloc(sizeof(Antena));
    if (novaAntena == NULL) {
        perror("Erro ao alocar memoria para Antena");
        exit(EXIT_FAILURE); // Termina o programa em caso de erro de aloca��o
    }

    // Inicializa os valores da nova antena
    novaAntena->frequencia = freq;
    novaAntena->linha = linha;
    novaAntena->coluna = coluna;

    // Insere a nova antena no in�cio da lista ligada
    novaAntena->prox = ed->cabeca;
    ed->cabeca = novaAntena;
}


/**
 * Fun��o para remover uma antena com uma frequ�ncia espec�fica numa determinada posi��o.
 *
 * Percorre a lista ligada de Antenas para encontrar a antena que corresponde �
 * frequ�ncia e coordenadas especificadas. Se encontrada, remove a antena da lista e
 * libera a mem�ria associada a ela.
 *
 */
int removerAntena(ED* ed, char freq, int linha, int coluna) {

    Antena* atual = ed->cabeca;  // Ponteiro para percorrer a lista
    Antena* anterior = NULL;      // Ponteiro para manter refer�ncia ao n� anterior

    // Percorre a lista at� encontrar a antena ou chegar ao final
    while (atual != NULL) {

        // Verifica se a antena atual corresponde aos crit�rios de remo��o
        if (atual->linha == linha && atual->coluna == coluna && atual->frequencia == freq) {

            // Se a antena a ser removida for a primeira da lista
            if (anterior == NULL) {
                ed->cabeca = atual->prox;  // Atualiza a cabe�a da lista
            }
            else {
                anterior->prox = atual->prox;  // Salta o n� a ser removido
            }

            free(atual);  // Liberta a mem�ria da antena removida
            return 1;  // Retorna 1 indicando remo��o bem-sucedida
        }

        // Avan�a para o pr�ximo n�, mantendo o anterior registrado
        anterior = atual;
        atual = atual->prox;
    }

    return 0; // Retorna 0 caso a antena n�o tenha sido encontrada na lista
}


// Fun��o para inserir uma antena manualmente
void inserirAntenaManual(ED* ed) {
    char freq;
    int linha, coluna;

    // Ler frequ�ncia
    printf("Insira a frequencia da antena (caractere) a acrescentar: ");
    scanf_s(" %c", &freq, 1);

    // Ler coordenadas
    printf("Insira a linha da antena: ");
    scanf_s("%d", &linha);

    printf("Insira a coluna da antena: ");
    scanf_s("%d", &coluna);

    // Chamar fun��o de inser��o
    insereAntena(ed, freq, linha, coluna);
}

// Fun��o para remover uma antena manualmente
void removerAntenaManual(ED* ed) {
    char freq;
    int linha, coluna;

    // Ler frequ�ncia
    printf("Insira a frequencia da antena (caractere) a remover: ");
    scanf_s(" %c", &freq, 1);

    // Ler coordenadas
    printf("Insira a linha da antena: ");
    scanf_s("%d", &linha);

    printf("Insira a coluna da antena: ");
    scanf_s("%d", &coluna);

    // Chamar fun��o de remo��o
    removerAntena(ed, freq, linha, coluna);
}
