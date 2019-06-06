#ifndef PERSONWITHSTRENGTHTOFIGHT_H
#define PERSONWITHSTRENGTHTOFIGHT_H

#include <string>
#include "Noble.h"

namespace WarriorCraft{
    class PersonWithStrengthToFight : public Noble{
    public: 
        PersonWithStrengthToFight(const std::string& name, int strength);
        void setStrengthLoser();
        void wayOfDefending() const;
        void setStrengthWinner(Noble& loser);
    };
}

#endif
