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

#endif // GRAFO_H
