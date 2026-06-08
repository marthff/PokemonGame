# PokemonBase

## Visão Geral

O arquivo `PokemonBase.h` contém os principais elementos do domínio da aplicação.

Ele define:

- sistema de tipos Pokémon;
- golpes disponíveis;
- estrutura de um Pokémon;
- cálculo de dano;
- representação de estados de batalha.

Todos os demais componentes do projeto dependem direta ou indiretamente dessas definições.

---

# Sistema de Tipos

## Enum Type

Representa os tipos elementais disponíveis.

```cpp
enum Type
```

Exemplos:

- FIRE
- WATER
- GRASS
- DRAGON
- GHOST

---

## TypeChart

```cpp
float TypeChart[TYPE_COUNT][TYPE_COUNT]
```

Matriz de efetividade utilizada para calcular vantagens e desvantagens entre tipos.

### Exemplo

```text
FIRE → GRASS = 2.0
FIRE → WATER = 0.5
NORMAL → GHOST = 0.0
```

---

## GetEffectiveness

```cpp
float GetEffectiveness(Type atk, Type def)
```

Retorna o multiplicador de efetividade entre um tipo atacante e um tipo defensor.

### Complexidade

```text
O(1)
```

A operação consiste em um acesso direto à matriz.

---

# Classe Move

## Responsabilidade

Representar um golpe disponível para um Pokémon.

---

## Estrutura

### name

Nome do golpe.

Exemplo:

```text
Flamethrower
```

---

### type

Tipo elemental do golpe.

Exemplo:

```text
FIRE
```

---

### category

Categoria do golpe.

Valores possíveis:

```text
PHYSICAL
SPECIAL
STATUS
```

---

### power

Poder base utilizado no cálculo de dano.

---

## Observação

Os golpes são definidos globalmente no arquivo.

Exemplo:

```cpp
static Move Flamethrower(...)
```

Essas instâncias funcionam como um banco de movimentos simplificado para a aplicação.

---

# Classe Pokemon

## Responsabilidade

Representar um Pokémon participante da batalha.

---

## Atributos

### name

Nome do Pokémon.

---

### types

Tipos elementais.

Pode conter:

- um tipo;
- dois tipos.

Exemplo:

```text
[FIRE, FLYING]
```

---

### hp

HP base utilizado para normalização dos danos.

---

### attack

Ataque físico.

---

### defense

Defesa física.

---

### spAttack

Ataque especial.

---

### spDefense

Defesa especial.

---

### speed

Velocidade utilizada para determinar a ordem das ações.

---

### moves

Conjunto de movimentos disponíveis.

O projeto considera até quatro ações por Pokémon.

---

# Algoritmo de Cálculo de Dano

## CalculateDamage

```cpp
int CalculateDamage(...)
```

Calcula o dano percentual causado por um golpe.

---

## Etapas

### 1. Seleção de atributos

Golpes físicos utilizam:

```text
Attack
Defense
```

Golpes especiais utilizam:

```text
SpAttack
SpDefense
```

---

### 2. Cálculo de efetividade

Para cada tipo do defensor:

```text
multiplicador *= efetividade
```

Exemplo:

```text
FIRE → GRASS = 2.0
FIRE → STEEL = 2.0

Resultado = 4.0
```

---

### 3. Aplicação do STAB

STAB (Same Type Attack Bonus).

Se o tipo do golpe pertence ao atacante:

```text
1.5x
```

é aplicado ao dano.

---

### 4. Conversão para porcentagem

O dano bruto é convertido para porcentagem do HP base do alvo.

---

### 5. Discretização

O resultado é arredondado para múltiplos de 10%.

Exemplo:

```text
23% → 30%
41% → 50%
```

---

## Objetivo da Discretização

A discretização reduz significativamente o número de estados possíveis da batalha.

Sem ela, o espaço de estados cresceria rapidamente, tornando a construção completa do grafo inviável para fins acadêmicos.

---

## Complexidade

```text
O(t)
```

Onde:

```text
t = quantidade de tipos do defensor
```

Como um Pokémon possui no máximo dois tipos:

```text
O(1)
```

na prática.

---

# Classe State

## Responsabilidade

Representar um estado específico da batalha.

Cada vértice do grafo contém exatamente um objeto desta classe.

---

## Atributos

### p1

Referência para o Pokémon 1.

---

### p2

Referência para o Pokémon 2.

---

### hp1

HP atual do Pokémon 1.

Representado em porcentagem.

---

### hp2

HP atual do Pokémon 2.

Representado em porcentagem.

---

# Identity

```cpp
std::string Identity() const
```

Gera um identificador único para o estado.

Exemplo:

```text
Charizard_70_Blastoise_40
```

Esse identificador é utilizado como chave da tabela hash do grafo.

---

## Complexidade

```text
O(1)
```

---

# ApplyMove

```cpp
void ApplyMove(...)
```

Executa um golpe ofensivo.

O método:

1. calcula o dano;
2. reduz o HP do alvo;
3. impede valores negativos.

---

## Complexidade

```text
O(1)
```

---

# ApplyRecover

```cpp
void ApplyRecover(...)
```

Executa a ação Recover.

Características:

- restaura 50% de HP;
- respeita o limite máximo de 100%.

---

## Complexidade

```text
O(1)
```

---

# Step

```cpp
State Step(int moveIndex1, int moveIndex2)
```

Método mais importante da classe.

Recebe uma combinação de ações e produz o próximo estado da batalha.

---

## Fluxo

### 1. Seleção dos golpes

Os índices recebidos identificam os movimentos escolhidos.

---

### 2. Determinação da ordem

A velocidade dos Pokémon é comparada.

```text
Maior Speed → age primeiro
```

---

### 3. Execução da ação do primeiro Pokémon

Pode ser:

- ataque;
- Recover.

---

### 4. Execução da ação do segundo Pokémon

Executada somente se o Pokémon ainda estiver vivo.

---

### 5. Retorno do novo estado

O estado original não é alterado.

Um novo objeto é retornado.

---

## Complexidade

```text
O(1)
```

---

# Papel no Projeto

A classe `State` é a ligação entre o domínio Pokémon e a modelagem por grafos.

Cada estado representa um vértice.

Cada chamada de `Step()` representa uma transição entre vértices.

Essa abstração permite que o problema seja tratado como um grafo direcionado explorável por algoritmos clássicos de busca.
