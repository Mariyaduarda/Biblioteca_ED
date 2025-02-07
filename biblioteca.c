#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

void inicializaLista(ListaLivro* lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
}

void adicionaLivro(ListaLivro* lista, Livro* livro) {
    NodoLivro* novoNodo = (NodoLivro*)malloc(sizeof(NodoLivro));
    novoNodo->livro = livro;
    novoNodo->proximo = NULL;

    if (lista->ultimo != NULL) {
        lista->ultimo->proximo = novoNodo;
    } else {
        lista->primeiro = novoNodo;
    }
    lista->ultimo = novoNodo;
}

void imprimirLista(ListaLivro* lista) {
    NodoLivro* atual = lista->primeiro;
    while (atual != NULL) {
        Livro* livro = atual->livro;
        printf("ID: %d, Titulo: %s, Autor: %s, Ano: %d, Genero: %s\n",
               livro->id, livro->titulo, livro->autor, livro->anoPubl, livro->genero);
        atual = atual->proximo;
    }
}

void lerArquivoEntrada(char *StrEntrada,ListaLivro* lista) {

    char Controle;
    char auxFinalLinha;
    FILE *arquivo = fopen(StrEntrada, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    do {
        fscanf(arquivo, " %c", &Controle);
        switch (Controle) {
            case 'I': {
                Livro* livro = (Livro*)malloc(sizeof(Livro));
                fscanf(arquivo, "%d %[^,],%[^,],%d,%s", &livro->id, livro->titulo, livro->autor, &livro->anoPubl, livro->genero);
                adicionaLivro(lista, livro);
                break;
            }
            case '#':
                do {
                    fscanf(arquivo, "%c", &auxFinalLinha);
                } while (auxFinalLinha != '\n');
                break;
            case 'F':
                fclose(arquivo);
                return;
        }
    } while (1);
}
