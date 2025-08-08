#ifndef UPGRADES_H
#define UPGRADES_H
#include <string>
#include <cmath>

class Upgrades
{
public:
    struct Upgrade 
    {
    std::string name;
    int level;
    float baseCost;
    float costMultiplier;
    float effectPerLevel;
    bool unlocked;

    float GetCurrentCost() const 
    {
        return baseCost * std::pow(costMultiplier, level);
    }

    float GetEffect() const 
    {
        return level * effectPerLevel;
    }
    };
};
#endif