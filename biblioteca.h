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
}Livro;

typedef struct NodoLivro {
  Livro* livro;
  struct NodoLivro* proximo;
} NodoLivro;

typedef struct {
  NodoLivro* primeiro;
  NodoLivro* ultimo;
} ListaLivro;

void lerArquivoEntrada(char *StrEntrada,ListaLivro* lista);
void inicializaLista(ListaLivro* lista);
void imprimirLista(ListaLivro* lista);
#endif

