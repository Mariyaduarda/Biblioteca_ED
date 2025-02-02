#include <stdio.h>
#include"../../model/include/model_livros.h"

void mostrarMenu() {
    printf("\n===== Sistema de Biblioteca =====\n");
    printf("1. Adicionar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Buscar Livro\n");
    printf("4. Remover Livro\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}

void exibirLivro(Livro livro) {
    printf("Código: %d\nTítulo: %s\nAutor: %s\nAno: %d\n", 
           livro.codigo_id, livro.titulo, livro.autor, livro.ano_publicacao);
}
