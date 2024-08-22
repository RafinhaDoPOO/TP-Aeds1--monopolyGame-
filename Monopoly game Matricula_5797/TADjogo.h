#ifndef TADJOGO_h
#define TADJOGO_h

#include "tabuleiro.h"
#include "jogador.h"
#include "localidade.h"

typedef struct {
    Tabuleiro tabuleiro;
    Jogador *jogadores;
    int numero_jogadores;
    int jogadorAtual;
} Jogo;

void PreencherJogo(Tabuleiro *tabuleiro, const char arq[]);
void adicionar_jogador(Jogador *jogadores, const char arq[], int *num_jogadores);
int rola_dados();
void MovimentoJogadores(Jogo* jogo, int a);
void comprarPropriedade(Jogador* jogador, Localidade* localidade);
void PagamentoAluguel(Jogador* jogador, Localidade* localidade, Jogador* jogadores, int numero_jogadores);
void construir(Localidade* Localidade, Jogador* jogador);
void Falencia(Jogador* jogador);
void proxRodada();
void PrintJogo();
void inicializarJogador(Jogador *jogadorA, char nomeN[], int saldo, int id); 
void imprimeJogador(const Jogador *jogadores, int num_jogadores);


#endif 