// hash_biblioteca.h
#ifndef HASH_BIBLIOTECA_H
#define HASH_BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*implementando uma lista encadeada*/
typedef struct livro {
   int  codigo_id;
   char *titulo;
   char *autor; 
   char *isbn; //lembrar que sao 13 posições + string
   int  ano_publicacao;
   char *idioma;
   char *editora;
   char *genero;
   int  disponivel;
   struct livro *proximo; //ponteiro para  proximo livro
} Livro;

// encoporando a hash
typedef struct {
    Livro **tabela;
    int     tamanho;
} HashTable;

/*metodos para implementar hash*/
HashTable* criar_hash_table();
int hash_fun(HashTable *hasht, int id);
void inserir_livro(HashTable *hasht, Livro *livro);
Livro* buscar_por_id(HashTable *hasht, int id);
Livro* buscar_por_isbn(HashTable *hasht, char *isbn);
void remover_livro(HashTable *ht, int id);
void destruir_hash_table(HashTable *hasht);

#endif