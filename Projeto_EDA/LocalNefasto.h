/*!
 *  @file LocalNefasto.h
 *  @author Tiago Afonso
 *  @date 2025-03-20
 *  @project Listas Ligadas Antenas
 *
 *  Declaração de Dados e Funções para manipulação de Locais Nefastos
 */
#pragma once
#ifndef LOCALNEFASTO_H
#define LOCALNEFASTO_H

#include "Dados.h" 

void calcularLocaisNefastos(ED* ed, ED_LocaisNefastos* locaisNefastos, int max_linhas, int max_colunas);	

void listarLocaisNefastos(const ED_LocaisNefastos* locais);

void listarLocaisNefastosFormatado(const ED_LocaisNefastos* locais, int max_linhas, int max_colunas);

#endif // LOCALNEFASTO_H

