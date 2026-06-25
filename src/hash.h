#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdbool.h>

/* Tipo usado para esconder os campos internos da tabela */
typedef struct HashTable HashTable;

/* Dados usados na analise de colisoes */
typedef struct {
    size_t capacidade;
    size_t quantidade;
    size_t buckets_usados;
    size_t buckets_com_colisao;
    size_t total_colisoes;
    size_t maior_cadeia;
    double fator_carga;
} HashStats;

/* Cria a tabela hash */
HashTable *hash_criar(size_t capacidade);

/* Libera a memoria usada pela tabela */
void hash_destruir(HashTable *tabela);

/* Insere um usuario na tabela */
bool hash_inserir(HashTable *tabela, const char *usuario);

/* Busca um usuario na tabela */
bool hash_buscar(const HashTable *tabela, const char *usuario);

/* Funcoes auxiliares da tabela */
size_t hash_tamanho(const HashTable *tabela);
size_t hash_capacidade(const HashTable *tabela);
HashStats hash_estatisticas(const HashTable *tabela);

/* Mostra as estatisticas da tabela */
void hash_imprimir_estatisticas(const HashTable *tabela);

#endif
