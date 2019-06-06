#ifndef ARCHER_H
#define ARCHER_H

#include "Warrior.h"

namespace WarriorCraft{
    class Archer : public Warrior{
    public: 
        Archer(const std::string& name, int strength);
        void wayOfDefending() const;
    };
}

#endif