#ifndef UPGRADES_H
#define UPGRADES_H
#include "raylib.h"
#include "resource_dir.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>


class Upgrades
{
public:
    struct Resource {
    std::string id;
    int perSecond = 0;
    int baseCost = 0;
    int totalCost = 0;
    int level = 1;};
    Resource ResourceTypes(std::string upgradeName);
    void ResourceManager(float& stoneCount, Resource& resourceType);
    int globalPerSecond = 0;
    float costScale = 1.15f;
};


#endif