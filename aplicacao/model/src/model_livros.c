#include"../../model/include/model_livros.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//limpa buffer usando variavel temporaria
void limpa_buffer(){
    int caracter;
    while((caracter = getchar()) != '\n' && caracter != EOF);
}

//alocar string dinamicamente
char* ler_string(){
    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strspn(buffer, "\n")] = '\0';
    char* str = (char*)malloc(strlen(buffer) + 1); //+1 é sobre o '\0'
    strcpy(str, buffer);
    return str;
}

Biblioteca* cria_biblioteca(){
    Biblioteca* biblioteca = (Biblioteca*)malloc(sizeof(Biblioteca));
    biblioteca->primeiro = NULL;
    biblioteca->total_livros = 0; // Inicializa como 0
    return biblioteca;
}

void libera_biblioteca(Biblioteca *biblioteca){
    Livro *atual = biblioteca->primeiro;

    while(atual != NULL){
        Livro *proximo = atual->proximo;

        //libera as strings
        free(atual->titulo);
        free(atual->autor);
        free(atual->isbn);
        free(atual->idioma);
        free(atual->editora);
        free(atual->genero);

        free(atual);
        atual = proximo;
    }
    free(biblioteca);
}
//cadastramento dos livros
void cadastrar_livro(Biblioteca *biblioteca){
    
    Livro* novo = (Livro*)malloc(sizeof(Livro));
    novo->proximo = NULL;
    novo->codigo_id = biblioteca->total_livros + 1;
    
   printf("Digite o titulo do livro: ");
    novo->titulo = ler_string();

    printf("Digite o autor do livro: ");
    novo->autor = ler_string();

    printf("Digite o ISBN do livro: ");
    novo->isbn = ler_string();

    printf("Digite o ano de publicação do livro: ");
    scanf("%d", &novo->ano_publicacao);
    limpa_buffer();

    printf("Digite o idioma do livro: ");
    novo->idioma = ler_string();

    printf("Digite a editora do livro: ");
    novo->editora = ler_string();

    printf("Digite o genero do livro: ");
    novo->genero = ler_string();

    printf("Está disponivel (1 para Sim, 0 para Não): ");
    scanf("%d", &novo->disponivel);
    limpa_buffer();

    // inserção do novo livro no inicio da lista
    novo->proximo = biblioteca->primeiro;
    biblioteca->primeiro = novo;
    biblioteca->total_livros++;

    printf("Êxito ao ser cadastrado!\n");
}
//ver os livros
void listar_livro(Biblioteca *biblioteca){
    //caso a qnt de livros seja nula, saia do programa
    if(biblioteca->total_livros == 0)
    {
        printf("Nenhum livro foi cadastrado até então.");
        EXIT_FAILURE;
    }
    //uso da tabela ascii com bordas e organizadores
    printf("\n\t----- Lista de Livros -----\n");
    printf("\n| %-5s | %-30s | %-30s | %-13s | %-4s | %-15s | %-20s | %-10s | %-10s |\n",
           "ID", "Titulo", "Autor", "ISBN", "Ano", "Idioma", "Editora", "Genero", "Disponível");

    printf("|-------|--------------------------------|--------------------------------|---------------|------|------------------|----------------------|------------|------------|\n");
    Livro *atual = biblioteca->primeiro;
    while (atual != NULL)
    {
        //uso da tabela ascii p ainhamento ao imprimir. 5/30/13 e etc sao caracters p formato
          printf("| %-5d | %-30s | %-30s | %-13s | %-4d | %-15s | %-20s | %-10s | %-10s |\n", 
               atual->codigo_id, atual->titulo, atual->autor, atual->isbn,
               atual->ano_publicacao, atual->idioma, atual->editora,
               atual->genero, atual->disponivel ? "SIM" : "NAO");
        atual = atual->proximo;
    }
    printf("\n");//add linha no final da execucao p aparencia
    
}
//atualiza a info dos livros
void atualizar_livro(Biblioteca *biblioteca){
    int ID;
    printf("Digite o ID do livro para atualiza-lo: \n");
    scanf("%d", &ID);

    limpa_buffer();

    Livro *atual = biblioteca->primeiro;
    //busca binaria
    while (atual != NULL && atual->codigo_id != ID)
    {
        atual = atual->proximo;
    }
    //se o ponteiro atual for = a null sai do prgrama
    if(atual == NULL){
        printf("Livro não encontrado.");
        return; //sai do programa
    }
    
    //libera as string antigas
    free(atual->titulo);
    free(atual->autor);
    free(atual->isbn);
    free(atual->idioma);
    free(atual->editora);
    free(atual->genero);

    //atualiza o as novas info do livro
    printf("Digite o novo título do livro: ");
    atual->titulo = ler_string();

    printf("Digite o novo autor do livro: ");
    atual->autor = ler_string();

    printf("Digite o novo ISBN do livro: ");
    atual->isbn = ler_string();

    printf("Digite o novo ano de publicação do livro: ");
    scanf("%d", &atual->ano_publicacao);
    limpa_buffer();

    printf("Digite o novo  idioma do livro: ");
    atual->idioma = ler_string();

    printf("Digite a nova editora do livro: ");
    atual->editora = ler_string();

    printf("Digite o novo gênero do livro: ");
    atual->genero = ler_string();

    printf("Está disponível (1 para SIM, 0 para NAO): ");
    scanf("%d", &atual->disponivel);
    limpa_buffer();

    printf("Êxito ao atualizar livro.\n");

}
void deletar_livro(Biblioteca *biblioteca){
    //verifica se ha livros para excluir
    if(biblioteca->primeiro == NULL){
        printf("Biblioteca vazia.");
        return;
    }
    int ID;
    printf("Digite o ID do livro para exclusão:\n");
    scanf("%d", &ID);
    limpa_buffer();

    //funcao hash

    Livro *atual = biblioteca->primeiro;
    Livro *anterior = NULL;

    //procura o lvro
    while (atual != NULL && atual->codigo_id != ID)
    {
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL){
        printf("Livro não encontrado.\n");
        return;
    }
    if(anterior == NULL){ //removendo nó da lista
        //removendo o primeito elemento
        biblioteca->primeiro = atual->proximo;
    }
    else{
        anterior->proximo = atual->proximo;
    }
    //libera a memoria do livro
    free(atual->titulo);
    free(atual->autor);
    free(atual->isbn);
    free(atual->idioma);
    free(atual->editora);
    free(atual->genero);
    free(atual);

    biblioteca->total_livros--;
    printf("Êxito ao deletar livros.\n");
}

/*int main() {
    Biblioteca *biblioteca = cria_biblioteca();  // Cria a biblioteca

    int opcao;
    do {
        // Exibe o menu de opções
        printf("\n----- Sistema de Biblioteca -----\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar livros\n");
        printf("3. Atualizar livro\n");
        printf("4. Deletar livro\n");
        printf("5. Sair\n");
        printf("Escolha uma opaoo: ");
        scanf("%d", &opcao);
        limpa_buffer();

        switch (opcao) {
            case 1:
                cadastrar_livro(biblioteca);  // Função para cadastrar livro
                break;
            case 2:
                listar_livro(biblioteca);  // Função para listar livros
                break;
            case 3:
                atualizar_livro(biblioteca);  // Função para atualizar livro
                break;
            case 4:
                deletar_livro(biblioteca);  // Função para deletar livro
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    libera_biblioteca(biblioteca);  // Libera a memória alocada ao final
    return 0;
}
*/