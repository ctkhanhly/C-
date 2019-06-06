#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "Warrior.h"

namespace WarriorCraft{
    class Swordsman : public Warrior{
    public: 
        Swordsman(const std::string& name, int strength);
        void wayOfDefending() const;
    };
}

#endif