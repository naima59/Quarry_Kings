#include "upgrades.h"

Upgrades::Resource Upgrades::resourceTypes(std::string upgradeName)
{
    if (upgradeName == "pickAxeQuality")
    {
        return {"pickAxeQuality", 10, 0, 1};  
    }
    throw std::runtime_error("Unknown resource: " + upgradeName);
}

void Upgrades::resourceManager(float& stoneCount, Resource& resourceType)
{
    if (stoneCount >= resourceType.amount)
    {
        stoneCount -= resourceType.amount;
        resourceType.level += 1;
        resourceType.amount *= 1.5;
        resourceType.perSecond += .0025;
        
        char logMessage[128];
        sprintf(logMessage, "Resource Level: %d  | Resource Amount: %.2f | Stone Per Scond: %.4f", resourceType.level, resourceType.amount, resourceType.perSecond);
        TraceLog(LOG_INFO, "%s", logMessage);
    }
};