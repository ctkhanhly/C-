#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>

namespace WarriorCraft{
    class Noble{
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble){ return os;}
    private:
        std::string name;
        double strength;
        bool isDead;
    public: 
        Noble(const std::string& name): name(name), strength(0), isDead(false){}
        Noble(const std::string& name, int strength): name(name), strength(strength), isDead(false){}
        void setStrength(double strength);
        void setIsDead(bool isDead);
        bool getIsDead() const;
        double getStrength() const;
        const std::string& getName() const;
        void battle(Noble& noble);
        virtual void wayOfDefending() const = 0;
        virtual void setStrengthWinner(Noble& loser) = 0;
        virtual void setStrengthLoser() = 0;
    };
}
#endif