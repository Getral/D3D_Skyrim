#include "Framework.h"

Item::Item(string name, int type, int weight, int value)
{
	status.name = name;
	status.type = type;
	status.weight = weight;
	status.gold = value;
}
