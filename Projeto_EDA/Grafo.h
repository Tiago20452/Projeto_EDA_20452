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
void carregarGrafoDeFicheiro(GR* grafo, ED* ed);
void inserirVertice(GR* grafo, Antena* antena);
void inserirAresta(GR* grafo, Antena* a1, Antena* a2);
void listarVertices(GR* grafo);
void listarArestas(GR* grafo);

// ---------- Funções de Busca ----------
void buscaProfundidade(GR* grafo, int linha, int coluna);

#endif // GRAFO_H
