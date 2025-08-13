#ifndef UPGRADES_H
#define UPGRADES_H
#include <string>
#include <stdexcept>
#include <iostream>
#include "raylib.h"
#include <cmath>

class Upgrades
{
public:
    struct Resource {
    std::string id;
    double amount = 0.0; 
    double perSecond = 0.0;
    int baseCost = 0;
    float costScale = 0.0;
    float rateScale = 0.0;
    int totalCost = 0;
    int level = 0;};
    Resource resourceTypes(std::string upgradeName);
    void resourceManager(float& stoneCount, Resource& resourceType);
    float globalPerSecond = 0.f;
};


#endif