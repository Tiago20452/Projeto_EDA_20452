// Projeto_EDA.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>

#include "Antena.h"

int main() {
    ED* ed = criarED();
    const char* nomeArquivo = "Antenas.txt"; // Define o nome do arquivo aqui
    carregarAntenasDeFicheiro(ed, nomeArquivo); // Passa o nome como argumento
    listarAntenas(ed);
    destruirED(ed);
    return 0;
}
