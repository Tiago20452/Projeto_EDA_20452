/*!
 *  @file Antena.h
 *  @author Tiago Afonso
 *  @date 2025-03-17
 *  @project Listas Ligadas Antenas
 * 
 * Declaração de Dados e Funções para manipulação de Antenas
 */

#pragma once
#ifndef ANTENA_H
#define ANTENA_H

#include "Dados.h" // Para usar as estruturas Antena e ED

// ---------- Operações Básicas ----------
int verificaPosicaoAntena(ED* ed, int linha, int coluna);
void insereAntena(ED* ed, char freq, int linha, int coluna);
int removerAntena(ED* ed, char freq, int linha, int coluna);
void inserirAntenaManual(ED* ed);
void removerAntenaManual(ED* ed);

#endif // ANTENA_H
