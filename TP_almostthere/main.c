#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TADjogo.h"

void esperarEntrada() {
    printf("Pressione Enter para continuar...");
    getchar(); // Aguarda a entrada do usuário
}

int main() {
    srand(time(NULL)); // Inicializa a semente para a rolagem de dados

    // Inicializa o tabuleiro
    Tabuleiro tabuleiro;
    inicializarTabuleiro(&tabuleiro);

    // Preenche o tabuleiro com localidades a partir de um arquivo
    PreencherJogo(&tabuleiro, "localidades02.txt");
    imprimirTabuleiro(&tabuleiro);

    
    Jogador jogadores[6]; 
    int num_jogadores = 0;
    adicionar_jogador(jogadores, "jogadores02.txt", &num_jogadores);
    imprimeJogador(jogadores, num_jogadores);

    // Configura o jogo
    Jogo jogo;
    jogo.tabuleiro = tabuleiro;
    jogo.jogadores = jogadores;
    jogo.numero_jogadores = num_jogadores;
    jogo.jogadorAtual = 0; 

    char escolha;
    for (int i = 0; i < 100; i++) { 
        printf("\nJogador %d (%s), sua vez.\n", jogo.jogadorAtual + 1, jogo.jogadores[jogo.jogadorAtual].nome);

        // Escolha para rolar os dados
        printf("Deseja rolar os dados? (s/n): ");
        scanf(" %c", &escolha); 
        if (escolha == 's' || escolha == 'S') {
            int dado = rola_dados();
            printf("\nJogador %d (%s) rolou: %d\n", jogo.jogadorAtual + 1, jogo.jogadores[jogo.jogadorAtual].nome, dado);
            MovimentoJogadores(&jogo, dado);
        } else {
            
            printf("Você optou por não rolar os dados.\n");
        }
        jogo.jogadorAtual = (jogo.jogadorAtual + 1) % jogo.numero_jogadores;
        esperarEntrada();
    }

    return 0;
}
