/*!
 *  @file Projeto_EDA.cpp
 *  @author Tiago Afonso
 *  @date 2025-03-20
 *  @project Listas Ligadas Antenas
 *
 *  Main file do projeto
 */
#include <iostream>
#include "Antena.h"
#include "ListaAntenas.h"
#include "LocalNefasto.h"
#include "Grafo.h"


const char* nomeArquivo = "Antenas.txt";

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1 - Listar antenas\n");
    printf("2 - Listar antenas formatadas\n");
    printf("3 - Remover uma antena\n");
    printf("4 - Inserir uma antena\n");
    printf("5 - Calcular locais nefastos\n");
    printf("6 - Listar locais nefastos\n");
    printf("7 - Listar locais nefastos formatados\n");
    printf("8 - Listar vertices do grafo\n");   
    printf("9 - Listar arestas do grafo\n");
    printf("10 - Procura por profundidade\n");
    printf("11 - Sair\n");
    printf("Escolha uma opcao: ");
}


int main() {
    int opcao;
    ED* ed = criarED();
    ED_LocaisNefastos locaisNefastos = { NULL };
    GR* grafo = criarGrafo(); 
    int max_linhas, max_colunas;

    // Carregar antenas do ficheiro antes de exibir o menu
    carregarAntenasDeFicheiro(ed, nomeArquivo, &max_linhas, &max_colunas);

    carregarGrafoDeFicheiro(grafo, ed);

    do {
        exibirMenu();
        scanf_s("%d", &opcao);

        switch (opcao) {
        case 1:
            listarAntenas(ed);
            break;
        case 2:
            listarAntenasFormatado(ed, max_linhas, max_colunas);
            break;
        case 3:
            listarAntenas(ed);
            removerAntenaManual(ed);
            break;
        case 4:
            listarAntenas(ed);
            inserirAntenaManual(ed);
            break;
        case 5:
            calcularLocaisNefastos(ed, &locaisNefastos, max_linhas, max_colunas);
            printf("Calculo feito com sucesso.\n");
            break;
        case 6:
            listarLocaisNefastos(&locaisNefastos);
            break;
        case 7:
            listarLocaisNefastosFormatado(&locaisNefastos, max_linhas, max_colunas);
            break;
        case 8: 
            listarVertices(grafo);
            break;
        case 9: 
            listarArestas(grafo);
            break;
        case 10:
            int linha, coluna;
            printf("Digite as coordenadas da antena inicial (linha coluna): ");
            scanf_s("%d %d", &linha, &coluna);
            buscaProfundidade(grafo, linha, coluna);
            break;
        case 11:
            printf("A Sair...\n");
            break;
        default:
            printf("Opção invalida! Tente novamente.\n");
        }
    } while (opcao != 11);
;
    destruirED(ed); 
    destruirGrafo(grafo);
    return 0;
}
