/*!
 *  @file LocalNefasto.h
 *  @author Tiago Afonso
 *  @date 2025-03-20
 *  @project Listas Ligadas Antenas
 *
 *
 */
#pragma once
#ifndef LOCALNEFASTO_H
#define LOCALNEFASTO_H

#include "Dados.h" // Já define ED_LocaisNefastos

// Função principal
void calcularLocaisNefastos(ED* ed, ED_LocaisNefastos* locaisNefastos, int max_linhas, int max_colunas);	

// Função auxiliar (não declarada no .h)
void listarLocaisNefastos(const ED_LocaisNefastos* locais);

void listarLocaisNefastosFormatado(const ED_LocaisNefastos* locais, int max_linhas, int max_colunas);

#endif // LOCALNEFASTO_H