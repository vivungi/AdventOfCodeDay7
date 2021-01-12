// SEBDay7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Types.h"
#include "ParseInputFile.h"
#include "CountBags.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BagInfo bagInfo;

	ParseInputFile("C:/Users/Robin/Desktop/SEBDay7Large.txt", bagInfo);
	int numBags = CountBagsContainingBag(bagInfo, "shiny gold");
	std::cout << "Num bags containing shiny gold bags are: " << numBags;
	int numBagsContained = CountBagsContainedInBag(bagInfo, "shiny gold");

	/*light red bags contain 1 bright white bag, 2 muted yellow bags.
		dark orange bags contain 3 bright white bags, 4 muted yellow bags.
		bright white bags contain 1 shiny gold bag.
		muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
		shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
		dark olive bags contain 3 faded blue bags, 4 dotted black bags.
		vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
		faded blue bags contain no other bags.
		dotted black bags contain no other bags.*/
	return 0;
}

