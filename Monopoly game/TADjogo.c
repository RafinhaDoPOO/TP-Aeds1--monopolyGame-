// TADjogo.c
#include "TADjogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PreencherJogo(Tabuleiro *tabuleiro, const char arq[]) {
    FILE *file = fopen(arq, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        // Processa cada linha do arquivo
        char endereco[200], cor[20];
        int custoCompra, valorAluguel;

        // Use o formato correto para a leitura dos dados
        if (sscanf(linha, "%199[^;];%19[^;];%d;%d", endereco, cor, &custoCompra, &valorAluguel) != 4) {
            fprintf(stderr, "Erro ao ler os dados da linha: %s", linha);
            continue; // Pula para a próxima linha em caso de erro
        }

        // Cria uma nova localidade e insere no tabuleiro
        Localidade localidade;
        inicializarLocalidade(&localidade, endereco, cor, custoCompra, valorAluguel);
        inserirLocalidade(tabuleiro, &localidade);
    }

    fclose(file);
}

void adicionar_jogador(Jogador *jogadores, const char arq[], int *num_jogadores) {
    FILE *file = fopen(arq, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        char nome[256];
        int dinheiro, idJogador;

        // Use o formato correto para a leitura dos dados
        if (sscanf(linha, "%255[^;];%d;%d", nome, &dinheiro, &idJogador) != 3) {
            fprintf(stderr, "Erro ao ler os dados da linha: %s", linha);
            continue; // Pula para a próxima linha em caso de erro
        }

        // Inicializa o jogador
        inicializarJogador(&jogadores[*num_jogadores], nome, dinheiro, idJogador);
        (*num_jogadores)++;
    }

    fclose(file);
}

void inicializarJogador(Jogador *jogadorA, char nomeN[], int saldo, int id2) {
    strcpy(jogadorA->nome, nomeN);
    jogadorA->id = id2;
    jogadorA->saldo = saldo;
    for (int i = 0; i < MAX_PROPRIEDADES; i++) {
        jogadorA->propriedades[i] = NULL;
    }
}

void imprimeJogador(const Jogador *jogadores, int num_jogadores) {
    for (int i = 0; i < num_jogadores; i++) {
        printf("Jogador %d:\n", i + 1);
        printf("Nome: %s\n", jogadores[i].nome);
        printf("Dinheiro: %d\n", jogadores[i].saldo); // Ajustado para %d para inteiros
        printf("ID: %d\n", jogadores[i].id);
        printf("\n");
    }
}

void TFalencia(Jogador *jogadorA) {
    if (jogadorA->saldo < 0) {
        jogadorA->saldo = 0;
        printf("Jogador %s faliu!\n", jogadorA->nome);
    }
}
