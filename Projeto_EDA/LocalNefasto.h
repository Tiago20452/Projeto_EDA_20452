#pragma once
#ifndef LOCALNEFASTO_H
#define LOCALNEFASTO_H

#include "Dados.h" // J� define ED_LocaisNefastos

// Fun��o principal
void calcularLocaisNefastos(ED* ed, ED_LocaisNefastos* locaisNefastos);

// Fun��o auxiliar (n�o declarada no .h)
void listarLocaisNefastos(const ED_LocaisNefastos* locais);

#endif // LOCALNEFASTO_H