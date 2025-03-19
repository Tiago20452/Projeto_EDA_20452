#pragma once

#ifndef LISTAANTENAS_H
#define LISTAANTENSA_H

#include "Dados.h" // Para usar as estruturas Antena e ED

// ---------- Gestão da ED ----------
ED* criarED();
void destruirED(ED* ed);
void carregarAntenasDeFicheiro(ED* ed, const char* nomeFicheiro);
void listarAntenas(const ED* ed);


#endif // ANTENA_H