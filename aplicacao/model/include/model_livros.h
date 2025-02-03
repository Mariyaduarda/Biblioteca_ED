#ifndef  LIVROS_H
#define  LIVROS_H

/*implementando uma lista encadeada*/
typedef struct livro {
    /* dado em "*" ponteiro para um tipo de dados  & "int" amarzena valor direto na variavel*/
    int  codigo_id;   //id a partir da propria biblioteca que criamos
    char *titulo;
    char *autor;
    char *isbn;      //id unico de 13 caracteres
    int  ano_publicacao; 
    char *idioma;
    char *editora;
    char *genero;
    int  disponivel;
    struct livro *proximo; //ponteiro para  proximo livro
} Livro;

//biblioteca a ser definida
typedef struct{
    Livro *primeiro;   //ponteiro para o primiero nó(livro)
    int total_livros; //qnt de livros ja cadastrados 
}Biblioteca;

Biblioteca* cria_biblioteca(int livros_total_inicial);
void libera_biblioteca(Biblioteca *biblioteca); //libera a memoria alocada para a bibli
void cadastrar_livro(Biblioteca *biblioteca);   //funcionalidade de cadastro de livros
void listar_livro(Biblioteca *biblioteca);      //mostra todos os livros cadastrados
void atualizar_livro(Biblioteca *biblioteca);   //atualizar dados
void deletar_livro(Biblioteca *biblioteca);     //permite excluir im livro, a memoria ocupada se libera
//void busca_livro(); avore? ou hash
//void emprestimo_livro();
//void devolucao_livro();

#endif

