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
    printf("8 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;
    ED* ed = criarED();
    ED_LocaisNefastos locaisNefastos = { NULL };
    int max_linhas, max_colunas;

    // Carregar antenas do ficheiro antes de exibir o menu
    carregarAntenasDeFicheiro(ed, nomeArquivo, &max_linhas, &max_colunas);

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
            printf("A Sair...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 8);

    destruirED(ed);
    return 0;
}
