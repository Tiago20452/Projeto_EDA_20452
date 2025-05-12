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
  * Função para criar uma nova lista ligada vazia.
  *
  * Aloca dinamicamente memória para a estrutura ED e inicializa a cabeça da lista como NULL.
  * Em caso de falha na alocação de memória, exibe uma mensagem de erro e encerra o programa.
  *
 */
GR* criarGrafo() {
    GR* grafo = (GR*)malloc(sizeof(GR));
    if (grafo == NULL) {
        perror("Erro ao alocar memória para o grafo");
        exit(EXIT_FAILURE);
    }
    grafo->vertices = NULL;
    grafo->num_vertices = 0;
    return grafo;
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
  * Função para carregar um grafo a partir de um ficheiro de texto.
  *
  * Lê as antenas do ficheiro e as insere como vértices no grafo.
  * Cria arestas entre antenas que compartilham a mesma frequência.
  *
 */
void carregarGrafoDeFicheiro(GR* grafo, const char* nomeFicheiro) {
    ED* ed = criarED();
    int max_linhas, max_colunas;

    // Carrega antenas para a ED da Fase 1
    carregarAntenasDeFicheiro(ed, nomeFicheiro, &max_linhas, &max_colunas);

    // Insere todas as antenas como vértices
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        inserirVertice(grafo, atual);
        atual = atual->prox;
    }

    // Cria arestas entre antenas da mesma frequência
    atual = ed->cabeca;
    while (atual != NULL) {
        Antena* outra = atual->prox;
        while (outra != NULL) {
            if (atual->frequencia == outra->frequencia) {
                inserirAresta(grafo, atual, outra);
            }
            outra = outra->prox;
        }
        atual = atual->prox;
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
  * Adiciona cada vértice à lista de adjacências do outro.
  *
 */
void inserirAresta(GR* grafo, Antena* a1, Antena* a2) {
    if (grafo == NULL || a1 == NULL || a2 == NULL) return;

    Vertice* v1 = NULL, * v2 = NULL;

    // Encontra os vértices correspondentes às antenas
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (grafo->vertices[i]->antena == a1) v1 = grafo->vertices[i];
        if (grafo->vertices[i]->antena == a2) v2 = grafo->vertices[i];
    }

    // Se ambos os vértices existirem e tiverem a mesma frequência
    if (v1 && v2 && v1->antena->frequencia == v2->antena->frequencia) {
        // ---- Adiciona v2 à lista de adjacências de v1 ----
        Vertice** nova_adj_v1 = (Vertice**)realloc(
            v1->adjacencias,
            (v1->num_adjacencias + 1) * sizeof(Vertice*)
        );

        if (nova_adj_v1 == NULL) {
            perror("Erro ao realocar memória para adjacências de v1");
            return;
        }
        v1->adjacencias = nova_adj_v1;
        v1->adjacencias[v1->num_adjacencias++] = v2;

        // ---- Adiciona v1 à lista de adjacências de v2 ----
        Vertice** nova_adj_v2 = (Vertice**)realloc(
            v2->adjacencias,
            (v2->num_adjacencias + 1) * sizeof(Vertice*)
        );

        if (nova_adj_v2 == NULL) {
            // Desfaz a alteração em v1 para manter consistência
            v1->adjacencias = (Vertice**)realloc(
                v1->adjacencias,
                (v1->num_adjacencias - 1) * sizeof(Vertice*)
            );
            v1->num_adjacencias--;

            perror("Erro ao realocar memória para adjacências de v2");
            return;
        }
        v2->adjacencias = nova_adj_v2;
        v2->adjacencias[v2->num_adjacencias++] = v1;
    }
}

/**
  * Função para listar os vértices do grafo em ordem decrescente de linha e crescente de coluna.
  *
  * Cria um array temporário para armazenar os ponteiros dos vértices, ordena-os e exibe as informações.
  *
 */
void listarVertices(GR* grafo) {
    if (grafo == NULL || grafo->num_vertices == 0) {
        printf("Nenhum vértice no grafo.\n");
        return;
    }

    // Passo 1: Copiar os vértices para um array
    Vertice** arrayVertices = (Vertice**)malloc(grafo->num_vertices * sizeof(Vertice*));
    for (int i = 0; i < grafo->num_vertices; i++) {
        arrayVertices[i] = grafo->vertices[i];
    }

    // Passo 2: Ordenar por linha (decrescente) e coluna (crescente)
    qsort(arrayVertices, grafo->num_vertices, sizeof(Vertice*),
        [](const void* a, const void* b) -> int {
            Vertice* vA = *(Vertice**)a;
            Vertice* vB = *(Vertice**)b;

            // Ordenação decrescente por linha
            if (vA->antena->linha != vB->antena->linha) {
                return vB->antena->linha - vA->antena->linha;
            }

            // Ordenação crescente por coluna
            return vA->antena->coluna - vB->antena->coluna;
        });

    // Passo 3: Exibir os vértices ordenados
    printf("=== Vértices do Grafo (Ordenados) ===\n");
    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("Antena '%c' em (%d, %d)\n",
            arrayVertices[i]->antena->frequencia,
            arrayVertices[i]->antena->linha,
            arrayVertices[i]->antena->coluna);
    }
    printf("====================================\n");

    // Passo 4: Liberar memória
    free(arrayVertices);
}

/**
  * Função para listar as arestas do grafo.
  *
  * Percorre todos os vértices e exibe suas adjacências.
  *
 */
void listarArestas(GR* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        Vertice* v = grafo->vertices[i];
        printf("%c(%d, %d) esta conectado a:\n",
            v->antena->frequencia,
            v->antena->linha,
            v->antena->coluna);
        for (int j = 0; j < v->num_adjacencias; j++) {
            Vertice* vizinho = v->adjacencias[j];
            printf("  - %c(%d, %d)\n",
                vizinho->antena->frequencia,
                vizinho->antena->linha,
                vizinho->antena->coluna);
        }
    }
}


// Função auxiliar para DFS recursiva
static void DFSUtil(Vertice* v, bool visitados[]) {
    visitados[v->id] = true; // Marca como visitado
    printf("Antena '%c' em (%d, %d)\n",
        v->antena->frequencia,
        v->antena->linha,
        v->antena->coluna);

    // Visita todos os vértices adjacentes não visitados
    for (int i = 0; i < v->num_adjacencias; i++) {
        Vertice* vizinho = v->adjacencias[i];
        if (!visitados[vizinho->id]) {
            DFSUtil(vizinho, visitados);
        }
    }
}


// Função principal para DFS a partir de uma antena específica
void DFS(GR* grafo, Antena* antena) {
    if (grafo == NULL || antena == NULL) {
        printf("Parâmetros inválidos.\n");
        return;
    }

    // Encontra o vértice correspondente à antena
    Vertice* verticeInicio = NULL;
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (grafo->vertices[i]->antena == antena) {
            verticeInicio = grafo->vertices[i];
            break;
        }
    }

    if (verticeInicio == NULL) {
        printf("Antena não encontrada no grafo.\n");
        return;
    }

    // Inicializa array de visitados
    bool* visitados = (bool*)calloc(grafo->num_vertices, sizeof(bool));
    DFSUtil(verticeInicio, visitados);
    free(visitados);
}