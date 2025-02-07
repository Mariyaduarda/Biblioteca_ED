
#include <stdio.h>
#include <stdlib.h>
#include <biblioteca.h>

void menuBiblioteca(ListaLivro* lista){
    
    int opcao;
    do {
        printf("\n=== BIBLIOTECA ===\n");
        printf("1. Inicializar Lista\n");
        printf("2. Adicionar Livro\n");
        printf("3. Imprimir Lista\n");
        printf("4. Ler Arquivo de Entrada\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inicializaLista(lista);
                printf("Lista inicializada.\n");
                break;
            case 2: {
                printf("=== Adicionar Livro ===");
                Livro* novoLivro = (Livro*)malloc(sizeof(Livro));
                printf("\nID: ");
                scanf("%d", &novoLivro->id);
                printf("Título: ");
                scanf(" %[^\n]", novoLivro->titulo);
                printf("Autor: ");
                scanf(" %[^\n]", novoLivro->autor);
                printf("Ano: ");
                scanf("%d", &novoLivro->anoPubl);
                printf("Gênero: ");
                scanf(" %[^\n]", novoLivro->genero);
                adicionaLivro(lista, novoLivro);
                break;
            }
            case 3:
                printf("=== Imprimir Lista ===");
                imprimirLista(lista);
                break;
            case 4: {
                printf("=== Ler Arquivo de Entrada ===");
                char nomeArquivo[100];
                printf("Nome do arquivo: ");
                scanf(" %[^\n]", nomeArquivo);
                lerArquivoEntrada(nomeArquivo, lista);
                break;
            }
            case 5:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while(opcao != 5);
}
