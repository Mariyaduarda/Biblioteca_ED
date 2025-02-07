#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

#define tamanhoVetor 1000

void inicializaLista(ListaLivro* lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
}

void adicionaLivro(ListaLivro* lista, Livro* livro) {
    livro->disponivel = 1;// inicializa o disponivel
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

void removeLivro(ListaLivro* lista, int id){
    //procura na lista, algum item com esse id, aí remove ele

    // variaveis de auxilio
    NodoLivro atual = lista->primeiro;
    NodoLivroanterior = NULL;

    //enquanto nao chegar no final, percorre procurando esse id
    while (atual != NULL) {
        //confere se o atual e o q tem q deletar
        if (atual->livro->id == id) {

            // se achei o item, mas e o primeiro
            if (anterior == NULL) {
                // atualiza o primeiro da lista
                lista->primeiro = atual->proximo;
                // se e' o ultimo, atualiza a lista
                if (atual->proximo == NULL) lista->ultimo = NULL;
            }

            // se achei mas nao e' o primeiro
            else {
                //atualiza o proximo do anterior
                anterior->proximo = atual->proximo;
                // se e' o ultimo, atualiza a lista
                if (atual == lista->ultimo) lista->ultimo = anterior;
            }

            // libera a memmoria do item
            free(atual->livro);  // Libera a memória do livro
            free(atual);         // Libera a memória do nó
            printf("\n - Livro com id %d foi removido com sucesso", id);
            return;

        }

        //avanca as variaveis
        anterior = atual;
        atual = atual->proximo;
    }

    // se nao achou o item, mostra isso
    printf("\n - Nao foi encontrado nenhum livro com o id %d. - ", id);
    return;

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

//livro dispponivel ou indisponivel verificacao + emprestimo + devolucao
void verificaDisponibildiade(ListaLivro* lista){
  NodoLivro* atual = lista->primeiro;
      while(atual != NULL){
        Livro* livro = atual->livro;
        if(livro->disponivel == 1){
          printf("Livro disponivel: id %d, titulo %s", livro->id, livro->titulo);
        } else {
            printf("Livro indisponivel: id %d, titulo %s", livro->id, livro->titulo);
        }
        atual = atual->proximo;
      }
}

void emprestarLivro(ListaLivro* lista, int id){
    NodoLivro* atual = lista->primeiro;
    while(atual != NULL){
        if( atual->livro->id = id && atual->livro->disponivel == 1){
            atual->livro->disponivel = 0;
            printf("Livro emprestado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Livro não foi encontrado ou esta indisponivel.\n");
}
void devolverLivro(ListaLivro* lista, int id){
    NodoLivro* atual = lista->primeiro;
        while(atual != NULL){
            if( atual->livro->id = id && atual->livro->disponivel == 0){
                atual->livro->disponivel = 1;
                printf("Livro devolvido com sucesso!\n");
                return;
            }
            atual = atual->proximo;
        }
        printf("Livro não foi encontrado ou esta indisponivel.\n");
}

/*começo da tabela hash*/
HashTable* criarHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (ht == NULL) {
        printf("Erro na alocação da tabela hash\n");
        exit(1);
    }
    
    for (int i = 0; i < 1000; i++) {
        ht->tabela[i] = NULL;
    }
    ht->quantidade = 0;
    return ht;
}

int hashFunction(int id) {
    return id % 1000;   
}

int inserirLivroHash(HashTable* ht, Livro* livro) {
    if (ht->quantidade >= 1000) {
        printf("Tabela hash está cheia!\n");
        return 0;
    }

    int index = hashFunction(livro->id);
    int tentativas = 0;
    
    //tratamento de colisão com sondagem linear
    while (tentativas < 1000) {
        if (ht->tabela[index] == NULL) {
            ht->tabela[index] = livro;
            ht->quantidade++;
            return 1;
        }
        index = (index + 1) % 1000;  //próxima posição - sondagem linear
        tentativas++;
    }
    
    printf("Não foi possível inserir o livro, tabela cheia\n");
    return 0;
}

Livro* buscarLivroHash(HashTable* ht, int id) {
    int index = hashFunction(id);
    int tentativas = 0;
    
    //busca com sondagem linear
    while (tentativas < 1000) {
        if (ht->tabela[index] == NULL) {
            return NULL;
        }
        if (ht->tabela[index]->id == id) {
            return ht->tabela[index];
        }
        index = (index + 1) % 1000;
        tentativas++;
    }
    return NULL;
}

//funções do arquivo
void salvarHashParaArquivo(HashTable* ht, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < 1000; i++) {
        if (ht->tabela[i] != NULL) {
            Livro* livro = ht->tabela[i];
            fprintf(arquivo, "%d,%s,%s,%d,%s,%d\n", 
                    livro->id, livro->titulo, livro->autor, 
                    livro->anoPubl, livro->genero, livro->disponivel);
        }
    }
    fclose(arquivo);
}

void carregarArquivoParaHash(HashTable* ht, const char* nomeArquivo) {
    FILE* arquivo = fopen(/*nomeArquivo*/, "r");
    if (!arquivo) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    char linha[500];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Livro* livro = (Livro*)malloc(sizeof(Livro));
        if (livro == NULL) {
            printf("Erro de alocação de memória para livro\n");
            continue;
        }
        
        sscanf(linha, "%d,%[^,],%[^,],%d,%[^,],%d", 
               &livro->id, livro->titulo, livro->autor, 
               &livro->anoPubl, livro->genero, &livro->disponivel);
        
        if (!inserirLivroHash(ht, livro)) {
            free(livro);  /*lbera memória se não conseguiu inserir*/
        }
    }
    fclose(arquivo);
}


