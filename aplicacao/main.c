#include <stdio.h>  // entrada e saída
#include <stdlib.h> // alocação de memória
#include"../aplicacao/model/include/model_livros.h"
#include "db_config.h"
// Programa principal
int main() {
    //incializa a biblioteca
    Biblioteca* bibli = cria_biblioteca();

    //onectar ao banco
    MYSQL *conn = conectarBanco();

   

    return 0;
}