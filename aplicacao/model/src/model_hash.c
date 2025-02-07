#include "../../model/include/model_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//cria tabela e verfica as cobdicoes propicias para tal
HashTable* criar_hash_table(int tamanho){
    HashTable *hasht = malloc(sizeof(HashTable));       /*aloco memoria para a estrutura hash*/
    if(hasht == NULL){
        //verificacao para a alocacao
        perror("Erro ao alocar a tabela hash.");
        exit(EXIT_FAILURE);
    }
    hasht->tabela = malloc(sizeof(Livro*) * tamanho);   /*definindo array para pont. livros*/
    if(hasht->tabela == NULL){
        perror("Erro ao alocar tabela de livros.");
        free(hasht);
        exit(EXIT_FAILURE);
    }
    hasht->tamanho = tamanho; /*atribuindo tamanho*/

    /*inicializa as posições da tabela*/
    for(int i = 0; i < tamanho; i++){
        hasht->tabela[i] = NULL;
    }
    return hasht;
//yasmim os nome de arquivo sao ilustrativos
//carrega o arquivo da biblioteca txt
FILE *arquivo = fopen(ARQUIVO, "rb");
if (arquivo != NULL){
    Livro livro_temporario;
    while (fread(&livro_temporario, sizeof(Livro), 1, arquivo) == 1){
        //alocar memoria do livro novo
        Livro *add_livro = malloc(sizeof(Livro));
        if(add_livro == NULL){
            perror("Erro ao alocar memoria do livro.");
            continue;
        }
    
        //copia dados do lviro
        *add_livro = livro_temporario;
        add_livro->proximo = NULL;

        //inserir na tabela hasht
        int indice = has_fun(hasht, add_livro->codigo_id);
        add_livro->proximo = hasht->tabela[indice];
        hast->tabela[indice] = add_livro;
    }
    fclose(arq);
}
return hasht;
}

/*aqui jaz a fun da hash, distribui ids dos livros pela tabela. % retorna resto da divisao
do id pelo tam dessa tabela hash
obs: resto sempre sera entre 0 e tam-1 */
int hash_fun(HashTable *hasht, int id){ //n sei se é acima ou abaixo do criar tab.hash
    return id % hasht->tamanho;
}

void inserir_livro(HashTable *hasht, Livro *livro){
    int indice = hash_fun(hasht, livro->codigo_id);
    livro->proximo = hasht->tabela[indice];
    hasht->tabela[indice] = livro;

    salvar_hash_arquivo(hasht);
}
Livro* buscar_por_id(HashTable *hasht, int id){
    int indice = hash_fun(hasht, id);
    Livro *atual = hasht->tabela[indice];

    while(atual != NULL){
        if(atual->codigo_id == id){
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}
//busca pelo isbn
Livro* buscar_por_isbn(HashTable *hasht, char *isbn){
    for(int i = 0; i < hasht->tamanho, i++){
        Livro *atual = hasht->tabela[i];
        while(atual != NULL){
            if(strcmp(atual->isbn, isbn) == 0){
                return atual;
            }
            atual = atual->proximo;
        }
    }
    return NULL;
}
void remover_livro(HashTable *hasht, int id){
    int indice = hash_fun(hasht, id);
    Livro *atual = hasht->tabela[indice];
    Livro *anterior = NULL;

    while(atual != NULL){
        if(atual->codigo_id == id){
            if(anterior == NULL){
                haasht->tabela[indice] = atual->proximo;
            }else{
                anterior-proximo = atual->proximo;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    FILE *arquivo_semLivroExcluido = fopen(arquivoAcervo, "rb"); //nomes so para vc entender 
    FILE *arquivo_temporario = fopen("arquivoAcervo_temporario", "wb"); //nome ilustrativo ok

    if(arquivo_semLivroExcluido == NULL || arquivo_temporario == NULL){
        perror("Erro ao abrir arquivos para exclusão");
        return;
    }
    Livro livro_temporario;

    while(fread(&livro_temporario, sizeof(Livro, 1, arquivo_semLivroExcluido) == 1)){
        if(livro_temp.codigo_id != id){
            fwrite(&livro_temporario, sizeof(Livro), 1, arquivo_semLivroExlcuido);
        }
    }
    fclose(arquivo_semLivroExluido);
    fclose(arquivo_temporario);

    remove(ArquivoAcervo);
    rename("arquivoAcervo_temporario", arquivoAcervo);
}
//destuindo a hasht
void destruir_hash_table(HashTable *hasht){
    for(int i = 0; i < hasht->tamanho; i++){
        Livro *atual = hasht->tabela[i];
        while(atual != NULL){
            Livro *swap = atual;
            atual = atual->proximo;
            free(swap);
        }
    }
    free(hasht->tabela);
    free(hasht);
}