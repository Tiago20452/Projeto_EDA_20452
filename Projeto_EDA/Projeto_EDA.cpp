// Projeto_EDA.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Antena.h"
#include "ListaAntenas.h"
#include "LocalNefasto.h"


int main() {

    const char* nomeArquivo = "Antenas.txt";
    ED* ed = criarED();
	ED_LocaisNefastos locaisNefastos = { NULL };
	int max_linhas, max_colunas;

	// Carregar antenas de um ficheiro
    carregarAntenasDeFicheiro(ed, nomeArquivo, &max_linhas, &max_colunas); 

	// Listar antenas
    listarAntenas(ed);
	listarAntenasFormatado(ed, max_linhas, max_colunas);

    //Remover uma antena existente
	removerAntena(ed,'O', 4, 4);
    listarAntenas(ed);

	//Inserir uma antena manualmente
	inserirAntenaManual(ed);    
	listarAntenas(ed);
 
	// Calcular locais nefastos
	calcularLocaisNefastos(ed, &locaisNefastos, max_linhas, max_colunas);

	// Listar resultados
	listarLocaisNefastos(&locaisNefastos);

	// Listar resultados formatados como o ficheiro de entrada
	listarLocaisNefastosFormatado(&locaisNefastos, max_linhas, max_colunas);

	destruirED(ed);

    return 0;
}
