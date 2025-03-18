// Projeto_EDA.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>

#include "Antena.h"
#include "ListaAntenas.h"

int main() {

    ED* ed = criarED();

    const char* nomeArquivo = "Antenas.txt"; 

    carregarAntenasDeFicheiro(ed, nomeArquivo); 
    listarAntenas(ed);
    destruirED(ed);
    return 0;
}
