#ifndef  LIVROS_H
#define  LIVROS_H

typedef struct livro {
    int id;             //id a partir da propria biblioteca que criamos
    char titulo[230];
    char autor[100];
    char isbn[13];      //id unico de 13 caracteres
    int ano_publicacao; 
    char idioma[30];
    char editora[50];
    char genero[50];
    int disponivel;
} Livro;

void cadastrar_livro();
void listar_livro();
void atualizar_livro();
void deletar_livro();

void busca_livro();
void emprestimo_livro();
void devolucao_livro();
#endif

