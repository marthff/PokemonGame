#pragma once
#include "CombatGraph.h"
#include <set>
#include <iostream>

class MetaAnalyzer {
private:
    bool hasCycleDFS(std::string nodeId, std::unordered_map<std::string, GraphNode*>& map, std::set<std::string>& visited, std::set<std::string>& stack) {
        visited.insert(nodeId);
        stack.insert(nodeId);

        GraphNode* node = map[nodeId];
        if (node->state.hp1 <= 0 || node->state.hp2 <= 0) {
            stack.erase(nodeId);
            return false;
        }

        for (const auto& trans : node->transitions) {
            if (stack.find(trans.nextStateId) != stack.end()) {
                return true; 
            }
            if (visited.find(trans.nextStateId) == visited.end()) {
                if (hasCycleDFS(trans.nextStateId, map, visited, stack))
                    return true;
            }
        }

        stack.erase(nodeId);
        return false;
    }

public:
    int CheckAbsoluteWinner(CombatGraph& cg) {
        std::set<std::string> visited;
        std::queue<std::string> q;
        q.push(cg.rootId);
        visited.insert(cg.rootId);

        bool p1WinsAtLeastOnce = false;
        bool p2WinsAtLeastOnce = false;
        bool drawOrLoopPossible = false;

        while (!q.empty()) {
            std::string currId = q.front();
            q.pop();

            GraphNode* node = cg.graphMap[currId];

            if (node->state.hp1 <= 0 || node->state.hp2 <= 0) {
                if (node->state.hp1 > 0 && node->state.hp2 <= 0) p1WinsAtLeastOnce = true;
                else if (node->state.hp2 > 0 && node->state.hp1 <= 0) p2WinsAtLeastOnce = true;
                else drawOrLoopPossible = true;
                continue;
            }

            if (node->transitions.empty()) {
                drawOrLoopPossible = true;
                continue;
            }

            for (const auto& t : node->transitions) {
                if (visited.find(t.nextStateId) == visited.end()) {
                    visited.insert(t.nextStateId);
                    q.push(t.nextStateId);
                }
            }
        }

        if (p1WinsAtLeastOnce && !p2WinsAtLeastOnce && !drawOrLoopPossible) return 1; 
        if (p2WinsAtLeastOnce && !p1WinsAtLeastOnce && !drawOrLoopPossible) return 2; 
        return 0; 
    }

    bool DetectEndlessBattles(CombatGraph& cg) {
        std::set<std::string> visited;
        std::set<std::string> stack;
        return hasCycleDFS(cg.rootId, cg.graphMap, visited, stack);
    }

    float CalculateWinRateP1(CombatGraph& cg) {
        int p1Leaves = 0;
        int totalLeaves = 0;

        for (auto const& [id, node] : cg.graphMap) {
            if (node->state.hp1 <= 0 || node->state.hp2 <= 0) {
                totalLeaves++;
                if (node->state.hp1 > 0 && node->state.hp2 <= 0) {
                    p1Leaves++;
                }
            }
        }
        if (totalLeaves == 0) return 0.0f;
        return (float)p1Leaves / totalLeaves;
    }

    void PrintSampleBattle(CombatGraph& cg) {
        std::string currentId = cg.rootId;
        int turn = 1;

        std::cout << "\n--------------------------------------------------\n";
        std::cout << "⚔️ SIMULACAO DE COMBATE ATIVA: " << cg.graphMap[currentId]->state.p1->name 
                  << " x " << cg.graphMap[currentId]->state.p2->name << "\n";
        std::cout << "--------------------------------------------------\n";

        while (true) {
            GraphNode* node = cg.graphMap[currentId];
            
            std::cout << "Turno " << turn << ":\n";
            std::cout << "  -> " << node->state.p1->name << " HP: " << node->state.hp1 << "%\n";
            std::cout << "  -> " << node->state.p2->name << " HP: " << node->state.hp2 << "%\n";

            if (node->state.hp1 <= 0 || node->state.hp2 <= 0) {
                std::cout << "\n🏁 FIM DE COMBATE: ";
                if (node->state.hp1 > 0) std::cout << node->state.p1->name << " E O VENCEDOR!\n";
                else if (node->state.hp2 > 0) std::cout << node->state.p2->name << " E O VENCEDOR!\n";
                else std::cout << "COMBATE EMPATADO!\n";
                break;
            }

            if (node->transitions.empty()) break;

            // Escolha padrão simulada: Ambas as IAs executam suas primeiras habilidades indexadas (0,0)
            const Transition* chosenTransition = nullptr;
            for (const auto& t : node->transitions) {
                if (t.moveIdx1 == 0 && t.moveIdx2 == 0) {
                    chosenTransition = &t;
                    break;
                }
            }

            if (!chosenTransition) chosenTransition = &node->transitions[0];

            std::cout << "  💥 " << node->state.p1->name << " desferiu: " << node->state.p1->moves[chosenTransition->moveIdx1].name << "\n";
            std::cout << "  💥 " << node->state.p2->name << " desferiu: " << node->state.p2->moves[chosenTransition->moveIdx2].name << "\n";
            std::cout << "--------------------------------------------------\n";

            currentId = chosenTransition->nextStateId;
            turn++;

            if (turn > 15) {
                std::cout << "🔄 [CICLO RECURSIVO] Travamento de loop por regeneracao consecutiva (Recover)!\n";
                break;
            }
        }
    }
};