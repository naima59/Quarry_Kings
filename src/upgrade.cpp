#include "upgrades.h"

Upgrades::Resource Upgrades::ResourceTypes(std::string upgradeName)
{
    if (upgradeName == "pickaxeQuality")
    {
        return {"pickaxeQuality", 1, 10, 10, 0};  
    }

    if (upgradeName == "villager")
    {
        return {"villager", 5, 50, 50, 0};
    }

    if (upgradeName == "cart")
    {
        return {"cart", 50, 500,500, 0};
    }    

    if (upgradeName == "oxen")
    {
        return {"oxen", 500, 5000,5000, 0};
    }

    throw std::runtime_error("Unknown resource: " + upgradeName);
}

void Upgrades::ResourceManager(float& stoneCount, Resource& resourceType)
{

    if(resourceType.level == 1 && stoneCount >= resourceType.baseCost)
    {
        stoneCount -= resourceType.baseCost;
        resourceType.level++;
        resourceType.totalCost = resourceType.baseCost * pow(costScale, resourceType.level);
        globalPerSecond += resourceType.perSecond;
    }
    else if(resourceType.level != 1 && stoneCount >= resourceType.totalCost)
    {
        stoneCount -= resourceType.totalCost;
        resourceType.level++;
        resourceType.totalCost =  resourceType.baseCost * pow(costScale, resourceType.level);
        globalPerSecond += resourceType.perSecond;
    }

};