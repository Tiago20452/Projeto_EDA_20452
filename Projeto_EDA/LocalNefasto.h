#pragma once
#ifndef LOCALNEFASTO_H
#define LOCALNEFASTO_H

#include "Dados.h" // Já define ED_LocaisNefastos

// Função principal
void calcularLocaisNefastos(ED* ed, ED_LocaisNefastos* locaisNefastos);

// Função auxiliar (não declarada no .h)
void listarLocaisNefastos(const ED_LocaisNefastos* locais);

#endif // LOCALNEFASTO_H