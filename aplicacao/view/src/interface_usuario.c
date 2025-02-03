#include <stdio.h>
#include"../../model/include/model_livros.h"

//view mostra menu de entrada
void mostrarMenu() {
    printf("\n------- Sistema de Biblioteca -------\n");
    printf("1. Cadastrar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Buscar Livro\n");
    printf("4. Remover Livro\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}

//view mostrar livros
void listar_livro(Livro livro) {
    printf("Código: %d\nTítulo: %s\nAutor: %s\nISNB:%s\nAno: %d\nIdioma: %s\nEditora: %s\nGênero: %s\nDisponível: %s\n", 
           livro.codigo_id, livro.titulo, livro.autor, livro.isbn, livro.ano_publicacao, livro.idioma, livro.editora, 
           livro.genero, livro.disponivel);
}
