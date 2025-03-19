#pragma once
#ifndef ANTENA_H
#define ANTENA_H

#include "Dados.h" // Para usar as estruturas Antena e ED

// ---------- Opera��es B�sicas ----------
int verificaPosicaoAntena(ED* ed, int linha, int coluna);
void insereAntena(ED* ed, char freq, int linha, int coluna);
int removerAntena(ED* ed, char freq, int linha, int coluna);

// ---------- Opera��es Avan�adas (Fase 1) ----------
void calcularLocaisNefastos(ED* ed, ED* locaisNefastos);


#endif // ANTENA_H
