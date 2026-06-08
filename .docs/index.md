# Documentação Técnica

## Visão Geral

Este projeto modela batalhas Pokémon simplificadas como um problema de teoria dos grafos.

Em vez de simular apenas uma sequência específica de ações, o sistema constrói o conjunto completo de estados alcançáveis para um confronto entre dois Pokémon e representa essas possibilidades através de um grafo direcionado.

Após a construção do grafo, algoritmos de análise são executados para responder perguntas como:

- Qual a taxa de vitória de um Pokémon?
- Existe um vencedor absoluto?
- Existem ciclos que tornam a batalha interminável?
- Qual equipe possui maior dominância estatística?

O domínio Pokémon foi utilizado como contexto para o estudo de modelagem de estados, exploração de grafos e análise algorítmica.

## Arquitetura

```text
main.cpp
    │
    ▼
MetaAnalyzer
    │
    ▼
CombatGraph
    │
    ▼
State
Pokemon
Move
TypeChart
```

### Responsabilidades

| Componente   | Responsabilidade                             |
| ------------ | -------------------------------------------- |
| main.cpp     | Execução da simulação e geração do relatório |
| PokemonBase  | Modelo de dados da batalha                   |
| CombatGraph  | Construção do espaço de estados              |
| MetaAnalyzer | Execução das análises sobre o grafo          |

## Conceitos Fundamentais

### Estado

Um estado representa um instante da batalha.

Exemplo:

```text
Charizard_70_Blastoise_40
```

Significa:

- Charizard com 70% de HP
- Blastoise com 40% de HP

### Grafo de Combate

Cada estado é modelado como um vértice.

Cada combinação possível de ações gera uma transição para outro estado.

```text
Estado A
    │
    ├── (Flamethrower, Hydro Pump)
    ▼
Estado B

    ├── (Recover, Hydro Pump)
    ▼
Estado C
```

### Controle da Explosão Combinatória

Para limitar o crescimento do espaço de estados, o projeto utiliza uma discretização do HP.

Características:

- HP representado entre 0% e 100%.
- Danos arredondados para múltiplos de 10%.
- Cura fixa de 50%.

Essa simplificação reduz significativamente a quantidade de estados distintos possíveis, tornando viável a construção completa do grafo.

## Documentos

- [PokemonBase.md](PokemonBase.md)
- [CombatGraph.md](CombatGraph.md)
- [MetaAnalyzer.md](MetaAnalyzer.md)
- [main.md](main.md)
