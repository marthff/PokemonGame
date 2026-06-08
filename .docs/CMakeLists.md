# CMakeLists

## Visão Geral

O arquivo `CMakeLists.txt` define como o projeto deve ser compilado utilizando o sistema de build CMake.

Seu objetivo é centralizar as configurações de compilação e permitir que diferentes ambientes gerem executáveis de forma padronizada.

## Configuração Mínima

```cmake
cmake_minimum_required(...)
```

Define a versão mínima do CMake necessária para processar o projeto.

## Nome do Projeto

```cmake
project(PokemonGame)
```

Registra o nome do projeto dentro do ambiente de build.

Esse nome também é utilizado como base para o executável gerado.

## Padrão da Linguagem

```cmake
set(CMAKE_CXX_STANDARD 14)
```

Define que o código deve ser compilado utilizando recursos do padrão C++14.

## Diretórios de Inclusão

```cmake
include_directories(.)
```

Permite que os arquivos de cabeçalho localizados na raiz do projeto sejam encontrados durante a compilação.

## Geração do Executável

```cmake
add_executable(...)
```

Define o executável principal do projeto.

Durante a compilação, o CMake utilizará os arquivos especificados para produzir o programa final.

## Papel na Arquitetura

O CMake não participa da lógica de batalha ou da modelagem dos grafos.

Sua função é exclusivamente relacionada ao processo de construção do software.
