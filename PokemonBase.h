#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

enum Type {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS, ICE, FIGHTING, POISON, GROUND, FLYING, 
    PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY, TYPE_COUNT
};
enum Category { PHYSICAL, SPECIAL, STATUS };

static float TypeChart[TYPE_COUNT][TYPE_COUNT] = {
    // DEFENDER →
    // NOR FIR WAT ELE GRA ICE FIG POI GRO FLY PSY BUG ROC GHO DRA DAR STE FAI
    /* NORMAL  */ {1,1,1,1,1,1,1,1,1,1,1,1,0.5f,0,1,1,0.5f,1},
    /* FIRE    */ {1,0.5f,0.5f,1,2,2,1,1,1,1,1,2,0.5f,1,0.5f,1,2,1},
    /* WATER   */ {1,2,0.5f,1,0.5f,1,1,1,2,1,1,1,2,1,0.5f,1,1,1},
    /* ELECTRIC*/ {1,1,2,0.5f,0.5f,1,1,1,0,2,1,1,1,1,0.5f,1,1,1},
    /* GRASS   */ {1,0.5f,2,1,0.5f,1,1,0.5f,2,0.5f,1,0.5f,2,1,0.5f,1,0.5f,1},
    /* ICE     */ {1,0.5f,0.5f,1,2,0.5f,1,1,2,2,1,1,1,1,2,1,0.5f,1},
    /* FIGHTING*/ {2,1,1,1,1,2,1,0.5f,1,0.5f,0.5f,0.5f,2,0,1,2,2,0.5f},
    /* POISON  */ {1,1,1,1,2,1,1,0.5f,0.5f,1,1,1,0.5f,0.5f,1,1,0,2},
    /* GROUND  */ {1,2,1,2,0.5f,1,1,2,1,0,1,0.5f,2,1,1,1,2,1},
    /* FLYING  */ {1,1,1,0.5f,2,1,2,1,1,1,1,2,0.5f,1,1,1,0.5f,1},
    /* PSYCHIC */ {1,1,1,1,1,1,2,2,1,1,0.5f,1,1,1,1,0,0.5f,1},
    /* BUG     */ {1,0.5f,1,1,2,1,0.5f,0.5f,1,0.5f,2,1,1,0.5f,1,2,0.5f,0.5f},
    /* ROCK    */ {1,2,1,1,1,2,0.5f,1,0.5f,2,1,2,1,1,1,1,0.5f,1},
    /* GHOST   */ {0,1,1,1,1,1,1,1,1,1,2,1,1,2,1,0.5f,1,1},
    /* DRAGON  */ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,0.5f,0},
    /* DARK    */ {1,1,1,1,1,1,0.5f,1,1,1,2,1,1,2,1,0.5f,1,0.5f},
    /* STEEL   */ {1,0.5f,0.5f,0.5f,1,2,1,1,1,1,1,1,2,1,1,1,0.5f,2},
    /* FAIRY   */ {1,0.5f,1,1,1,1,2,0.5f,1,1,1,1,1,1,2,2,0.5f,1}
};

inline float GetEffectiveness(Type atk, Type def) {
    return TypeChart[(int)atk][(int)def];
}

class Move {
public:
    std::string name;
    Type type;
    Category category;
    int power;

    Move(std::string name, Type type, Category category, int power) {
        this->name = name;
        this->type = type;
        this->category = category;
        this->power = power;
    }
};

// Banco de movimentos globais
static Move Recover        ("Recover",      NORMAL,   STATUS,    0); // [cite: 12]
static Move BodySlam       ("Body Slam",    NORMAL,   PHYSICAL, 85);
static Move Boomburst      ("Boomburst",    NORMAL,   SPECIAL,  140);
static Move FirePunch      ("Fire Punch",   FIRE,     PHYSICAL, 75);
static Move Flamethrower   ("Flamethrower", FIRE,     SPECIAL,  90);
static Move Liquidation    ("Liquidation",  WATER,    PHYSICAL, 85);
static Move HydroPump      ("Hydro Pump",   WATER,    SPECIAL,  110);
static Move ThunderPunch   ("Thunder Punch",ELECTRIC, PHYSICAL, 75);
static Move Thunderbolt    ("Thunderbolt",  ELECTRIC, SPECIAL,  90);
static Move LeafBlade      ("Leaf Blade",   GRASS,    PHYSICAL, 90);
static Move EnergyBall     ("Energy Ball",  GRASS,    SPECIAL,  90);
static Move IcePunch       ("Ice Punch",    ICE,      PHYSICAL, 75);
static Move IceBeam        ("Ice Beam",     ICE,      SPECIAL,  90);
static Move CloseCombat    ("Close Combat", FIGHTING, PHYSICAL, 120);
static Move AuraSphere     ("Aura Sphere",  FIGHTING, SPECIAL,  80);
static Move PoisonJab      ("Poison Jab",   POISON,   PHYSICAL, 80);
static Move SludgeBomb     ("Sludge Bomb",  POISON,   SPECIAL,  90);
static Move Earthquake     ("Earthquake",   GROUND,   PHYSICAL, 100);
static Move MudSlap        ("Mud-Slap",     GROUND,   SPECIAL,  20);
static Move DrillPeck      ("Drill Peck",   FLYING,   PHYSICAL, 80);
static Move Hurricane      ("Hurricane",    FLYING,   SPECIAL,  110);
static Move PsychicMove    ("Psychic",      PSYCHIC,  SPECIAL,  90);
static Move Psystrike      ("Psystrike",    PSYCHIC,  SPECIAL,  100);
static Move Megahorn       ("Megahorn",     BUG,      PHYSICAL, 120);
static Move BugBuzz        ("Bug Buzz",     BUG,      SPECIAL,  90);
static Move RockSlide      ("Rock Slide",   ROCK,     PHYSICAL, 75);
static Move AncientPower   ("Ancient Power",ROCK,     SPECIAL,  60);
static Move ShadowClaw     ("Shadow Claw",  GHOST,    PHYSICAL, 70);
static Move ShadowBall     ("Shadow Ball",  GHOST,    SPECIAL,  80);
static Move DragonClaw     ("Dragon Claw",  DRAGON,   PHYSICAL, 80);
static Move DracoMeteor    ("Draco Meteor", DRAGON,   SPECIAL,  130);
static Move Crunch         ("Crunch",       DARK,     PHYSICAL, 80);
static Move DarkPulse      ("Dark Pulse",   DARK,     SPECIAL,  80);
static Move MetalClaw      ("Metal Claw",   STEEL,    PHYSICAL, 50);
static Move IronHead       ("Iron Head",    STEEL,    PHYSICAL, 80);
static Move PlayRough      ("Play Rough",   FAIRY,    PHYSICAL, 90);
static Move DazzlingGleam  ("Dazzling Gleam",FAIRY,   SPECIAL,  80);

class Pokemon {
public:
    std::string name;
    std::vector<Type> types;
    int hp;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;
    std::vector<Move> moves;

    Pokemon(std::string name, std::vector<Type> types, int hp, int attack, int defense, int spAttack, int spDefense, int speed, std::vector<Move> moves) {
        this->name = name;
        this->types = types;
        this->hp = hp;
        this->attack = attack;
        this->defense = defense;
        this->spAttack = spAttack;
        this->spDefense = spDefense;
        this->speed = speed;
        this->moves = moves; // Máximo 4 ações [cite: 13]
    }
};

inline int CalculateDamage(Pokemon& attacker, Pokemon& defender, Move& move) {
    if (move.category == STATUS)
        return 0;

    float atkStat = (move.category == PHYSICAL) ? attacker.attack  : attacker.spAttack;
    float defStat = (move.category == PHYSICAL) ? defender.defense : defender.spDefense;
    
    float effectiveness = 1.0f;
    for (Type t : defender.types)    
        effectiveness *= GetEffectiveness(move.type, t);

    float stab = 1.0f;
    for (Type t : attacker.types) {
        if (t == move.type) {
            stab = 1.5f;
            break;
        }
    }

    float damage  = (((22.0f * move.power * (atkStat / defStat)) / 50.0f) + 2.0f) * stab * effectiveness;
    float percent = (damage / defender.hp) * 100.0f;
    int rounded   = (int)std::ceil(percent / 10.0f) * 10; // Discretização de 10% arredondada para cima 

    return std::max(10, rounded);
}

class State {
public:
    Pokemon* p1; int hp1;
    Pokemon* p2; int hp2;

    State() : p1(nullptr), p2(nullptr), hp1(100), hp2(100) {}
    State(Pokemon* p1, Pokemon* p2) {
        this->p1 = p1;
        this->p2 = p2;
        hp1 = 100;
        hp2 = 100;
    }
    State(Pokemon* p1, Pokemon* p2, int hp1, int hp2) {
        this->p1 = p1;
        this->p2 = p2;
        this->hp1 = hp1;
        this->hp2 = hp2;
    }

    std::string Identity() const {
        return p1->name + "_" + std::to_string(hp1) + "_" + p2->name + "_" + std::to_string(hp2);
    }

    void ApplyMove(Pokemon* attacker, Pokemon* defender, int& attackerHP, int& defenderHP, Move& move) {
        if (attackerHP <= 0 || defenderHP <= 0) return;
        int damage = CalculateDamage(*attacker, *defender, move);
        defenderHP = std::max(0, defenderHP - damage);
    }

    void ApplyRecover(int& attackerHP, int& defenderHP) {
        if (attackerHP <= 0 || defenderHP <= 0) return;
        attackerHP = std::min(100, attackerHP + 50); // Cura 50% [cite: 12]
    }

    State Step(int moveIndex1, int moveIndex2) {
        State next = *this;
        Move move1 = p1->moves[moveIndex1];
        Move move2 = p2->moves[moveIndex2];

        bool p1First = p1->speed >= p2->speed; // Critério de velocidade básico 

        if (p1First) {
            if (move1.name == "Recover") ApplyRecover(next.hp1, next.hp2);
            else                         ApplyMove(p1, p2, next.hp1, next.hp2, move1);

            if (move2.name == "Recover") ApplyRecover(next.hp2, next.hp1);
            else                         ApplyMove(p2, p1, next.hp2, next.hp1, move2);
        } else {
            if (move2.name == "Recover") ApplyRecover(next.hp2, next.hp1);
            else                         ApplyMove(p2, p1, next.hp2, next.hp1, move2);

            if (move1.name == "Recover") ApplyRecover(next.hp1, next.hp2);
            else                         ApplyMove(p1, p2, next.hp1, next.hp2, move1);
        }
        return next;
    }
};