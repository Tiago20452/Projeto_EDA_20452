#ifndef DADOS_H
#define DADOS_H

/**
 * @brief Estrutura que representa uma antena na lista ligada
 */
typedef struct Antena {
    char frequencia;        ///< Frequência da antena (ex: 'A', 'O')
    int linha;              ///< Linha na matriz (coordenada x)
    int coluna;             ///< Coluna na matriz (coordenada y)
    struct Antena* prox;    ///< Ponteiro para a próxima antena na lista
} Antena;

/**
 * @brief Estrutura principal ED (lista ligada de antenas)
 */
typedef struct {
    Antena* cabeca;         ///< Ponteiro para a primeira antena da lista
} ED;

#endif // DADOS_H