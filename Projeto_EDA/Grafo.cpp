/*!
 *  @file Grafo.cpp
 *  @author Tiago Afonso
 *  @date 2025-05-01
 *  @project Listas Ligadas Antenas
 *
 * Resolução e implementação de funções para manipulação de Antenas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"
#include "Dados.h"
#include "ListaAntenas.h"
#include "Antena.h"

 /**
  * Função para criar uma nova estrutura de grafo vazia.
  *
  * Aloca dinamicamente memória para a estrutura GR e inicializa seus componentes básicos.
  * Em caso de falha na alocação de memória, exibe uma mensagem de erro e encerra o programa.
  * Retorna um ponteiro para o grafo criado.
  *
  */
GR* criarGrafo() {
    // Aloca memória para a estrutura do grafo
    GR* grafo = (GR*)malloc(sizeof(GR));

    // Verifica se a alocação de memória foi bem-sucedida
    if (grafo == NULL) {
        perror("Erro ao alocar memória para o grafo"); // Exibe mensagem de erro
        exit(EXIT_FAILURE); // Encerra o programa com código de falha
    }

    // Inicializa a lista de vértices como NULL (grafo vazio)
    grafo->vertices = NULL;

    // Define o número inicial de vértices como zero
    grafo->num_vertices = 0;

    return grafo; // Retorna o ponteiro para o grafo recém-criado
}

/**
  * Função para libertar toda a memória alocada para o grafo.
  *
  * Percorre todos os vértices do grafo, libertando a memória de cada um deles e suas adjacências.
  * No final, liberta a memória da estrutura do grafo.
  *
 */
void destruirGrafo(GR* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        free(grafo->vertices[i]->adjacencias);
        free(grafo->vertices[i]);
    }
    free(grafo->vertices);
    free(grafo);
}

/**
 * Função para carregar um grafo a partir de uma estrutura de dados de antenas (ED).
 *
 * Percorre a lista ligada de antenas e insere cada antena como um vértice no grafo.
 * Em seguida, cria arestas entre todas as antenas que compartilham a mesma frequência de ressonância.
 *
 */
void carregarGrafoDeFicheiro(GR* grafo, ED* ed) {

    // Percorre a lista ligada de antenas e adiciona cada uma como vértice no grafo
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        inserirVertice(grafo, atual); // Insere a antena atual como vértice
        atual = atual->prox; // Avança para a próxima antena na lista
    }

    atual = ed->cabeca; // Reinicia o ponteiro para o início da lista
    while (atual != NULL) {
        Antena* outra = atual->prox; // Ponteiro auxiliar para comparar com as antenas seguintes
        while (outra != NULL) {
            // Verifica se as antenas atual e 'outra' têm a mesma frequência
            if (atual->frequencia == outra->frequencia) {
                inserirAresta(grafo, atual, outra); // Cria aresta entre as antenas
            }
            outra = outra->prox; // Avança para a próxima antena na lista
        }
        atual = atual->prox; // Avança para a próxima antena principal
    }
}

/**
  * Função para inserir um vértice (antena) no grafo.
  *
  * Verifica se a antena já existe no grafo antes de inseri-la.
  * Se não existir, aloca memória para o novo vértice e o adiciona ao grafo.
  *
 */
void inserirVertice(GR* grafo, Antena* antena) {
    // Verifica se a antena já está no grafo
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (grafo->vertices[i]->antena == antena) {
            return; // Antena já existe, não faz nada
        }
    }

    // Aloca memória para o novo vértice
    Vertice* novo = (Vertice*)malloc(sizeof(Vertice));
    if (novo == NULL) {
        perror("Erro ao alocar memória para o vértice");
        exit(EXIT_FAILURE);
    }

    // Inicializa os campos do novo vértice
    novo->antena = antena;
    novo->adjacencias = NULL;
    novo->num_adjacencias = 0;

    // Redimensiona o array de vértices do grafo
    Vertice** temp = (Vertice**)realloc(
        grafo->vertices,
        (grafo->num_vertices + 1) * sizeof(Vertice*)
    );

    if (temp == NULL) {
        free(novo); // Libera o vértice recém-criado
        perror("Erro ao realocar memória para os vértices");
        exit(EXIT_FAILURE);
    }

    // Atualiza o array de vértices e o contador
    grafo->vertices = temp;
    grafo->vertices[grafo->num_vertices] = novo;
    grafo->num_vertices++;
}

/**
 * Função para inserir uma aresta entre dois vértices (antenas) no grafo.
 *
 * Verifica se ambos os vértices existem e têm a mesma frequência antes de criar a aresta.
 * Adiciona cada vértice à lista de adjacências do outro (grafo não direcionado).
 */
void inserirAresta(GR* grafo, Antena* a1, Antena* a2) {

    // Se o grafo ou qualquer uma das antenas for nulo, a função termina sem fazer nada
    if (grafo == NULL || a1 == NULL || a2 == NULL) return;

    Vertice* v1 = NULL, * v2 = NULL;

    // Percorre todos os vértices do grafo para identificar os que correspondem às antenas a1 e a2
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (grafo->vertices[i]->antena == a1) v1 = grafo->vertices[i];
        if (grafo->vertices[i]->antena == a2) v2 = grafo->vertices[i];
    }

    // A aresta só é inserida se ambos os vértices forem encontrados
    // e as antenas tiverem a mesma frequência
    if (v1 && v2 && v1->antena->frequencia == v2->antena->frequencia) {

        // Adiciona v2 à lista de adjacências de v1
        Vertice** nova_adj_v1 = (Vertice**)realloc(
            v1->adjacencias,
            (v1->num_adjacencias + 1) * sizeof(Vertice*)
        );

        // Verifica se a realocação de memória falhou
        if (nova_adj_v1 == NULL) {
            perror("Erro ao realocar memória para adjacências de v1");
            return;
        }

        // Actualiza a lista de adjacências de v1 e incrementa o número de adjacências
        v1->adjacencias = nova_adj_v1;
        v1->adjacencias[v1->num_adjacencias++] = v2;

        // Adiciona v1 à lista de adjacências de v2 
        Vertice** nova_adj_v2 = (Vertice**)realloc(
            v2->adjacencias,
            (v2->num_adjacencias + 1) * sizeof(Vertice*)
        );

        // Verifica se a realocação de memória falhou
        if (nova_adj_v2 == NULL) {
            // Desfaz a alteração feita anteriormente em v1 para manter a consistência
            v1->adjacencias = (Vertice**)realloc(
                v1->adjacencias,
                (v1->num_adjacencias - 1) * sizeof(Vertice*)
            );
            v1->num_adjacencias--;

            perror("Erro ao realocar memória para adjacências de v2");
            return;
        }

        // Actualiza a lista de adjacências de v2 e incrementa o número de adjacências
        v2->adjacencias = nova_adj_v2;
        v2->adjacencias[v2->num_adjacencias++] = v1;
    }
}


/**
 * Função para listar os vértices do grafo por ordem decrescente da linha e crescente da coluna.
 *
 * A função cria um array temporário com os ponteiros para os vértices,
 * ordena-os segundo os critérios especificados e imprime a informação de cada antena.
 */
void listarVertices(GR* grafo) {

    // Verifica se o grafo é válido e contém vértices
    if (grafo == NULL || grafo->num_vertices == 0) {
        printf("Nenhum vertice no grafo.\n");
        return;
    }

    // Copia os ponteiros dos vértices para um array auxiliar
    Vertice** arrayVertices = (Vertice**)malloc(grafo->num_vertices * sizeof(Vertice*));
    for (int i = 0; i < grafo->num_vertices; i++) {
        arrayVertices[i] = grafo->vertices[i];
    }

    // Ordena o array de vértices:
    // - Primeiro por linha (ordem decrescente)
    // - Em caso de empate, por coluna (ordem crescente)
    qsort(arrayVertices, grafo->num_vertices, sizeof(Vertice*),
        [](const void* a, const void* b) -> int {
            Vertice* vA = *(Vertice**)a;
            Vertice* vB = *(Vertice**)b;

            if (vA->antena->linha != vB->antena->linha) {
                return vB->antena->linha - vA->antena->linha;
            }

            return vA->antena->coluna - vB->antena->coluna;
        });

    // Imprime os vértices ordenados com as suas respetivas posições e frequências
    printf("=== Vertices do Grafo (Ordenados) ===\n");
    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("Antena '%c' em (%d, %d)\n",
            arrayVertices[i]->antena->frequencia,
            arrayVertices[i]->antena->linha,
            arrayVertices[i]->antena->coluna);
    }
    printf("====================================\n");

    // Liberta a memória alocada para o array auxiliar
    free(arrayVertices);
}


/**
 * Função para listar as arestas do grafo.
 *
 * Percorre todos os vértices e imprime as antenas às quais cada um está ligado.
 */
void listarArestas(GR* grafo) {

    // Verifica se o grafo é válido
    if (grafo == NULL || grafo->num_vertices == 0) {
        printf("Grafo vazio ou inválido.\n");
        return;
    }

    // Percorre todos os vértices do grafo
    for (int i = 0; i < grafo->num_vertices; i++) {
        Vertice* v = grafo->vertices[i];

        // Imprime a antena do vértice atual
        printf("%c(%d, %d) está conectado a:\n",
            v->antena->frequencia,
            v->antena->linha,
            v->antena->coluna);

        // Percorre e imprime as antenas vizinhas (adjacentes)
        for (int j = 0; j < v->num_adjacencias; j++) {
            Vertice* vizinho = v->adjacencias[j];
            printf("  - %c(%d, %d)\n",
                vizinho->antena->frequencia,
                vizinho->antena->linha,
                vizinho->antena->coluna);
        }
    }
}


/**
 * Função auxiliar recursiva para realizar a Procura por Profundidade.
 *
 */
void auxProfundidade(Vertice* v, bool visitado[]) {

    // Marca o vértice atual como visitado
    // Utiliza uma hash simples com base nas coordenadas (linha * 1000 + coluna)
    visitado[v->antena->linha * 1000 + v->antena->coluna] = true;

    // Imprime a informação da antena visitada
    printf("Antena '%c' em (%d, %d)\n",
        v->antena->frequencia,
        v->antena->linha,
        v->antena->coluna);

    // Percorre os vizinhos do vértice
    for (int i = 0; i < v->num_adjacencias; i++) {
        Vertice* vizinho = v->adjacencias[i];

        // Calcula o índice hash do vizinho
        int hash = vizinho->antena->linha * 1000 + vizinho->antena->coluna;

        // Visita o vizinho se ainda não tiver sido visitado
        if (!visitado[hash]) {
            auxProfundidade(vizinho, visitado);
        }
    }
}


/**
 * 
 * Função para iniciar a busca em profundidade (DFS) no grafo a partir de uma antena específica.
 *
 */
void buscaProfundidade(GR* grafo, int linha, int coluna) {

    // Verifica se o grafo é válido e contém vértices
    if (grafo == NULL || grafo->num_vertices == 0) {
        printf("Grafo vazio ou invalido.\n");
        return;
    }

    // Procura o vértice correspondente às coordenadas fornecidas
    Vertice* inicio = NULL;
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (grafo->vertices[i]->antena->linha == linha &&
            grafo->vertices[i]->antena->coluna == coluna) {
            inicio = grafo->vertices[i];
            break;
        }
    }

    // Se não encontrar o vértice, informa o utilizador e termina
    if (inicio == NULL) {
        printf("Antena em (%d, %d) não encontrada.\n", linha, coluna);
        return;
    }

    // Cria e inicializa o array de visitados, utilizando uma hash simples baseada nas coordenadas
    // Assume que as coordenadas máximas são até 999x999
    bool visitado[1000000] = { false };

    // Inicia a procura a partir do vértice encontrado
    auxProfundidade(inicio, visitado);
}


