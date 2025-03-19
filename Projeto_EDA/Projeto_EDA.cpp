// Projeto_EDA.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Antena.h"
#include "ListaAntenas.h"


int main() {

    char freq;
	int linha, coluna;

    const char* nomeArquivo = "Antenas.txt";
    ED* ed = criarED();

    carregarAntenasDeFicheiro(ed, nomeArquivo); 
    listarAntenas(ed);

	removerAntena(ed,'O', 5, 5);

    listarAntenas(ed);

	//Inserir uma antena manualmente

    printf("Insira a frequência da antena (caractere): ");
    scanf_s(" %c", &freq, 1); 

    printf("Insira a linha da antena: ");
    scanf_s("%d", &linha);

    printf("Insira a coluna da antena: ");
    scanf_s("%d", &coluna);

    insereAntena(ed, freq, linha, coluna);

	listarAntenas(ed);
    
    destruirED(ed);

    return 0;
}
