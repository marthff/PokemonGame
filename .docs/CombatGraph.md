# CombatGraph

## Visão Geral

A classe `CombatGraph` é o núcleo do projeto.

Sua responsabilidade é gerar e armazenar o espaço completo de estados alcançáveis durante uma batalha entre dois Pokémon.

O resultado é um grafo direcionado onde:

- vértices representam estados;
- arestas representam transições causadas por ações dos jogadores.

## Estrutura Transition

Representa uma aresta do grafo.

### Atributos

| Campo       | Descrição                          |
| ----------- | ---------------------------------- |
| moveIdx1    | Movimento utilizado pelo Pokémon 1 |
| moveIdx2    | Movimento utilizado pelo Pokémon 2 |
| nextStateId | Identificador do estado destino    |

## Estrutura GraphNode

Representa um vértice do grafo.

### Atributos

| Campo       | Descrição            |
| ----------- | -------------------- |
| state       | Estado da batalha    |
| transitions | Transições possíveis |

## Classe CombatGraph

### Responsabilidade

Construir e armazenar todos os estados alcançáveis de um confronto.

### graphMap

```cpp
std::unordered_map<std::string, GraphNode*>
```

Tabela hash utilizada para:

- localizar estados rapidamente;
- evitar duplicação de vértices;
- reutilizar estados já descobertos.

### Complexidade

Busca média:

```text
O(1)
```

### rootId

Identificador do estado inicial da batalha.

Serve como ponto de entrada para algoritmos de busca.

## Algoritmo de Construção

### BuildGraph

Constrói o grafo utilizando Breadth-First Search (BFS).

Fluxo:

1. Inserir estado inicial na fila.
2. Processar estados pendentes.
3. Gerar todas as combinações de ações possíveis.
4. Produzir estados sucessores.
5. Inserir novos estados na fila.
6. Registrar transições.

## Complexidade

Se:

```text
V = quantidade de estados
E = quantidade de transições
```

Então:

### Tempo

```text
O(V + E)
```

### Espaço

```text
O(V + E)
```

## Decisão de Projeto

Estados iguais são reutilizados.

Isso é realizado através da função:

```cpp
Identity()
```

Antes de criar um novo vértice, a tabela hash é consultada.

Caso o estado já exista, apenas uma nova transição é registrada.

Essa estratégia evita crescimento redundante do grafo.
