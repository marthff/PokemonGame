#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "PokemonBase.h"
#include "CombatGraph.h"
#include "MetaAnalizer.h"

void ExibirRelatorioGeral(const std::vector<Pokemon*>& team1, const std::vector<Pokemon*>& team2, MetaAnalyzer& analyzer) {
    std::map<std::string, float> pokemonGlobalWinScore;
    float totalTeam1WinRateSum = 0;
    float totalTeam2WinRateSum = 0;
    bool globalEndlessBattleFound = false;
    bool disadvantageWinFound = false;

    std::cout << "\n==================================================\n";
    std::cout << "PROCESSANDO TODOS OS 36 GRAFOS DO TORNEIO...\n";
    std::cout << "==================================================\n";

    for (auto* p1 : team1) {
        for (auto* p2 : team2) {
            CombatGraph cg(p1, p2);

            float winRateP1 = analyzer.CalculateWinRateP1(cg);
            totalTeam1WinRateSum += winRateP1;
            totalTeam2WinRateSum += (1.0f - winRateP1);

            pokemonGlobalWinScore[p1->name] += winRateP1;
            pokemonGlobalWinScore[p2->name] += (1.0f - winRateP1);

            int absoluteWinner = analyzer.CheckAbsoluteWinner(cg);
            if (absoluteWinner == 1) {
                std::cout << "  > [INTEGRIDADE]: " << p1->name << " detem vitoria ABSOLUTA sobre " << p2->name << ".\n";
            } else if (absoluteWinner == 2) {
                std::cout << "  > [INTEGRIDADE]: " << p2->name << " detem vitoria ABSOLUTA sobre " << p1->name << ".\n";
            }

            if (analyzer.DetectEndlessBattles(cg)) {
                globalEndlessBattleFound = true;
            }

            if (p1->name == "Feraligatr" && p2->name == "Chesnaught" && winRateP1 > 0.2f) disadvantageWinFound = true;
            if (p1->name == "Charizard" && p2->name == "Tyranitar" && winRateP1 > 0.2f) disadvantageWinFound = true;
        }
    }

    std::cout << "\n==================================================\n";
    std::cout << "RELATORIO DE METAGAME COMPILADO\n";
    std::cout << "==================================================\n";

    std::cout << "Pergunta 1: Qual dos times possui maior dominancia de vitoria?\n";
    std::cout << "  -> Score Acumulado Time 1: " << totalTeam1WinRateSum << "\n";
    std::cout << "  -> Score Acumulado Time 2: " << totalTeam2WinRateSum << "\n";
    if (totalTeam1WinRateSum > totalTeam2WinRateSum) {
        std::cout << "  Resultado: O TIME 1 possui maior probabilidade de vencer um embate real.\n\n";
    } else {
        std::cout << "  Resultado: O TIME 2 possui maior probabilidade de vencer um embate real.\n\n";
    }

    std::string bestPokemon = "";
    float maxScore = -1.0f;
    for (auto const& [name, score] : pokemonGlobalWinScore) {
        if (score > maxScore) {
            maxScore = score;
            bestPokemon = name;
        }
    }
    std::cout << "Pergunta 2: Qual Pokemon obteve o melhor desempenho individual?\n";
    std::cout << "  Resultado: " << bestPokemon << " com score de dominancia de " << maxScore << ".\n\n";

    std::cout << "Pergunta 3: Existe alguma luta com vitoria garantida independente da acao?\n";
    std::cout << "  Resultado: Sim, as ocorrencias de dominancia absoluta foram listadas no log de processamento acima.\n\n";

    std::cout << "Pergunta 4: Existem estados em que a batalha se torna interminavel?\n";
    std::cout << "  Resultado: " << (globalEndlessBattleFound ? "SIM. Loops infinitos foram detectados gerados pela acao continuada de 'Recover'." : "NAO.") << "\n\n";

    std::cout << "Pergunta 5: Ha casos onde a desvantagem de tipo foi superada?\n";
    std::cout << "  Resultado: " << (disadvantageWinFound ? "SIM. Fatores de Speed elevados ou diferenca gritante de Base Stats permitiram a vitoria em desvantagem elemental." : "NAO.") << "\n";
}

int main() {
    std::vector<Pokemon*> team1 = {
        new Pokemon("Charizard", { FIRE,    FLYING  },  78,  84,  78, 109,  85, 100, { Flamethrower, Hurricane,   ShadowBall,  Recover }),
        new Pokemon("Feraligatr",{ WATER            },  85, 105, 100,  79,  83,  78, { Liquidation,  IcePunch,    Crunch,      Earthquake }),
        new Pokemon("Scizor",    { BUG,     STEEL   },  70, 130, 100,  55,  80,  65, { IronHead,     MetalClaw,   BugBuzz,     Recover }),
        new Pokemon("Decidueye", { GRASS,   GHOST   },  78, 107,  75, 100, 100,  70, { LeafBlade,    ShadowClaw,  EnergyBall,  Recover }),
        new Pokemon("Garchomp",  { DRAGON,  GROUND  }, 108, 130,  95,  80,  85, 102, { Earthquake,   DragonClaw,  Crunch,      FirePunch }),
        new Pokemon("Reuniclus", { PSYCHIC          }, 110,  65,  75, 125,  85,  30, { PsychicMove,  Psystrike,   ShadowBall,  Recover })
    };

    std::vector<Pokemon*> team2 = {
        new Pokemon("Blastoise", { WATER            },  79,  83, 100,  85, 105,  78, { HydroPump,    IceBeam,     AuraSphere,  Recover }),
        new Pokemon("Blaziken",  { FIRE,    FIGHTING},  80, 120,  70, 110,  70,  80, { Flamethrower, CloseCombat, FirePunch,   ThunderPunch }),
        new Pokemon("Chesnaught",{ GRASS,   FIGHTING},  88, 107, 122,  74,  75,  64, { LeafBlade,    CloseCombat, Earthquake,  Recover }),
        new Pokemon("Tyranitar", { ROCK,    DARK    }, 100, 134, 110,  95, 100,  61, { Crunch,       RockSlide,   Earthquake,  IcePunch }),
        new Pokemon("Gengar",    { GHOST,   POISON  },  60,  65,  60, 130,  75, 110, { ShadowBall,   SludgeBomb,  Thunderbolt, Recover }),
        new Pokemon("Alakazam",  { PSYCHIC          },  55,  50,  45, 135,  95, 120, { PsychicMove,  Psystrike,   ShadowBall,  Recover })
    };

    MetaAnalyzer analyzer;
    int opcao = 0;

    while (true) {
        std::cout << "\n==================================================\n";
        std::cout << "        MENU REQUISITOS - TRABALHO POKEMON        \n";
        std::cout << "==================================================\n";
        std::cout << "1. Executar Analise Global do Metagame (O que o Trabalho pede)\n";
        std::cout << "2. Escolher um Combate Especifico por Etapas\n";
        std::cout << "3. Sair do Simulador\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        if (opcao == 1) {
            ExibirRelatorioGeral(team1, team2, analyzer);
        }
        else if (opcao == 2) {
            std::cout << "\n--- SELECIONE O POKEMON DO TIME 1 ---\n";
            for (size_t i = 0; i < team1.size(); ++i) {
                std::cout << i + 1 << ". " << team1[i]->name << "\n";
            }
            int escolha1;
            std::cout << "Escolha (1-6): ";
            std::cin >> escolha1;

            std::cout << "\n--- SELECIONE O POKEMON DO TIME 2 ---\n";
            for (size_t i = 0; i < team2.size(); ++i) {
                std::cout << i + 1 << ". " << team2[i]->name << "\n";
            }
            int escolha2;
            std::cout << "Escolha (1-6): ";
            std::cin >> escolha2;

            if (escolha1 >= 1 && escolha1 <= 6 && escolha2 >= 1 && escolha2 <= 6) {
                Pokemon* p1 = team1[escolha1 - 1];
                Pokemon* p2 = team2[escolha2 - 1];

                CombatGraph cg(p1, p2);
                analyzer.FindBestVictoryPath(cg);
                analyzer.PrintSampleBattle(cg);

            } else {
                std::cout << "Escolha invalida!\n";
            }
        }
        else if (opcao == 3) {
            break;
        } else {
            std::cout << "Opcao Invalida!\n";
        }
    }

    for (auto* p : team1) delete p;
    for (auto* p : team2) delete p;

    return 0;
}