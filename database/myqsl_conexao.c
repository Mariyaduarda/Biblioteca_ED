#include "mysql_conexao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MYSQL* conectarBanco() {
    MYSQL *conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "Erro ao inicializar o MySQL: %s\n", mysql_error(conn));
        exit(1);
    }

    // Configuração do timeout
    unsigned int timeout = 5;
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);

    if (mysql_real_connect(conn, 
                          DB_HOST, 
                          DB_USER, 
                          DB_PASS, 
                          DB_NAME, 
                          DB_PORT, 
                          NULL, 
                          0) == NULL) {
        fprintf(stderr, "Erro ao conectar ao banco: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("Conexão bem-sucedida ao banco de dados!\n");
    return conn;
}

void desconectarBanco(MYSQL *conn) {
    if (conn != NULL) {
        mysql_close(conn);
    }
}

void criarTabelaLivros(MYSQL *conn) {
    const char *query = "CREATE TABLE IF NOT EXISTS livros ("
                       "id INT PRIMARY KEY AUTO_INCREMENT,"
                       "titulo VARCHAR(100) NOT NULL,"
                       "autor VARCHAR(100) NOT NULL,"
                       "isbn VARCHAR(13) UNIQUE NOT NULL,"
                       "ano_publicacao INT NOT NULL,"
                       "idioma VARCHAR(50) NOT NULL,"
                       "editora VARCHAR(100) NOT NULL,"
                       "genero VARCHAR(50) NOT NULL,"
                       "disponivel BOOLEAN NOT NULL DEFAULT TRUE"
                       ")";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao criar tabela: %s\n", mysql_error(conn));
        return;
    }
    printf("Tabela 'livros' criada/verificada com sucesso!\n");
}

int salvarLivroBD(MYSQL *conn, Livro *livro) {
    char query[1024];
    char titulo_esc[201], autor_esc[201], isbn_esc[27], 
         idioma_esc[101], editora_esc[201], genero_esc[101];

    // Escapa as strings para prevenir SQL injection
    mysql_real_escape_string(conn, titulo_esc, livro->titulo, strlen(livro->titulo));
    mysql_real_escape_string(conn, autor_esc, livro->autor, strlen(livro->autor));
    mysql_real_escape_string(conn, isbn_esc, livro->isbn, strlen(livro->isbn));
    mysql_real_escape_string(conn, idioma_esc, livro->idioma, strlen(livro->idioma));
    mysql_real_escape_string(conn, editora_esc, livro->editora, strlen(livro->editora));
    mysql_real_escape_string(conn, genero_esc, livro->genero, strlen(livro->genero));

    snprintf(query, sizeof(query),
             "INSERT INTO livros (titulo, autor, isbn, ano_publicacao, idioma, editora, genero, disponivel) "
             "VALUES ('%s', '%s', '%s', %d, '%s', '%s', '%s', %d)",
             titulo_esc, autor_esc, isbn_esc, livro->ano_publicacao,
             idioma_esc, editora_esc, genero_esc, livro->disponivel);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao inserir livro: %s\n", mysql_error(conn));
        return 0;
    }
    
    return (int)mysql_insert_id(conn);
}