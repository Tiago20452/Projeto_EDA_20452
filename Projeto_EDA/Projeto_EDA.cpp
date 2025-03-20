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

    carregarAntenasDeFicheiro(ed, nomeArquivo); 
    listarAntenas(ed);

 //   //Remover uma antena existente
	//removerAntena(ed,'O', 5, 5);

 //   listarAntenas(ed);

	////Inserir uma antena manualmente

	//inserirAntenaManual(ed);    

	//listarAntenas(ed);
 //   
 //   destruirED(ed);

	// Calcular locais nefastos
	calcularLocaisNefastos(ed, &locaisNefastos);

	// Listar resultados
	listarLocaisNefastos(&locaisNefastos);


    return 0;
}
