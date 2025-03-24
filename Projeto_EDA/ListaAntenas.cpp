/*!
 *  @file ListaAntenas.cpp
 *  @author Tiago Afonso
 *  @date 2025-03-18
 *  @project Listas Ligadas Antenas
 *
 *  Resolu��o e implementa��o de Fun��es para manipula��o de uma Lista de Antenas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaAntenas.h"
#include "Antena.h"
#include "Dados.h"

 /**
  * Fun��o para criar uma nova lista ligada vazia.
  *
  * Aloca dinamicamente mem�ria para a estrutura ED e inicializa a cabe�a da lista como NULL.
  * Em caso de falha na aloca��o de mem�ria, exibe uma mensagem de erro e encerra o programa.
  *
  */
ED* criarED() {
    // Aloca mem�ria para a estrutura ED
    ED* ed = (ED*)malloc(sizeof(ED));
    if (ed == NULL) {
        perror("Erro ao alocar mem�ria para ED");
        exit(EXIT_FAILURE); // Encerra o programa em caso de erro na aloca��o
    }

    ed->cabeca = NULL; // Inicializa a lista como vazia
    return ed; // Retorna o ponteiro para a estrutura criada
}


/**
 * Fun��o para libertar toda a mem�ria alocada para a lista ligada de antenas.
 *
 * Percorre a lista ligada, libertando a mem�ria de cada n� (antena) individualmente.
 * No final, liberta a mem�ria da estrutura ED.
 *
 */
void destruirED(ED* ed) {
    Antena* atual = ed->cabeca;  // Ponteiro para percorrer a lista

    // Percorre a lista, liberando a mem�ria de cada antena
    while (atual != NULL) {
        Antena* prox = atual->prox; // Guarda refer�ncia para o pr�ximo n�
        free(atual);  // Liberta a mem�ria da antena atual
        atual = prox; // Avan�a para o pr�ximo n�
    }

    free(ed); // Liberta a mem�ria da estrutura ED
}


/**
 * Fun��o para carregar antenas a partir de um ficheiro de texto e armazen�-las em uma lista ligada.
 *
 * O ficheiro deve conter uma matriz de caracteres, onde cada c�lula pode conter:
 * - Um caractere representando uma antena (por exemplo, 'A', 'O').
 * - O caractere '.' indicando uma posi��o vazia.
 *
 * A fun��o determina automaticamente o n�mero m�ximo de linhas e colunas do ficheiro.
 * Cada antena encontrada � inserida na estrutura ED.
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

    // L� o ficheiro linha por linha
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        size_t comprimento = strlen(buffer);

        // Remove o caractere de nova linha ('\n') se presente
        if (comprimento > 0 && buffer[comprimento - 1] == '\n') {
            buffer[comprimento - 1] = '\0';
            comprimento--;
        }

        // Atualiza o n�mero m�ximo de colunas encontrado
        if (comprimento > *max_colunas) {
            *max_colunas = comprimento;
        }

        // Processa cada caractere da linha
        for (int coluna = 0; coluna < comprimento; coluna++) {
            if (buffer[coluna] != '.') {  // Se n�o for '.', � uma antena
                insereAntena(ed, buffer[coluna], linhaAtual, coluna);
            }
        }

        linhaAtual++;  // Avan�a para a pr�xima linha
    }

    *max_linhas = linhaAtual;  // Atualiza o n�mero total de linhas lidas
    fclose(arquivo);  // Fecha o ficheiro ap�s a leitura
}


/**
 * Fun��o para listar as antenas ordenadas de forma decrescente por linha.
 *
 * A fun��o percorre a lista ligada para contar o n�mero de antenas, armazena os ponteiros
 * num array e utiliza `qsort` para ordenar as antenas pela linha de forma decrescente.
 * Em caso de empate nas linhas, a ordena��o � feita pela coluna em ordem crescente.
 *
 */
void listarAntenas(const ED* ed) {
    // Passo 1: Contar o n�mero total de antenas na lista
    int numAntenas = 0;
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        numAntenas++;
        atual = atual->prox;
    }

    // Passo 2: Alocar um array de ponteiros para armazenar as antenas
    Antena** arrayAntenas = (Antena**)malloc(numAntenas * sizeof(Antena*));
    if (arrayAntenas == NULL) {
        perror("Erro ao alocar mem�ria");
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

            // Ordena��o decrescente por linha
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

    // Passo 6: Libertar a mem�ria alocada para o array de ponteiros
    free(arrayAntenas);
}


/**
 * Fun��o para listar as antenas em formato de matriz, semelhante ao ficheiro de entrada.
 *
 * A fun��o aloca dinamicamente uma matriz de caracteres, preenche-a com '.' para indicar
 * espa�os vazios e substitui essas posi��es pelos caracteres das antenas conforme a lista ligada.
 * A matriz formatada �  impressa na consola.
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
        perror("Erro ao alocar mem�ria para a matriz");
        exit(EXIT_FAILURE);
    }

    // Alocar e inicializar cada linha da matriz
    for (int i = 0; i < max_linhas; i++) {
        matriz[i] = (char*)malloc((max_colunas + 1) * sizeof(char)); // +1 para '\0'
        if (matriz[i] == NULL) {
            perror("Erro ao alocar mem�ria para uma linha da matriz");
            exit(EXIT_FAILURE);
        }
        // Preencher a linha com '.' e adicionar o terminador de string '\0'
        for (int j = 0; j < max_colunas; j++) {
            matriz[i][j] = '.';
        }
        matriz[i][max_colunas] = '\0';
    }

    // Percorrer a lista de antenas e marcar suas posi��es na matriz
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
        free(matriz[i]); // Libera a mem�ria da linha ap�s a impress�o
    }

    // Liberar mem�ria alocada para o array de ponteiros
    free(matriz);
    printf("=======================\n");
}
