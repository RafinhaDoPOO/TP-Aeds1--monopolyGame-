#include "localidade.h"
#include <string.h>

void inicializarLocalidade(Localidade *localidade, const char *endereco, const char *cor, int custoCompra, int valorAluguel) {
    strcpy(localidade->endereco, endereco);
    strcpy(localidade->cor, cor);
    localidade->custoCompra = custoCompra;
    localidade->valorAluguel = valorAluguel;
    localidade->construcao = 0;
    localidade->proprietario = -1;
}