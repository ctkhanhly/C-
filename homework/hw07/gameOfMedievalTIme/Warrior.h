#ifndef WARRIOR_H
#define WARRIOR_H

#include "Protector.h"
namespace WarriorCraft{
    class Warrior : public Protector{
    public:
        Warrior(const std::string& name, int strength);
    };
}

#endif