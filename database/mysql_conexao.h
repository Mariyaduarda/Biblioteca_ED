#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "1948"
#define DB_NAME "meus_livros"
#define DB_PORT 3306

MYSQL* conectarBanco();
void desconectarBanco(MYSQL *conn);
void criarTabelaLivros(MYSQL *conn);
int salvarLivroBD(MYSQL *conn, Livro *livro);
Livro* buscarLivroBD(MYSQL *conn, int id);
void atualizarLivroBD(MYSQL *conn, Livro *livro);
void deletarLivroBD(MYSQL *conn, int id);

#endif