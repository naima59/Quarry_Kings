#include "upgrades.h"

Upgrades::Resource Upgrades::resourceTypes(std::string upgradeName)
{
    if (upgradeName == "pickaxeQuality")
    {
        return {"pickaxeQuality", 1, 0, 10, 1.8, 1.12, 10, 0};  
    }

    if (upgradeName == "villager")
    {
        return {"villager", 1, .01, 50,1.5, 1.12, 50, 0};
    }

    if (upgradeName == "oxen")
    {
        return {"oxen", 1, .05, 1000,1.15, 1.15, 800, 0};
    }

    throw std::runtime_error("Unknown resource: " + upgradeName);
}

void Upgrades::resourceManager(float& stoneCount, Resource& resourceType)
{

    if(resourceType.level == 0 && stoneCount >= resourceType.baseCost)
    {
        stoneCount -= resourceType.baseCost;
        resourceType.level++;
        resourceType.amount++;
        resourceType.totalCost = resourceType.baseCost * pow(resourceType.costScale, resourceType.level);
        globalPerSecond += resourceType.perSecond;
    }
    else if(resourceType.level != 0 && stoneCount >= resourceType.totalCost)
    {
        stoneCount -= resourceType.totalCost;
        resourceType.level++;
        resourceType.amount++;
        resourceType.perSecond = resourceType.perSecond * pow(resourceType.rateScale, resourceType.level);
        resourceType.totalCost = resourceType.baseCost * pow(resourceType.costScale, resourceType.level);
        globalPerSecond += resourceType.perSecond;
    }

};