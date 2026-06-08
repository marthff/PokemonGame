# PokemonGame

## Visão Geral

PokemonGame é um projeto desenvolvido em C++ com o objetivo de modelar batalhas Pokémon simplificadas utilizando conceitos de teoria dos grafos.

Em vez de simular apenas uma sequência específica de ações, o sistema constrói o espaço completo de estados alcançáveis durante um confronto entre dois Pokémon. Esse espaço é representado por um grafo direcionado, permitindo a execução de análises algorítmicas sobre os possíveis resultados da batalha.

O projeto foi desenvolvido com fins educacionais e acadêmicos, explorando conceitos como:

- modelagem de estados;
- teoria dos grafos;
- busca em largura (BFS);
- busca em profundidade (DFS);
- análise de complexidade;
- avaliação de cenários competitivos.

## Objetivos do Projeto

O sistema busca responder perguntas como:

- Qual equipe possui maior dominância estatística?
- Qual Pokémon apresenta o melhor desempenho geral?
- Existem confrontos com vitória garantida?
- Existem batalhas potencialmente infinitas?
- A vantagem de tipo é sempre determinante?

## Estrutura do Projeto

```text
.
├── CombatGraph.h
├── MetaAnalyzer.h
├── PokemonBase.h
├── main.cpp
├── CMakeLists.txt
├── README.md
└── .docs/
    ├── index.md
    ├── PokemonBase.md
    ├── CombatGraph.md
    ├── MetaAnalyzer.md
    ├── main.md
    └── CMakeLists.md
```

## Requisitos

Antes de compilar o projeto, certifique-se de possuir:

- Compilador compatível com C++14
  - GCC
  - Clang
  - MSVC

- CMake

Versão recomendada:

```text
CMake 3.15+
```

## Compilação

Criar diretório de build:

```
mkdir build
cd build
```

Gerar os arquivos de compilação:

```
cmake ..
```

Compilar:

```
cmake --build .
```

Executar:

**Linux**

```bash
./PokemonGame
```

**Windows**

```powershell
./PokemonGame
```

## Funcionamento

Ao iniciar o programa, um menu interativo é exibido.

### Opção 1 — Análise Global do Metagame

Executa todos os confrontos possíveis entre os dois times.

Total de confrontos:

```text
6 × 6 = 36 batalhas
```

Para cada batalha:

- o grafo é construído;
- as métricas são calculadas;
- os resultados são agregados.

Ao final, um relatório consolidado é apresentado.

### Opção 2 — Simulação de Combate Específico

Permite selecionar manualmente um Pokémon de cada equipe.

O sistema então:

- constrói o grafo correspondente;
- executa uma simulação demonstrativa;
- exibe a evolução dos estados da batalha.

### Opção 3 — Encerrar

Finaliza a execução do programa.

## Documentação

A documentação técnica completa encontra-se no diretório:

```text
.docs/
```

O ponto de entrada recomendado é:

```text
.docs/index.md
```

A documentação descreve:

- arquitetura do sistema;
- estruturas de dados;
- algoritmos utilizados;
- análise de complexidade;
- modelagem dos estados;
- funcionamento dos grafos de combate.

## Finalidade Acadêmica

Este projeto foi desenvolvido como exercício acadêmico para aplicação prática de conceitos de:

- Programação Orientada a Objetos;
- Estruturas de Dados;
- Teoria dos Grafos;
- Análise de Algoritmos;
- Modelagem de Sistemas.

As regras de batalha foram simplificadas intencionalmente para priorizar a análise computacional do problema.

## Licença

Este projeto é distribuído sob os termos definidos no arquivo LICENSE presente no repositório.
