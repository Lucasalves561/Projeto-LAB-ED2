#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash.h"
#include "bloom.h"

#define TAM_HASH 200003
#define TAM_BLOOM 1000000
#define NUM_HASHES 3

/* Pausa o programa para o usuario conseguir ler a mensagem */
void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);
    getchar();
}

/* Insere um usuario na tabela hash e no filtro de Bloom */
void inserir_usuario(HashTable *hash, BloomFilter *bloom) {
    char usuario[100];

    printf("\nNovo usuario: ");
    fflush(stdout);

    if (scanf("%99s", usuario) != 1) {
        return;
    }

    while (getchar() != '\n');

    /* Primeiro insere na hash, se ainda nao existir */
    if (hash_inserir(hash, usuario)) {
        bloom_inserir(bloom, usuario);
        printf("\nUsuario inserido com sucesso!\n");
    } else {
        printf("\nUsuario ja existe.\n");
    }

    pausar();
}

/* Consulta primeiro no Bloom e depois confirma na hash */
void consultar_usuario(HashTable *hash, BloomFilter *bloom) {
    char usuario[100];

    printf("\nDigite o usuario: ");
    fflush(stdout);

    if (scanf("%99s", usuario) != 1) {
        return;
    }

    while (getchar() != '\n');

    /* Se o Bloom disser que nao existe, nao precisa consultar a hash */
    if (!bloom_consultar(bloom, usuario)) {
        printf("\nUsuario definitivamente nao existe.\n");
        pausar();
        return;
    }

    /* Se o Bloom disser que talvez exista, confirma na hash */
    if (hash_buscar(hash, usuario)) {
        printf("\nUsuario encontrado.\n");
    } else {
        printf("\nFalso positivo do Bloom.\n");
    }

    pausar();
}

/* Carrega os usuarios de um arquivo texto */
void carregar_usuarios(HashTable *hash, BloomFilter *bloom, const char *arquivo) {
    FILE *fp;
    char usuario[100];
    int total = 0;

    fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return;
    }

    /* Le cada linha do arquivo e insere nas duas estruturas */
    while (fgets(usuario, sizeof(usuario), fp) != NULL) {
        usuario[strcspn(usuario, "\n")] = '\0';

        if (strlen(usuario) == 0) {
            continue;
        }

        hash_inserir(hash, usuario);
        bloom_inserir(bloom, usuario);
        total++;
    }

    fclose(fp);

    printf("%d usuarios carregados com sucesso!\n", total);
}

/* Executa um teste comparando busca com Bloom e sem Bloom */
void executar_experimento(const char *arquivo_usuarios,
                          const char *arquivo_consultas,
                          int quantidade) {
    FILE *fp;
    char usuario[100];

    HashTable *hash;
    BloomFilter *bloom;

    clock_t inicio, fim;
    double tempo_sem_bloom;
    double tempo_com_bloom;

    int consultas = 0;
    int falsos_positivos = 0;
    int consultas_evitadas = 0;

    /* Cria uma hash e um Bloom novos para cada experimento */
    hash = hash_criar(TAM_HASH);
    bloom = bloom_criar(TAM_BLOOM, NUM_HASHES);

    if (hash == NULL || bloom == NULL) {
        printf("Erro ao criar estruturas para experimento.\n");
        return;
    }

    fp = fopen(arquivo_usuarios, "r");

    if (fp == NULL) {
        printf("Erro ao abrir %s\n", arquivo_usuarios);
        hash_destruir(hash);
        bloom_destruir(bloom);
        return;
    }

    /* Carrega os usuarios cadastrados */
    while (fgets(usuario, sizeof(usuario), fp) != NULL) {
        usuario[strcspn(usuario, "\n")] = '\0';

        if (strlen(usuario) == 0) {
            continue;
        }

        hash_inserir(hash, usuario);
        bloom_inserir(bloom, usuario);
    }

    fclose(fp);

    fp = fopen(arquivo_consultas, "r");

    if (fp == NULL) {
        printf("Erro ao abrir %s\n", arquivo_consultas);
        hash_destruir(hash);
        bloom_destruir(bloom);
        return;
    }

    /* Mede o tempo buscando direto na tabela hash */
    inicio = clock();

    while (fgets(usuario, sizeof(usuario), fp) != NULL) {
        usuario[strcspn(usuario, "\n")] = '\0';

        if (strlen(usuario) == 0) {
            continue;
        }

        hash_buscar(hash, usuario);
    }

    fim = clock();
    tempo_sem_bloom = (double)(fim - inicio) / CLOCKS_PER_SEC;

    fclose(fp);

    fp = fopen(arquivo_consultas, "r");

    /* Mede o tempo consultando primeiro no Bloom */
    inicio = clock();

    while (fgets(usuario, sizeof(usuario), fp) != NULL) {
        usuario[strcspn(usuario, "\n")] = '\0';

        if (strlen(usuario) == 0) {
            continue;
        }

        consultas++;

        if (!bloom_consultar(bloom, usuario)) {
            consultas_evitadas++;
        } else {
            if (!hash_buscar(hash, usuario)) {
                falsos_positivos++;
            }
        }
    }

    fim = clock();
    tempo_com_bloom = (double)(fim - inicio) / CLOCKS_PER_SEC;

    fclose(fp);

    printf("%-12d %-18.6f %-18.6f %-18d %-18d\n",
           quantidade,
           tempo_sem_bloom,
           tempo_com_bloom,
           falsos_positivos,
           consultas_evitadas);

    hash_destruir(hash);
    bloom_destruir(bloom);
}

/* Executa os experimentos pedidos no trabalho */
void executar_experimentos(void) {
    printf("\nQuantidade   Tempo sem Bloom    Tempo com Bloom    Falsos Positivos   Consultas Evitadas\n");
    printf("-----------------------------------------------------------------------------------------\n");

    executar_experimento("data/usuarios1000.txt", "data/consultas1000.txt", 1000);
    executar_experimento("data/usuarios10000.txt", "data/consultas10000.txt", 10000);
    executar_experimento("data/usuarios100000.txt", "data/consultas100000.txt", 100000);

    pausar();
}

/* Funcao principal do programa */
int main(void) {
    HashTable *hash;
    BloomFilter *bloom;
    int opcao;

    /* Cria as estruturas principais */
    hash = hash_criar(TAM_HASH);
    bloom = bloom_criar(TAM_BLOOM, NUM_HASHES);

    if (hash == NULL || bloom == NULL) {
        printf("Erro ao criar estruturas.\n");
        return 1;
    }

    /* Carrega os usuarios iniciais */
    carregar_usuarios(hash, bloom, "data/usuarios.txt");

    /* Menu principal */
    do {
        printf("\n==============================\n");
        printf("1 - Inserir usuario\n");
        printf("2 - Consultar usuario\n");
        printf("3 - Estatisticas Hash\n");
        printf("4 - Estatisticas Bloom\n");
        printf("5 - Executar experimentos\n");
        printf("0 - Sair\n");
        printf("==============================\n");
        printf("Opcao: ");
        fflush(stdout);

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }

        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                inserir_usuario(hash, bloom);
                break;

            case 2:
                consultar_usuario(hash, bloom);
                break;

            case 3:
                hash_imprimir_estatisticas(hash);
                pausar();
                break;

            case 4:
                bloom_imprimir_estatisticas(bloom);
                pausar();
                break;

            case 5:
                executar_experimentos();
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                pausar();
        }

    } while (opcao != 0);

    /* Libera a memoria antes de finalizar */
    hash_destruir(hash);
    bloom_destruir(bloom);

    return 0;
}