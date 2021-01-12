#ifndef CountBagsH
#define CountBagsH
#include <string>

struct BagInfo;

int CountBagsContainingBag(const BagInfo& bagInfo, std::string bagName);

int CountBagsContainedInBag(const BagInfo& bagInfo, std::string bagName);

#endif