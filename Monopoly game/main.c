#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"
#include "localidade.h"
#include "jogador.h"
#include "TADjogo.h"

 int main() {
    // Inicialização do tabuleiro
    Tabuleiro tabuleiro;
    inicializarTabuleiro(&tabuleiro);
    PreencherJogo(&tabuleiro, "localidades02.txt");
    Jogador jogadores[20];  // Supondo que MAX_JOGADORES seja definido em jogo.h
    int numJogadores = 0;

    // Adiciona jogadores a partir do arquivo "jogadores02.txt"
    adicionar_jogador(jogadores, "jogadores02.txt", &numJogadores);

    // Imprime os jogadores adicionados
    printf("Jogadores adicionados:\n");
    imprimirTabuleiro(&tabuleiro);
    imprimeJogador(jogadores,numJogadores);
    return 0;
}