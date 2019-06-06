#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <string>

namespace WarriorCraft{
    class Lord;
    class Protector{
        friend std::ostream& operator<<(std::ostream& os, const Protector& protector);
    private:
        std::string name;
        double strength;
        bool isHired;
        bool isDead;
        Lord* lord;
    public:
        Protector(const std::string& name, double strength);
        void setIsHired(bool isHired);
        void setIsDead(bool isDead);
        bool getIsDead() const;
        void setStrength(double strength);
        void runaway();
        void setLord(Lord* lord);
        const std::string& getLordName() const;
        bool getIsHired() const;
        const std::string& getName() const;
        double getStrength() const;
        virtual void wayOfDefending() const = 0;//'wayOfDefending' is not virtual and cannot be declared pure

    };
}

#endif
