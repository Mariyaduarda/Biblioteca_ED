#include <stdio.h>  // entrada e saída
#include <stdlib.h>        // alocação de memória
#include <mysql/mysql.h>  // biblioteca do mysql

// Função para conectar ao banco de dados
MYSQL* conectarBanco() {
    MYSQL *conn = mysql_init(NULL);  // inicializa o objeto MYSQL

    if (conn == NULL) {
        fprintf(stderr, "Erro ao inicializar o MySQL: %s\n", mysql_error(conn));
        exit(1);
    }

    // configuração do tempo limite (opcional)
    unsigned int timeout = 5;  // tempo limite de 5 segundos
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);

    // conexão ao banco
    if (mysql_real_connect(
            conn,               // variável de conexão do BD
            "localhost",        // geralmente localhost
            "root",             // usuário padrão
            "1948",             // senha do root
            "meus_livros",      // nome do banco de dados
            3306,               // porta padrão do MySQL
            NULL,               // caminho para o socket (NULL para padrão)
            0) == NULL) {       // flags (geralmente 0)
        fprintf(stderr, "Erro ao conectar ao banco: %s\n", mysql_error(conn));
        mysql_close(conn);  // sempre feche o recurso antes de sair
        exit(1);
    }

    printf("Conexão bem-sucedida ao banco de dados!\n");
    return conn;  // retorna o objeto de conexão
}

// Programa principal
int main() {
    // Conectar ao banco
    MYSQL *conn = conectarBanco();

    // Realize operações no banco de dados aqui (opcio
