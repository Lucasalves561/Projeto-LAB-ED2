# Sistema de Consulta Eficiente com Tabela Hash e Filtro de Bloom

Projeto em C para consulta rápida de usuários cadastrados usando duas estruturas complementares:

* Tabela Hash para busca exata;
* Filtro de Bloom para reduzir consultas desnecessárias.

Esta versão do repositório contém a parte do **Integrante 2**, responsável pela implementação do **Filtro de Bloom**.

## Estrutura atual

* `bloom.h` - interface pública do Filtro de Bloom;
* `bloom.c` - implementação do Filtro de Bloom e funções hash;
* `hash.h` - interface pública da Tabela Hash;
* `hash.c` - implementação da Tabela Hash.

## O que está implementado no Filtro de Bloom

* criação e destruição do filtro;
* vetor de bits;
* inserção de usuários no filtro;
* consulta de usuários no filtro;
* uso de múltiplas funções hash;
* estatísticas básicas do filtro;
* apoio à medição de falsos positivos.

## Requisitos

* compilador C compatível com C99;
* `gcc` instalado e disponível no terminal.

## Como compilar o projeto

No Windows com `gcc` no `PATH`:

```powershell
gcc -Wall -Wextra -std=c99 main.c bloom.c hash.c -o projeto.exe
```

Para executar:

```powershell
.\projeto.exe
```

## Formato dos dados

Os usuários devem estar em um arquivo de texto, um por linha.

Exemplo:

```text
joao123
maria98
pedro45
```

## Como funciona o Filtro de Bloom

O Filtro de Bloom é usado antes da Tabela Hash.

Quando um usuário é inserido, o sistema marca posições no vetor de bits usando funções hash.
Na consulta, se alguma posição estiver com valor 0, o usuário definitivamente não existe.
Se todas as posições estiverem marcadas, o usuário possivelmente existe, então a Tabela Hash é consultada para confirmar.

## Observações

* O Filtro de Bloom não utiliza biblioteca pronta;
* As funções hash foram implementadas manualmente;
* O filtro pode gerar falsos positivos;
* Não há falsos negativos para usuários que foram inseridos corretamente;
* Remoção não foi implementada porque não é obrigatória no enunciado.

## Referências

* Conceitos de Filtro de Bloom;
* Conceitos de Tabela Hash;
* Documentação da linguagem C;
* Material da disciplina de Estruturas de Dados.

## Licença

Projeto acadêmico para disciplina de Estruturas de Dados.
