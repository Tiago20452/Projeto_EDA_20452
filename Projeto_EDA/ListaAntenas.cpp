/*!
 *  @file ListaAntenas.cpp
 *  @author Tiago Afonso
 *  @date 2025-03-18
 *  @project Listas Ligadas Antenas
 *
 *  Resolução e implementação de Funções para manipulação de uma Lista de Antenas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaAntenas.h"
#include "Antena.h"
#include "Dados.h"

 /**
  * Função para criar uma nova lista ligada vazia.
  *
  * Aloca dinamicamente memória para a estrutura ED e inicializa a cabeça da lista como NULL.
  * Em caso de falha na alocação de memória, exibe uma mensagem de erro e encerra o programa.
  *
  */
ED* criarED() {
    // Aloca memória para a estrutura ED
    ED* ed = (ED*)malloc(sizeof(ED));
    if (ed == NULL) {
        perror("Erro ao alocar memória para ED");
        exit(EXIT_FAILURE); // Encerra o programa em caso de erro na alocação
    }

    ed->cabeca = NULL; // Inicializa a lista como vazia
    return ed; // Retorna o ponteiro para a estrutura criada
}


/**
 * Função para libertar toda a memória alocada para a lista ligada de antenas.
 *
 * Percorre a lista ligada, libertando a memória de cada nó (antena) individualmente.
 * No final, liberta a memória da estrutura ED.
 *
 */
void destruirED(ED* ed) {
    Antena* atual = ed->cabeca;  // Ponteiro para percorrer a lista

    // Percorre a lista, liberando a memória de cada antena
    while (atual != NULL) {
        Antena* prox = atual->prox; // Guarda referência para o próximo nó
        free(atual);  // Liberta a memória da antena atual
        atual = prox; // Avança para o próximo nó
    }

    free(ed); // Liberta a memória da estrutura ED
}


/**
 * Função para carregar antenas a partir de um ficheiro de texto e armazená-las em uma lista ligada.
 *
 * O ficheiro deve conter uma matriz de caracteres, onde cada célula pode conter:
 * - Um caractere representando uma antena (por exemplo, 'A', 'O').
 * - O caractere '.' indicando uma posição vazia.
 *
 * A função determina automaticamente o número máximo de linhas e colunas do ficheiro.
 * Cada antena encontrada é inserida na estrutura ED.
 */
void carregarAntenasDeFicheiro(ED* ed, const char* nomeFicheiro, int* max_linhas, int* max_colunas) {
    FILE* arquivo = NULL;

    // Abre o ficheiro para leitura
    errno_t err = fopen_s(&arquivo, nomeFicheiro, "r");
    if (err != 0 || arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char buffer[1024];  // Buffer para armazenar cada linha lida do ficheiro
    int linhaAtual = 0;
    *max_colunas = 0;

    // Lê o ficheiro linha por linha
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        size_t comprimento = strlen(buffer);

        // Remove o caractere de nova linha ('\n') se presente
        if (comprimento > 0 && buffer[comprimento - 1] == '\n') {
            buffer[comprimento - 1] = '\0';
            comprimento--;
        }

        // Atualiza o número máximo de colunas encontrado
        if (comprimento > *max_colunas) {
            *max_colunas = comprimento;
        }

        // Processa cada caractere da linha
        for (int coluna = 0; coluna < comprimento; coluna++) {
            if (buffer[coluna] != '.') {  // Se não for '.', é uma antena
                insereAntena(ed, buffer[coluna], linhaAtual, coluna);
            }
        }

        linhaAtual++;  // Avança para a próxima linha
    }

    *max_linhas = linhaAtual;  // Atualiza o número total de linhas lidas
    fclose(arquivo);  // Fecha o ficheiro após a leitura
}


/**
 * Função para listar as antenas ordenadas de forma decrescente por linha.
 *
 * A função percorre a lista ligada para contar o número de antenas, armazena os ponteiros
 * num array e utiliza `qsort` para ordenar as antenas pela linha de forma decrescente.
 * Em caso de empate nas linhas, a ordenação é feita pela coluna em ordem crescente.
 *
 */
void listarAntenas(const ED* ed) {
    // Passo 1: Contar o número total de antenas na lista
    int numAntenas = 0;
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        numAntenas++;
        atual = atual->prox;
    }

    // Passo 2: Alocar um array de ponteiros para armazenar as antenas
    Antena** arrayAntenas = (Antena**)malloc(numAntenas * sizeof(Antena*));
    if (arrayAntenas == NULL) {
        perror("Erro ao alocar memória");
        return;
    }

    // Passo 3: Preencher o array com as antenas da lista ligada
    atual = ed->cabeca;
    for (int i = 0; i < numAntenas; i++) {
        arrayAntenas[i] = atual;
        atual = atual->prox;
    }

    // Passo 4: Ordenar as antenas primeiro por linha (decrescente), depois por coluna (crescente)
    qsort(arrayAntenas, numAntenas, sizeof(Antena*),
        [](const void* a, const void* b) -> int {
            Antena* antenaA = *(Antena**)a;
            Antena* antenaB = *(Antena**)b;

            // Ordenação decrescente por linha
            if (antenaA->linha != antenaB->linha) {
                return antenaB->linha - antenaA->linha; // Inverter a ordem
            }

            // Se as linhas forem iguais, ordenar por coluna de forma crescente
            return antenaA->coluna - antenaB->coluna;
        });

    // Passo 5: Exibir a lista de antenas ordenadas
    printf("=== Lista de Antenas (Ordenadas) ===\n");
    for (int i = 0; i < numAntenas; i++) {
        printf("Antena '%c' em (%d, %d)\n",
            arrayAntenas[i]->frequencia,
            arrayAntenas[i]->linha,
            arrayAntenas[i]->coluna);
    }
    printf("====================================\n");

    // Passo 6: Libertar a memória alocada para o array de ponteiros
    free(arrayAntenas);
}


/**
 * Função para listar as antenas em formato de matriz, semelhante ao ficheiro de entrada.
 *
 * A função aloca dinamicamente uma matriz de caracteres, preenche-a com '.' para indicar
 * espaços vazios e substitui essas posições pelos caracteres das antenas conforme a lista ligada.
 * A matriz formatada é  impressa na consola.
 *
 */
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

    // Alocar e inicializar cada linha da matriz
    for (int i = 0; i < max_linhas; i++) {
        matriz[i] = (char*)malloc((max_colunas + 1) * sizeof(char)); // +1 para '\0'
        if (matriz[i] == NULL) {
            perror("Erro ao alocar memória para uma linha da matriz");
            exit(EXIT_FAILURE);
        }
        // Preencher a linha com '.' e adicionar o terminador de string '\0'
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
            matriz[atual->linha][atual->coluna] = atual->frequencia; // Marca a antena na matriz
        }
        atual = atual->prox;
    }

    // Imprimir a matriz formatada na consola
    printf("=== Mapa de Antenas ===\n");
    for (int i = 0; i < max_linhas; i++) {
        printf("%s\n", matriz[i]); // Imprime cada linha da matriz
        free(matriz[i]); // Libera a memória da linha após a impressão
    }

    // Liberar memória alocada para o array de ponteiros
    free(matriz);
    printf("=======================\n");
}
