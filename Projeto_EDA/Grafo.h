/*!
 *  @file Grafo.h
 *  @author Tiago Afonso
 *  @date 2025-05-01
 *  @project Listas Ligadas Antenas
 *
 *  Declaração das estruturas de dados para manipulação de Grafos
 */

#pragma once
#ifndef GRAFO_H
#define GRAFO_H

#include "Dados.h" // Para usar a estrutura Antena


// ---------- Funções Básicas do Grafo ----------
GR* criarGrafo();
void destruirGrafo(GR* grafo);
void carregarGrafoDeFicheiro(GR* grafo, const char* nomeFicheiro);
void inserirVertice(GR* grafo, Antena* antena);
void inserirAresta(GR* grafo, Antena* a1, Antena* a2);
void listarVertices(GR* grafo);
void listarArestas(GR* grafo);

void DFS(GR* grafo, Antena* antena);

#endif // GRAFO_H
