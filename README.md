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

# Observações

* A implementação não utiliza bibliotecas prontas para Tabela Hash ou Filtro de Bloom.
* Todas as funções hash foram implementadas manualmente.
* O Filtro de Bloom pode gerar falsos positivos.
* Não existem falsos negativos para elementos previamente inseridos.
* A remoção de usuários não foi implementada por não ser um requisito do projeto.

---

# Integrantes

* Integrante 1 — Implementação da Tabela Hash.
* Integrante 2 — Implementação do Filtro de Bloom.
* Integrante 3 — Integração do sistema, experimentos e análise dos resultados.

---

# Referências

* Documentação oficial da linguagem C.
* Material da disciplina de Estruturas de Dados.
* Conceitos de Tabela Hash.
* Conceitos de Filtro de Bloom.

---

# Licença

Projeto acadêmico desenvolvido para a disciplina de Laboratorio de Estruturas de Dados II.
