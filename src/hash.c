#include "hash.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoHash {
    char *usuario;
    struct NoHash *proximo;
} NoHash;

/* Cada posicao da tabela aponta para uma lista ligada */
struct HashTable {
    NoHash **buckets;
    size_t capacidade;
    size_t quantidade;
    size_t total_colisoes;
};

/* Copia uma string para uma nova area de memoria */
static char *hash_strdup(const char *texto) {
    size_t tamanho;
    char *copia;

    if (texto == NULL) {
        return NULL;
    }

    tamanho = strlen(texto) + 1;
    copia = (char *)malloc(tamanho);
    if (copia == NULL) {
        return NULL;
    }

    memcpy(copia, texto, tamanho);
    return copia;
}

/* Funcao hash djb2 */
static unsigned long hash_djb2(const char *texto) {
    unsigned long hash = 5381;
    int caractere;

    while ((caractere = (unsigned char)*texto++) != '\0') {
        hash = ((hash << 5) + hash) + (unsigned long)caractere;
    }

    return hash;
}

/* Calcula a posicao dentro da tabela */
static size_t hash_indice(const HashTable *tabela, const char *usuario) {
    return hash_djb2(usuario) % tabela->capacidade;
}

HashTable *hash_criar(size_t capacidade) {
    HashTable *tabela;

    if (capacidade == 0) {
        return NULL;
    }

    tabela = (HashTable *)malloc(sizeof(HashTable));
    if (tabela == NULL) {
        return NULL;
    }

    tabela->buckets = (NoHash **)calloc(capacidade, sizeof(NoHash *));
    if (tabela->buckets == NULL) {
        free(tabela);
        return NULL;
    }

    tabela->capacidade = capacidade;
    tabela->quantidade = 0;
    tabela->total_colisoes = 0;

    return tabela;
}

void hash_destruir(HashTable *tabela) {
    size_t i;

    if (tabela == NULL) {
        return;
    }

    for (i = 0; i < tabela->capacidade; i++) {
        NoHash *atual = tabela->buckets[i];
        while (atual != NULL) {
            NoHash *proximo = atual->proximo;
            free(atual->usuario);
            free(atual);
            atual = proximo;
        }
    }

    free(tabela->buckets);
    free(tabela);
}

bool hash_inserir(HashTable *tabela, const char *usuario) {
    size_t indice;
    NoHash *atual;
    NoHash *novo;

    if (tabela == NULL || usuario == NULL || usuario[0] == '\0') {
        return false;
    }

    indice = hash_indice(tabela, usuario);
    atual = tabela->buckets[indice];

    /* Verifica se o usuario ja existe */
    while (atual != NULL) {
        if (strcmp(atual->usuario, usuario) == 0) {
            return false;
        }
        atual = atual->proximo;
    }

    novo = (NoHash *)malloc(sizeof(NoHash));
    if (novo == NULL) {
        return false;
    }

    novo->usuario = hash_strdup(usuario);
    if (novo->usuario == NULL) {
        free(novo);
        return false;
    }

    /* Se a posicao ja tinha alguem ocorreu colisao */
    if (tabela->buckets[indice] != NULL) {
        tabela->total_colisoes++;
    }

    /* Insere no inicio da lista */
    novo->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novo;
    tabela->quantidade++;

    return true;
}

bool hash_buscar(const HashTable *tabela, const char *usuario) {
    size_t indice;
    NoHash *atual;

    if (tabela == NULL || usuario == NULL || usuario[0] == '\0') {
        return false;
    }

    indice = hash_indice(tabela, usuario);
    atual = tabela->buckets[indice];

    /* Procura somente na lista da posicao calculada */
    while (atual != NULL) {
        if (strcmp(atual->usuario, usuario) == 0) {
            return true;
        }
        atual = atual->proximo;
    }

    return false;
}

size_t hash_tamanho(const HashTable *tabela) {
    return tabela == NULL ? 0 : tabela->quantidade;
}

size_t hash_capacidade(const HashTable *tabela) {
    return tabela == NULL ? 0 : tabela->capacidade;
}

HashStats hash_estatisticas(const HashTable *tabela) {
    HashStats stats = {0};
    size_t i;

    if (tabela == NULL) {
        return stats;
    }

    stats.capacidade = tabela->capacidade;
    stats.quantidade = tabela->quantidade;
    stats.total_colisoes = tabela->total_colisoes;
    stats.fator_carga = (double)tabela->quantidade / (double)tabela->capacidade;

    /* Percorre a tabela para calcular as estatisticas */
    for (i = 0; i < tabela->capacidade; i++) {
        size_t tamanho_cadeia = 0;
        NoHash *atual = tabela->buckets[i];

        while (atual != NULL) {
            tamanho_cadeia++;
            atual = atual->proximo;
        }

        if (tamanho_cadeia > 0) {
            stats.buckets_usados++;
        }

        if (tamanho_cadeia > 1) {
            stats.buckets_com_colisao++;
        }

        if (tamanho_cadeia > stats.maior_cadeia) {
            stats.maior_cadeia = tamanho_cadeia;
        }
    }

    return stats;
}

void hash_imprimir_estatisticas(const HashTable *tabela) {
    HashStats stats = hash_estatisticas(tabela);

    printf("Capacidade: %zu\n", stats.capacidade);
    printf("Usuarios cadastrados: %zu\n", stats.quantidade);
    printf("Buckets usados: %zu\n", stats.buckets_usados);
    printf("Buckets com colisao: %zu\n", stats.buckets_com_colisao);
    printf("Total de colisoes em insercoes: %zu\n", stats.total_colisoes);
    printf("Maior cadeia: %zu\n", stats.maior_cadeia);
    printf("Fator de carga: %.4f\n", stats.fator_carga);
}

#ifdef HASH_TEST_MAIN
/* Testes unitarios ativados com HASH_TEST_MAIN */
static void teste_criar_tabela(void) {
    HashTable *tabela = hash_criar(11);

    assert(tabela != NULL);
    assert(hash_tamanho(tabela) == 0);
    assert(hash_capacidade(tabela) == 11);

    hash_destruir(tabela);
}

static void teste_inserir_e_buscar(void) {
    HashTable *tabela = hash_criar(11);

    assert(hash_inserir(tabela, "ana"));
    assert(hash_inserir(tabela, "bruno"));
    assert(hash_inserir(tabela, "carla"));

    assert(hash_buscar(tabela, "ana"));
    assert(hash_buscar(tabela, "bruno"));
    assert(hash_buscar(tabela, "carla"));
    assert(!hash_buscar(tabela, "diego"));
    assert(hash_tamanho(tabela) == 3);

    hash_destruir(tabela);
}

static void teste_nao_insere_duplicado(void) {
    HashTable *tabela = hash_criar(11);

    assert(hash_inserir(tabela, "ana"));
    assert(!hash_inserir(tabela, "ana"));
    assert(hash_tamanho(tabela) == 1);

    hash_destruir(tabela);
}

static void teste_colisoes(void) {
    HashTable *tabela = hash_criar(2);
    HashStats stats;

    assert(hash_inserir(tabela, "ana"));
    assert(hash_inserir(tabela, "bruno"));
    assert(hash_inserir(tabela, "carla"));

    stats = hash_estatisticas(tabela);
    assert(stats.quantidade == 3);
    assert(stats.total_colisoes >= 1);
    assert(stats.maior_cadeia >= 2);

    hash_destruir(tabela);
}

int main(void) {
    teste_criar_tabela();
    teste_inserir_e_buscar();
    teste_nao_insere_duplicado();
    teste_colisoes();

    printf("Todos os testes da Tabela Hash passaram.\n");
    return 0;
}
#endif
