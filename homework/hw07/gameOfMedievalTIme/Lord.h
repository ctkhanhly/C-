#ifndef LORD_H
#define LORD_H

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"

namespace WarriorCraft{
    class Protector;
    class Noble;
    class Lord : public Noble{
    private:
        std::vector<Protector*> armyOfProtectors;
        size_t lookForProtector(Protector& protector) const;   
    public:
        Lord(const std::string& name);
        bool hires(Protector& protector);
        bool fires(Protector& protector);
        bool deleteProtector(Protector& protector);
        void setStrengthLoser();
        void setStrengthWinner(Noble& loser);
        void wayOfDefending() const;
    };
}

#endif