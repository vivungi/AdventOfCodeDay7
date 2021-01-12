#include "stdafx.h"
#include <sstream> 
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "ParseInputFile.h"
#include "Types.h"

struct BagContentTempInfo
{
	std::string bagIdString;
	int bagCount;
};

using BagContentMapTemp = std::unordered_map <int, std::vector<BagContentTempInfo>>;

//Inserts names of contained bags
void FillBagContentVec(std::string& line, std::vector<BagContentTempInfo>& bagContentNames)
{
	std::string::size_type ind = line.find("contain");
	ind += 6;
	if (line.substr(ind + 2, 2) == "no") //Empty bags are descried with contain no
	{
		return;
	}

	std::vector<std::string> bagContainNames;
	while (ind < line.size())
	{
		ind += 4;
		//Bag container information is followed by "," or "."(if last item)
		std::string::size_type nextInd = line.find(",", ind);
		if (nextInd > line.size())
		{
			nextInd = line.find(".", ind);
		}

		if (nextInd < line.size())
		{
			int offset = line.substr(nextInd - 1, 1) == "s" ? 5 : 4; //one additional offset when multiple bags
			int bagCount = 0;
			try
			{
				bagCount = std::stoi(line.substr(ind - 2, 1));
			}
			catch (std::exception e)
			{
				std::cout << "Invalid number of bags";
			}
			int stringSize = nextInd - offset - ind;
			bagContentNames.push_back({ line.substr(ind, stringSize), bagCount});
		}
		ind = nextInd;
	}
}

void FillBagIdMap(std::ifstream& inputFileStream, BagIdMap& bagIdMap, BagContentMapTemp& bagContainMapTemp)
{
	std::string line;
	int bagId = 0;
	while (std::getline(inputFileStream, line))
	{
		/*
		Input file structure is
		posh brown bags contain 1 dark lime bag, 5 mirrored crimson bags, 1 striped chartreuse bag.
		dull white bags contain no other bags.
		*/
		std::string::size_type ind = line.find("bags");
		if (ind > 0 && ind <line.size())
		{
			//Find name of the bag type;
			std::string bagName = line.substr(0, ind - 1);
			bagIdMap.insert({ bagName, bagId });
			FillBagContentVec(line, bagContainMapTemp[bagId]);
			bagId++;
		}
	}
}

//Fill integer map with contained bags
void FillBagContentMap(BagInfo& bagInfo, const BagContentMapTemp& bagContainMapTemp)
{
	for (auto tempMap : bagContainMapTemp)
	{
		BagIdCountSet bagContainInd;
		for (auto containNames : tempMap.second)
		{
			auto containIndexIt = bagInfo.bagIdMap.find(containNames.bagIdString);
			if (containIndexIt != bagInfo.bagIdMap.end())
			{
				bagContainInd.insert({ containIndexIt->second, containNames.bagCount});
			}
		}
		if (bagContainInd.size())
		{
			bagInfo.bagContentMap[tempMap.first] = bagContainInd;
		}
	}
}

void ParseInputFile(std::string input, BagInfo& bagInfo)
{
	std::ifstream inputFileStream(input);
	BagContentMapTemp bagContainMapTemp;
	if (inputFileStream.is_open())
	{
		FillBagIdMap(inputFileStream, bagInfo.bagIdMap, bagContainMapTemp);
		FillBagContentMap(bagInfo, bagContainMapTemp);
	}
}
