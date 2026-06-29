#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerar_usuario(char usuario[]) {
    int i;

    for (i = 0; i < 8; i++) {
        usuario[i] = 'a' + rand() % 26;
    }

    for (i = 8; i < 11; i++) {
        usuario[i] = '0' + rand() % 10;
    }

    usuario[11] = '\0';
}

void gerar_arquivo(const char *nome_arquivo, int quantidade, const char *prefixo) {
    FILE *fp;
    char usuario[20];
    int i;

    fp = fopen(nome_arquivo, "w");

    if (fp == NULL) {
        printf("Erro ao criar arquivo %s\n", nome_arquivo);
        return;
    }

    for (i = 0; i < quantidade; i++) {
        gerar_usuario(usuario);
        fprintf(fp, "%s%s\n", prefixo, usuario);
    }

    fclose(fp);
    printf("Arquivo %s criado com %d registros.\n", nome_arquivo, quantidade);
}

int main(void) {
    srand(time(NULL));

    gerar_arquivo("data/usuarios1000.txt", 1000, "");
gerar_arquivo("data/usuarios10000.txt", 10000, "");
gerar_arquivo("data/usuarios100000.txt", 100000, "");

gerar_arquivo("data/consultas1000.txt", 1000, "");
gerar_arquivo("data/consultas10000.txt", 10000, "");
gerar_arquivo("data/consultas100000.txt", 100000, "");

    return 0;
}
