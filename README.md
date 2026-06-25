# Sistema de Consulta Eficiente com Tabela Hash e Filtro de Bloom

Projeto em C para consulta rapida de usuarios cadastrados usando duas estruturas complementares:

- Tabela Hash para busca exata
- Filtro de Bloom para reduzir consultas desnecessarias

Esta versao do repositorio contem a parte do **Integrante 1**, responsavel pela Tabela Hash.

## Estrutura atual

- `hash.h` - interface publica da tabela hash
- `hash.c` - implementacao da tabela hash e testes unitarios

## O que esta implementado

- criacao e destruicao da tabela
- insercao de usuarios
- busca de usuarios
- tratamento de colisao com encadeamento externo
- calculo de estatisticas da tabela
- testes unitarios basicos

## Requisitos

- compilador C compativel com C99
- `gcc` instalado e disponivel no terminal

## Como compilar os testes da tabela hash

No Windows com `gcc` no `PATH`:

```powershell
gcc -Wall -Wextra -std=c99 -DHASH_TEST_MAIN hash.c -o teste_hash.exe
```

Se o comando acima funcionar, execute:

```powershell
.\teste_hash.exe
```

Saida esperada:

```text
Todos os testes da Tabela Hash passaram.
```

## Como usar no projeto final

O arquivo `hash.c` deve ser compilado junto com o restante do trabalho.

Exemplo de integracao futura:

```powershell
gcc -Wall -Wextra -std=c99 main.c bloom.c hash.c -o projeto.exe
```

## Formato dos dados

A parte da Tabela Hash trabalha com identificadores de usuarios em texto simples.

Exemplo:

```text
joao123
maria98
pedro45
```

## Observacoes

- A funcao hash foi implementada manualmente.
- O tratamento de colisao usa lista ligada em cada bucket.
- A estrutura nao usa biblioteca pronta de tabela hash.
- Remocao nao foi incluida porque nao e obrigatoria no enunciado.

## Referencias

- Documentacao da linguagem C
- Conceitos de Tabela Hash com encadeamento externo
- Conceitos de encadeamento e colisao em estruturas de dados

## Licenca

Projeto academico para disciplina de Estruturas de Dados.
