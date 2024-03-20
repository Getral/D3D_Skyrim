#include "Framework.h"

Item::Item(string name, int type, int weight, int value)
	: Model(name)
{
	status.name = name;
	status.type = type;
	status.weight = weight;
	status.value = value;
}
