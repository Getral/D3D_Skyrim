#include "Framework.h"

Potion::Potion(string name, int type, int weight, int value, int potion_type, int amount)
	:Item(name, type, weight, value),potion_type(potion_type),amount(amount)
{
}