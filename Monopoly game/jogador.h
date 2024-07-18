
#ifndef JOGADOR_H
#define JOGADOR_H

#include "localidade.h"

#define MAX_PROPRIEDADES 100

typedef struct {
    char nome[100];
    int id;
    int saldo;
    Localidade *propriedades[MAX_PROPRIEDADES];
} Jogador;


#endif