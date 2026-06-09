#pragma once
#include "CombatGraph.h"
#include <set>
#include <fstream>
#include <unordered_map>
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

    struct PathNode {
    std::string stateId;
    int damageTaken;

    bool operator>(const PathNode& other) const {
        return damageTaken > other.damageTaken;
    }
    };


    void FindBestVictoryPath(CombatGraph& cg) {

        std::unordered_map<std::string, int> minDamage;
        std::unordered_map<std::string, std::pair<std::string, std::string>> parent;

        std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode>> pq;

        pq.push({cg.rootId, 0});
        minDamage[cg.rootId] = 0;
        std::string finalWinningState = "";
        int bestFinalDamage = 999999;

        while (!pq.empty()) {
            PathNode current = pq.top();
            pq.pop();

            if (current.damageTaken > minDamage[current.stateId]) continue;

            GraphNode* node = cg.graphMap[current.stateId];

            if (node->state.hp1 > 0 && node->state.hp2 <= 0) {
                if (current.damageTaken < bestFinalDamage) {
                    bestFinalDamage = current.damageTaken;
                    finalWinningState = current.stateId;
                }
                continue;
            }

            for (const auto& transition : node->transitions) {
                GraphNode* nextNode = cg.graphMap[transition.nextStateId];

                int damageInStep = node->state.hp1 - nextNode->state.hp1;
                int totalDamage = current.damageTaken + std::max(0, damageInStep);

                if (minDamage.find(transition.nextStateId) == minDamage.end() || totalDamage < minDamage[transition.nextStateId]) {
                    minDamage[transition.nextStateId] = totalDamage;

                    std::string moveDesc = node->state.p1->moves[transition.moveIdx1].name;
                    parent[transition.nextStateId] = {current.stateId, moveDesc};

                    pq.push({transition.nextStateId, totalDamage});
                }
            }
        }

        if (finalWinningState != "") {
            std::cout << "\n--- ESTRATEGIA OTIRIMIZADA (MIN-HEAP) ---\n";
            std::cout << "Objetivo: Vencer sofrendo o minimo de dano.\n";

            std::vector<std::string> path;
            std::string curr = finalWinningState;
            while (curr != cg.rootId) {
                path.push_back("Use " + parent[curr].second + " -> Estado: " + curr);
                curr = parent[curr].first;
            }

            for (int i = path.size() - 1; i >= 0; i--) {
                std::cout << "Passo " << path.size() - i << ": " << path[i] << std::endl;
            }
            std::cout << "Dano total acumulado: " << bestFinalDamage << "%\n";
        } else {
            std::cout << "Nao foi encontrado um caminho de vitoria garantida para este combate.\n";
        }
    }


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

        std::ofstream logFile("dados.js");

        std::cout << "\n--------------------------------------------------\n";
        std::cout << "BATTLE SIMULATION: " << cg.graphMap[currentId]->state.p1->name
                  << " x " << cg.graphMap[currentId]->state.p2->name << "\n";
        std::cout << "--------------------------------------------------\n";

        if (logFile.is_open()) {
            logFile << "const dadosBatalha = [\n";
        }

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

                if (logFile.is_open()) {
                    logFile << "  [\"" << node->state.p1->name << "\", " << node->state.hp1 << ", \""
                            << node->state.p2->name << "\", " << node->state.hp2 << ", \"FIM\", \"FIM\"]\n";
                }
                break;
            }

            if (node->transitions.empty()) break;

            const Transition* chosenTransition = nullptr;
            for (const auto& t : node->transitions) {
                if (t.moveIdx1 == 0 && t.moveIdx2 == 0) {
                    chosenTransition = &t;
                    break;
                }
            }

            if (!chosenTransition) chosenTransition = &node->transitions[0];

            std::string nomeGolpeP1 = node->state.p1->moves[chosenTransition->moveIdx1].name;
            std::string nomeGolpeP2 = node->state.p2->moves[chosenTransition->moveIdx2].name;

            std::cout << node->state.p1->name << " desferiu: " << nomeGolpeP1 << "\n";
            std::cout << node->state.p2->name << " desferiu: " << nomeGolpeP2 << "\n";
            std::cout << "--------------------------------------------------\n";

            if (logFile.is_open()) {
                logFile << "  [\"" << node->state.p1->name << "\", " << node->state.hp1 << ", \""
                        << node->state.p2->name << "\", " << node->state.hp2 << ", \""
                        << nomeGolpeP1 << "\", \"" << nomeGolpeP2 << "\"],\n";
            }

            currentId = chosenTransition->nextStateId;
            turn++;

            if (turn > 15) {
                std::cout << "🔄 [CICLO RECURSIVO] Travamento de loop por regeneracao consecutiva (Recover)!\n";
                if (logFile.is_open()) {
                    logFile << "  [\"" << node->state.p1->name << "\", " << node->state.hp1 << ", \""
                            << node->state.p2->name << "\", " << node->state.hp2 << ", \"LOOP\", \"LOOP\"]\n";
                }
                break;
            }
        }

        if (logFile.is_open()) {
            logFile << "];\n";
            logFile.close();
        }
    }

};