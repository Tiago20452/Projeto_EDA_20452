#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaAntenas.h"
#include "Dados.h"

// Cria uma nova lista ligada vazia
ED* criarED() {
    ED* ed = (ED*)malloc(sizeof(ED));
    if (ed == NULL) {
        perror("Erro ao alocar memória para ED");
        exit(EXIT_FAILURE);
    }
    ed->cabeca = NULL;
    return ed;
}

// Liberra toda a memória da lista ligada
void destruirED(ED* ed) {
    Antena* atual = ed->cabeca;
    while (atual != NULL) {
        Antena* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(ed);
}