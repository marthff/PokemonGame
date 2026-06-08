# MetaAnalyzer

## Visão Geral

A classe `MetaAnalyzer` executa análises sobre o grafo de combate.

Seu objetivo é extrair informações estratégicas e estatísticas dos estados gerados.

---

## DetectEndlessBattles

### Objetivo

Detectar ciclos alcançáveis no grafo.

### Algoritmo

Depth-First Search (DFS).

### Funcionamento

Mantém dois conjuntos:

- visited
- stack

Se um estado for encontrado novamente durante a mesma pilha de recursão, um ciclo foi detectado.

### Complexidade

```text
O(V + E)
```

---

## CheckAbsoluteWinner

### Objetivo

Verificar se existe um vencedor absoluto.

### Definição

Um Pokémon é considerado vencedor absoluto quando todos os estados terminais alcançáveis resultam exclusivamente em sua vitória.

Não podem existir:

- derrotas;
- empates;
- ciclos considerados estados não conclusivos.

### Retorno

| Valor | Significado                   |
| ----- | ----------------------------- |
| 0     | Não existe vencedor absoluto  |
| 1     | Pokémon 1 é vencedor absoluto |
| 2     | Pokémon 2 é vencedor absoluto |

### Algoritmo

Breadth-First Search (BFS).

### Complexidade

```text
O(V + E)
```

---

## CalculateWinRateP1

### Objetivo

Calcular a taxa de vitória do Pokémon 1.

### Fórmula

```text
vitórias do P1
-------------------------
total de estados terminais
```

### Complexidade

```text
O(V)
```

---

## PrintSampleBattle

### Objetivo

Exibir uma trajetória de exemplo.

### Observação

Não representa uma estratégia ótima.

O método seleciona preferencialmente a combinação:

```text
(0,0)
```

ou seja:

- primeiro movimento do Pokémon 1;
- primeiro movimento do Pokémon 2.

O objetivo é apenas demonstrar a evolução dos estados.
