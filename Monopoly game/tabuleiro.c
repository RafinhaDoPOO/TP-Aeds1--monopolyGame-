#include "tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializarTabuleiro(Tabuleiro *tabuleiro) {
    tabuleiro->inicio = NULL;
    tabuleiro->fim = NULL;
}

Apontador* criarApontador(Localidade *localidade) {
    Apontador *novoApontador = (Apontador*)malloc(sizeof(Apontador));
    if (novoApontador == NULL) {
        perror("Falha ao alocar memória para o Apontador");
        exit(EXIT_FAILURE);
    }

    novoApontador->localidade = (Localidade*)malloc(sizeof(Localidade));
    if (novoApontador->localidade == NULL) {
        perror("Falha ao alocar memória para a Localidade");
        free(novoApontador);
        exit(EXIT_FAILURE);
    }

    memcpy(novoApontador->localidade, localidade, sizeof(Localidade));
    novoApontador->prox = NULL;

    return novoApontador;
}

void inserirLocalidade(Tabuleiro *tabuleiro, Localidade *localidade) {
    Apontador *novoApontador = criarApontador(localidade);

    if (tabuleiro->inicio == NULL) {
        // Lista vazia
        tabuleiro->inicio = novoApontador;
        tabuleiro->fim = novoApontador;
        novoApontador->prox = novoApontador; // Circularidade
    } else {
        // Inserir antes do início e manter a circularidade
        novoApontador->prox = tabuleiro->inicio;
        tabuleiro->fim->prox = novoApontador;
        tabuleiro->fim = novoApontador;
    }
}

void imprimirTabuleiro(Tabuleiro *tabuleiro) {
    if (tabuleiro->inicio == NULL) {
        printf("Tabuleiro vazio.\n");
        return;
    }
    
    Apontador *atual = tabuleiro->inicio;
    printf("Início -> ");

    do {
        printf("%s -> ", atual->localidade->endereco);
        atual = atual->prox;
    } while (atual != tabuleiro->inicio);

    printf("Início\n");
}