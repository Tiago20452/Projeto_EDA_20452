#pragma once

#ifndef LISTAANTENAS_H
#define LISTAANTENSA_H

#include "Dados.h" // Para usar as estruturas Antena e ED

// ---------- Gestão da ED ----------
ED* criarED();
void destruirED(ED* ed);
void carregarAntenasDeFicheiro(ED* ed, const char* nomeFicheiro, int* max_linhas, int* max_colunas);
void listarAntenas(const ED* ed);
void listarAntenasFormatado(const ED* ed, int max_linhas, int max_colunas);


#endif // ANTENA_H