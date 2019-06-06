#ifndef WIZARD_H
#define WIZARD_H

#include <string>
#include "Protector.h"

namespace WarriorCraft{
    class Wizard : public Protector{
    public:
        Wizard(const std::string& name, int strength);
        void wayOfDefending() const;
    };
}

#endif