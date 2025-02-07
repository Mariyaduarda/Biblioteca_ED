//
// Created by yasmim on 04/02/25.
//

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct Livro{
  int id;
  int anoPubl;
  char titulo[200];
  char autor[200];
  char genero[200];
  int disponivel; //1 para disponivel e 0 para indis.
}Livro;

typedef struct NodoLivro {
  Livro* livro;
  struct NodoLivro* proximo;
} NodoLivro;

typedef struct {
  NodoLivro* primeiro;
  NodoLivro* ultimo;
} ListaLivro;

//hashTable estrutura
typedef struct {
    Livro* tabela[1000]; 
    int quantidade;        //contador de elementos na hash
} HashTable;


void inicializaLista(ListaLivro* lista);
void adicionaLivro(ListaLivro* lista, Livro* livro);
void removeLivro(ListaLivro* lista, int id);
void imprimirLista(ListaLivro* lista);
void lerArquivoEntrada(char *StrEntrada,ListaLivro* lista);

//menu da biblioteca da yasmim branch
void menuBiblioteca(ListaLivro* lista);

//disponibilidade, emrpestar e devolver
void verificaDisponibildiade(ListaLivro* lista);
void emprestarLivro(ListaLivro* lista, int id);
void devolverLivro(ListaLivro* lista, int id);

//tabela hash id
HashTable* criar_hash_table(int tamanho);
void carregar_arquivo_hash(HashTable *hasht);
void inserir_livro(HashTable *hasht, Livro *livro);
Livro* buscar_por_id(HashTable *hasht, int id);
void remover_livro(HashTable *hasht, int id);
void destruir_hash_table(HashTable *hasht);

#endif

