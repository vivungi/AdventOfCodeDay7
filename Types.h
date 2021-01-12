#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <unordered_map>
#include <set>

using BagIdMap = std::unordered_map<std::string, int>;

struct BagIdCountInfo
{
	int bagId;
	int bagCount;
};

struct BagIdCountInfoCmp {
	bool operator()(const BagIdCountInfo& lhs, const BagIdCountInfo& rhs) const {
		return lhs.bagId < rhs.bagId;
	}
};


using BagIdCountSet = std::set < BagIdCountInfo, BagIdCountInfoCmp > ;
using BagContentMap = std::unordered_map<int, BagIdCountSet>;

struct BagInfo
{
	BagIdMap bagIdMap;
	BagContentMap bagContentMap;
};

#endif