#include "stdafx.h"

#include <vector>
#include "CountBags.h"
#include "Types.h"

using UniqueBags = std::set<int>;

std::vector<int> FindBagsContainingBag(const BagContentMap& bagContentMap, int bagIndex)
{
	std::vector<int> bagIdsOut;
	for (auto bagContentIt : bagContentMap)
	{
		const BagIdCountSet& bagIds = bagContentIt.second;
		for (auto bagIdCount : bagIds)
		{
			if (bagIdCount.bagId == bagIndex)
			{
				bagIdsOut.push_back(bagContentIt.first);
			}
		}
	}
	return bagIdsOut;
}

void FindAndInsertBags(const BagContentMap& bagContentMap, int bagIndex, UniqueBags& uniqueBags)
{
	std::vector<int> bagsHoldingIndex = FindBagsContainingBag(bagContentMap, bagIndex);
	uniqueBags.insert(bagsHoldingIndex.begin(), bagsHoldingIndex.end());
	for (auto bag : bagsHoldingIndex)
	{
		FindAndInsertBags(bagContentMap, bag, uniqueBags);
	}
}

int CountBagsContainingBag(const BagInfo& bagInfo, std::string bagName)
{
	auto bagIdIt = bagInfo.bagIdMap.find(bagName);
	if (bagIdIt != bagInfo.bagIdMap.end())
	{
		UniqueBags uniqueBags;
		int bagColorIndex = bagIdIt->second;
		FindAndInsertBags(bagInfo.bagContentMap, bagColorIndex, uniqueBags);
		return (int)uniqueBags.size();
	}
	return 0;
}

int CountBagsContainedInBagIndex(const BagContentMap& bagContentMap, int bagIndex)
{
	int bagCount = 0;
	auto bagContentIt = bagContentMap.find(bagIndex);
	if (bagContentIt != bagContentMap.end())
	{
		const BagIdCountSet& bagIds = bagContentIt->second;
		for (auto bagId : bagIds)
		{
			bagCount += bagId.bagCount *(1 + CountBagsContainedInBagIndex(bagContentMap, bagId.bagId));
		}
	}
	return bagCount;
}

int CountBagsContainedInBag(const BagInfo& bagInfo, std::string bagName)
{
	auto bagIdIt = bagInfo.bagIdMap.find(bagName);
	if (bagIdIt != bagInfo.bagIdMap.end())
	{
		int bagColorIndex = bagIdIt->second;
		return CountBagsContainedInBagIndex(bagInfo.bagContentMap, bagColorIndex);
	}
	return 0;
}
