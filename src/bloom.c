#include "bloom.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura interna do filtro */
struct BloomFilter {
    unsigned char *bits;
    size_t tamanho_bits;
    size_t quantidade_hashes;
};

/* Primeira funcao hash (djb2) */
static unsigned long hash_djb2(const char *texto) {
    unsigned long hash = 5381;
    int caractere;

    while ((caractere = (unsigned char)*texto++) != '\0') {
        hash = ((hash << 5) + hash) + (unsigned long)caractere;
    }

    return hash;
}

/* Segunda funcao hash (sdbm) */
static unsigned long hash_sdbm(const char *texto) {
    unsigned long hash = 0;
    int caractere;

    while ((caractere = (unsigned char)*texto++) != '\0') {
        hash = (unsigned long)caractere + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

/* Gera a posicao utilizando double hashing */
static size_t bloom_indice(const BloomFilter *bloom,
                           const char *usuario,
                           size_t tentativa) {

    unsigned long h1 = hash_djb2(usuario);
    unsigned long h2 = hash_sdbm(usuario);

    return (h1 + tentativa * h2) % bloom->tamanho_bits;
}

/* Cria o filtro */
BloomFilter *bloom_criar(size_t tamanho_bits,
                         size_t quantidade_hashes) {

    BloomFilter *bloom;

    if (tamanho_bits == 0 || quantidade_hashes == 0) {
        return NULL;
    }

    bloom = (BloomFilter *) malloc(sizeof(BloomFilter));

    if (bloom == NULL) {
        return NULL;
    }

    bloom->bits = (unsigned char *) calloc(tamanho_bits,
                                           sizeof(unsigned char));

    if (bloom->bits == NULL) {
        free(bloom);
        return NULL;
    }

    bloom->tamanho_bits = tamanho_bits;
    bloom->quantidade_hashes = quantidade_hashes;

    return bloom;
}

/* Libera a memoria */
void bloom_destruir(BloomFilter *bloom) {

    if (bloom == NULL) {
        return;
    }

    free(bloom->bits);
    free(bloom);
}
/* Insere um usuario no filtro */
void bloom_inserir(BloomFilter *bloom, const char *usuario) {
    size_t i;

    if (bloom == NULL || usuario == NULL || usuario[0] == '\0') {
        return;
    }

    for (i = 0; i < bloom->quantidade_hashes; i++) {
        size_t indice = bloom_indice(bloom, usuario, i);
        bloom->bits[indice] = 1;
    }
}

/* Consulta um usuario no filtro */
bool bloom_consultar(const BloomFilter *bloom, const char *usuario) {
    size_t i;

    if (bloom == NULL || usuario == NULL || usuario[0] == '\0') {
        return false;
    }

    for (i = 0; i < bloom->quantidade_hashes; i++) {
        size_t indice = bloom_indice(bloom, usuario, i);

        if (bloom->bits[indice] == 0) {
            return false;
        }
    }

    return true;
}
/* Calcula estatisticas do filtro */
BloomStats bloom_estatisticas(const BloomFilter *bloom) {
    BloomStats stats = {0};
    size_t i;

    if (bloom == NULL) {
        return stats;
    }

    stats.tamanho_bits = bloom->tamanho_bits;
    stats.quantidade_hashes = bloom->quantidade_hashes;

    for (i = 0; i < bloom->tamanho_bits; i++) {
        if (bloom->bits[i] == 1) {
            stats.bits_marcados++;
        }
    }

    return stats;
}

/* Mostra as estatisticas do filtro */
void bloom_imprimir_estatisticas(const BloomFilter *bloom) {
    BloomStats stats = bloom_estatisticas(bloom);

    printf("Tamanho do vetor Bloom: %zu bits\n", stats.tamanho_bits);
    printf("Quantidade de funcoes hash: %zu\n", stats.quantidade_hashes);
    printf("Bits marcados: %zu\n", stats.bits_marcados);
}
#ifdef BLOOM_TEST_MAIN
#include <assert.h>

/* Testa criacao do filtro */
static void teste_criar_bloom(void) {
    BloomFilter *bloom = bloom_criar(1000, 3);

    assert(bloom != NULL);

    bloom_destruir(bloom);
}

/* Testa insercao e consulta */
static void teste_inserir_e_consultar(void) {
    BloomFilter *bloom = bloom_criar(1000, 3);

    bloom_inserir(bloom, "ana123");
    bloom_inserir(bloom, "maria98");

    assert(bloom_consultar(bloom, "ana123"));
    assert(bloom_consultar(bloom, "maria98"));

    bloom_destruir(bloom);
}

/* Testa usuario que nao foi inserido */
static void teste_usuario_inexistente(void) {
    BloomFilter *bloom = bloom_criar(100000, 3);

    bloom_inserir(bloom, "joao123");

    assert(!bloom_consultar(bloom, "usuario_que_nao_existe"));

    bloom_destruir(bloom);
}

/* Testa estatisticas */
static void teste_estatisticas(void) {
    BloomFilter *bloom = bloom_criar(1000, 3);
    BloomStats stats;

    bloom_inserir(bloom, "ana123");
    bloom_inserir(bloom, "maria98");

    stats = bloom_estatisticas(bloom);

    assert(stats.tamanho_bits == 1000);
    assert(stats.quantidade_hashes == 3);
    assert(stats.bits_marcados > 0);

    bloom_destruir(bloom);
}

int main(void) {
    teste_criar_bloom();
    teste_inserir_e_consultar();
    teste_usuario_inexistente();
    teste_estatisticas();

    printf("Todos os testes do Filtro de Bloom passaram.\n");

    return 0;
}
#endif