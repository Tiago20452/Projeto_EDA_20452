#pragma once
#ifndef ANTENA_H
#define ANTENA_H

#include "Dados.h" // Para usar as estruturas Antena e ED

// ---------- Gest�o da ED ----------
ED* criarED();
void destruirED(ED* ed);

// ---------- Opera��es B�sicas ----------
void inserirAntena(ED* ed, char freq, int linha, int coluna);
int removerAntena(ED* ed, int linha, int coluna);

// ---------- Opera��es Avan�adas (Fase 1) ----------
void carregarAntenasDeFicheiro(ED* ed, const char* nomeFicheiro);
void calcularLocaisNefastos(ED* ed, ED* locaisNefastos);
void listarAntenas(const ED* ed);



#endif // ANTENA_H
