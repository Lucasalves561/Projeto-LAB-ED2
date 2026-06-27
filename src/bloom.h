#ifndef BLOOM_H
#define BLOOM_H

#include <stddef.h>
#include <stdbool.h>

/* Tipo usado para esconder os campos internos do filtro */
typedef struct BloomFilter BloomFilter;

/* Dados usados na analise do filtro */
typedef struct {
    size_t tamanho_bits;
    size_t quantidade_hashes;
    size_t bits_marcados;
} BloomStats;

/* Cria o filtro de Bloom */
BloomFilter *bloom_criar(size_t tamanho_bits, size_t quantidade_hashes);

/* Libera a memoria usada pelo filtro */
void bloom_destruir(BloomFilter *bloom);

/* Insere um usuario no filtro */
void bloom_inserir(BloomFilter *bloom, const char *usuario);

/* Consulta um usuario no filtro */
bool bloom_consultar(const BloomFilter *bloom, const char *usuario);

/* Estatisticas */
BloomStats bloom_estatisticas(const BloomFilter *bloom);

/* Mostra as estatisticas */
void bloom_imprimir_estatisticas(const BloomFilter *bloom);

#endif