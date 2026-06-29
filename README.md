# Sistema de Consulta Eficiente com Tabela Hash e Filtro de Bloom

Projeto desenvolvido em C para realizar consultas rápidas de usuários utilizando duas estruturas de dados complementares:

* **Tabela Hash** para armazenamento e busca exata dos usuários;
* **Filtro de Bloom** para reduzir consultas desnecessárias à Tabela Hash, aumentando a eficiência do sistema.

O projeto foi desenvolvido para a disciplina de **Estruturas de Dados**.

---

# Estrutura do Projeto

```text
Projeto-LAB-ED2/
│
├── src/
│   ├── main.c
│   ├── hash.c
│   ├── hash.h
│   ├── bloom.c
│   ├── bloom.h
│   └── gerar_usuarios.c
│
├── data/
│   ├── usuarios.txt
│   ├── usuarios1000.txt
│   ├── usuarios10000.txt
│   ├── usuarios100000.txt
│   ├── consultas1000.txt
│   ├── consultas10000.txt
│   └── consultas100000.txt
│
├── README.md
└── .gitignore
```

---

# Funcionalidades

O sistema permite:

* Inserir usuários manualmente;
* Consultar usuários cadastrados;
* Carregar usuários a partir de arquivos de texto;
* Consultar usuários utilizando primeiro o Filtro de Bloom;
* Confirmar consultas utilizando a Tabela Hash;
* Visualizar estatísticas da Tabela Hash;
* Visualizar estatísticas do Filtro de Bloom;
* Executar experimentos de desempenho com diferentes volumes de dados.

---

# Implementação

## Tabela Hash

A Tabela Hash foi implementada utilizando:

* função hash própria;
* tratamento de colisões por encadeamento externo;
* inserção de usuários;
* busca de usuários;
* estatísticas de utilização.

## Filtro de Bloom

O Filtro de Bloom foi implementado utilizando:

* vetor de bits;
* múltiplas funções hash;
* inserção de usuários;
* consulta probabilística;
* medição de falsos positivos.

---

# Requisitos

* Compilador compatível com o padrão C99;
* GCC instalado.

---

# Como Compilar

```bash
gcc -Wall -Wextra -std=c99 src/main.c src/hash.c src/bloom.c -o projeto
```

---

# Como Executar

```bash
./projeto
```
---

# Gerando os Arquivos de Teste

Caso seja necessário gerar novamente os arquivos utilizados nos experimentos, execute:

```bash
gcc -Wall -Wextra -std=c99 src/gerar_usuarios.c -o gerar_usuarios
./gerar_usuarios
```

Esse programa gera automaticamente os arquivos de usuários e consultas utilizados nos experimentos com 1.000, 10.000 e 100.000 registros.

---

# Arquivos de Entrada

Os usuários são armazenados em arquivos de texto, contendo um usuário por linha.

Exemplo:

```text
joao123
maria98
pedro45
```

Também são utilizados arquivos específicos para os experimentos:

* usuarios1000.txt
* usuarios10000.txt
* usuarios100000.txt
* consultas1000.txt
* consultas10000.txt
* consultas100000.txt

---

# Funcionamento

Quando um usuário é consultado, o sistema realiza os seguintes passos:

1. Consulta o Filtro de Bloom.
2. Se o Bloom indicar que o usuário definitivamente não existe, a busca termina imediatamente.
3. Caso o Bloom indique que o usuário pode existir, a Tabela Hash é consultada para confirmar.

Essa estratégia reduz o número de consultas realizadas diretamente na Tabela Hash.

---

# Experimentos

O sistema realiza experimentos utilizando bases de dados com:

* 1.000 usuários;
* 10.000 usuários;
* 100.000 usuários.

Durante os experimentos são coletadas as seguintes métricas:

* tempo de busca utilizando apenas a Tabela Hash;
* tempo de busca utilizando o Filtro de Bloom;
* quantidade de falsos positivos;
* quantidade de consultas evitadas pelo Filtro de Bloom.

---

# Exemplo de Execução

Ao executar o programa, o sistema apresenta o menu principal:

```text
10 usuarios carregados com sucesso!

==============================
1 - Inserir usuario
2 - Consultar usuario
3 - Estatisticas Hash
4 - Estatisticas Bloom
5 - Executar experimentos
0 - Sair
==============================
Opcao:
```

### Exemplo de inserção

```text
Opcao: 1

Novo usuario: analara123

Usuario inserido com sucesso!
```

### Exemplo de consulta

```text
Opcao: 2

Digite o usuario: analara123

Usuario encontrado.
```

Caso o usuário não esteja cadastrado:

```text
Opcao: 2

Digite o usuario: usuario999

Usuario definitivamente nao existe.
```

### Exemplo de execução dos experimentos

```text
Opcao: 5

Qtd    Tempo Hash(s)    Tempo Bloom(s)   Consultas   Evitadas   Falsos Positivos   Taxa(%)   Tempo Medio
-------------------------------------------------------------------------------------------------------------
1000    0.000181        0.000173         1000        1000       0                  0.00     0.00000017
10000   0.002041        0.001820         10000       9998       2                  0.02     0.00000018
100000  0.018545        0.017604         100000      97603      2397               2.40     0.00000018
```

Durante os experimentos, o sistema compara o tempo de consulta utilizando apenas a Tabela Hash e utilizando o Filtro de Bloom juntamente com a Tabela Hash. Também são apresentadas a quantidade de consultas realizadas, consultas evitadas, número de falsos positivos, taxa de falsos positivos e tempo médio de consulta.

---

# Observações

* A implementação não utiliza bibliotecas prontas para Tabela Hash ou Filtro de Bloom.
* Todas as funções hash foram implementadas manualmente.
* O Filtro de Bloom pode gerar falsos positivos.
* Não existem falsos negativos para elementos previamente inseridos.
* A remoção de usuários não foi implementada por não ser um requisito do projeto.

---

# Integrantes

* LUCAS — Implementação da Tabela Hash.
* JORGE — Implementação do Filtro de Bloom.
* ANA LARA — Integração do sistema, experimentos e análise dos resultados.

---

# Licença

Projeto acadêmico desenvolvido para a disciplina de Laboratorio de Estruturas de Dados II.
