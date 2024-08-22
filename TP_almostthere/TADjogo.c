// TADjogo.c
#include "TADjogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    jogadorA->posicao = 0;
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

int rola_dados(){

    int Dado = rand() %6 + 1;
    int Dado2 = rand() %6 + 1;


    return Dado + Dado2;
}

void comprarPropriedade(Jogador* jogador, Localidade* localidade) {
    if (jogador->saldo >= localidade->custoCompra) {
        jogador->saldo -= localidade->custoCompra;
        localidade->proprietario = jogador->id; 
        for (int i = 0; i < MAX_PROPRIEDADES; i++) {
            if (jogador->propriedades[i] == NULL) {
                jogador->propriedades[i] = localidade;
                break;
            }
        }

        printf("Jogador %s comprou a propriedade %s por %d\n", jogador->nome, localidade->endereco, localidade->custoCompra);
    } else {
        printf("Jogador %s não tem saldo suficiente para comprar a propriedade %s\n", jogador->nome, localidade->endereco);
    }
}



void MovimentoJogadores(Jogo* jogo, int a) {
    Jogador *jogador = &jogo->jogadores[jogo->jogadorAtual];
    int prePosicao = jogador->posicao;

    jogador->posicao = (jogador->posicao + a) % jogo->tabuleiro.tamanho;
    Apontador *novaLoc = AvancaCasa(jogo->tabuleiro.inicio, jogador->posicao);

    if (jogador->posicao < prePosicao) {
        jogador->saldo += 200;
    }

    if (jogador->posicao == 0) {
        jogador->saldo += 500;
    }

    printf("%s se moveu de %d para %d - %s\n", jogador->nome, prePosicao, jogador->posicao,
     novaLoc->localidade->endereco);

    
    int idProprietario = novaLoc->localidade->proprietario;
    if (idProprietario == -1) {
        char escolha;
        printf("Você está na propriedade %s. Deseja comprar esta propriedade? (s/n): ",
         novaLoc->localidade->endereco);
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            comprarPropriedade(jogador, novaLoc->localidade);
        } else {
            printf("Você optou por não comprar a propriedade.\n");
        }
    } else if (idProprietario == jogador->id) {
        char escolha;
        printf("Você já possui a propriedade %s. Deseja construir algo? (s/n): ",
         novaLoc->localidade->endereco);
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            construir(novaLoc->localidade, jogador);
        } else {
            printf("Você optou por não construir.\n");
        }
    } else {
        Jogador *proprietario = &jogo->jogadores[idProprietario];
        int aluguel = 0;
    if (novaLoc->localidade->construcao == 1) {
        aluguel = novaLoc->localidade->valorAluguel * 5;
    }else if (novaLoc->localidade->construcao == 2) {
        aluguel = novaLoc->localidade->valorAluguel * 10;
    }
    if (aluguel > 0) {
        jogador->saldo -= aluguel;
        proprietario->saldo += aluguel;
}
        printf("A propriedade %s pertence a %s. Você pagou R$%d de aluguel.\n", 
        novaLoc->localidade->endereco, proprietario->nome, aluguel);
    }
    
    printf("\nSaldo atual de %s: R$%d\n", jogador->nome, jogador->saldo);
    for (int i = 0; i < jogo->numero_jogadores; i++) {
        printf("Saldo de %s: R$%d\n", jogo->jogadores[i].nome, jogo->jogadores[i].saldo);
    }
}

void PagamentoAluguel(Jogador* jogador, Localidade* localidade, Jogador* jogadores, int numero_jogadores) {
    if (jogador->saldo >= localidade->valorAluguel) {
        jogador->saldo -= localidade->valorAluguel;

        for (int i = 0; i < numero_jogadores; i++) {
            if (jogadores[i].id == localidade->proprietario) {
                jogadores[i].saldo += localidade->valorAluguel;
                printf("%s pagou aluguel de %d para %s\n", jogador->nome, 
                localidade->valorAluguel, jogadores[i].nome);
                return;
            }
        }

        printf("Erro: Proprietário da propriedade não encontrado.\n");
    } else {
        printf("%s não tem dinheiro suficiente para pagar o aluguel de %s\n", jogador->nome, 
        localidade->endereco);
        Falencia(jogador);
    }
}
void construir(Localidade* localidade, Jogador* jogador) {
    if (localidade->proprietario == jogador->id) {
        if (localidade->construcao == 0) {
            if (jogador->saldo >= localidade->custoCompra) {
                jogador->saldo -= localidade->custoCompra;
                localidade->construcao = 1;
                printf("%s construiu uma casa na propriedade %s\n", jogador->nome, localidade->endereco);
            } else {
                printf("%s não tem dinheiro suficiente para construir uma casa em %s\n", 
                jogador->nome, localidade->endereco);
            }
        } else if (localidade->construcao == 1) {
            if (jogador->saldo >= localidade->custoCompra*5) {
                jogador->saldo -= localidade->custoCompra*5;
                localidade->construcao = 2;
                printf("%s construiu um hotel na propriedade %s\n", jogador->nome, localidade->endereco);
            } else {
                printf("%s não tem dinheiro suficiente para construir um hotel em %s\n",
                 jogador->nome, localidade->endereco);
            }
        } else {
            printf("Não é possível construir mais na propriedade %s\n", localidade->endereco);
        }
    } else {
        printf("%s não é o proprietário da propriedade %s\n", jogador->nome, localidade->endereco);
    }
}


void Falencia(Jogador* jogador){
    if (jogador->saldo < 0) {
        jogador->saldo = 0;
        printf("Jogador %s faliu!\n", jogador->nome);
    }
}
