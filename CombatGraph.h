#pragma once

#include "PokemonBase.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

struct Transition {
    int moveIdx1;
    int moveIdx2;
    std::string nextStateId;
};

struct GraphNode {
    State state;
    std::vector<Transition> transitions;
};

class CombatGraph {
public:
    std::unordered_map<std::string, GraphNode*> graphMap; 
    std::string rootId;

    CombatGraph(Pokemon* p1, Pokemon* p2) {
        State initialState(p1, p2);
        rootId = initialState.Identity();
        BuildGraph(initialState);
    }

    ~CombatGraph() {
        for (auto& pair : graphMap) {
            delete pair.second;
        }
    }

private:
    void BuildGraph(State startState) {
        std::queue<State> toProcess;
        toProcess.push(startState);

        GraphNode* rootNode = new GraphNode{startState, {}};
        graphMap[startState.Identity()] = rootNode;

        while (!toProcess.empty()) {
            State current = toProcess.front();
            toProcess.pop();

            std::string currId = current.Identity();
            GraphNode* currNode = graphMap[currId];

            if (current.hp1 <= 0 || current.hp2 <= 0) {
                continue;
            }

            for (size_t i = 0; i < current.p1->moves.size(); ++i) {
                for (size_t j = 0; j < current.p2->moves.size(); ++j) {
                    
                    State nextState = current.Step(i, j);
                    std::string nextId = nextState.Identity();

                    // Reutiliza estados idênticos através da Hash 
                    if (graphMap.find(nextId) == graphMap.end()) {
                        GraphNode* newNode = new GraphNode{nextState, {}};
                        graphMap[nextId] = newNode;
                        toProcess.push(nextState);
                    }

                    currNode->transitions.push_back({(int)i, (int)j, nextId});
                }
            }
        }
    }
};