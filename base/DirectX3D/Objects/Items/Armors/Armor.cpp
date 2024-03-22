#include "Framework.h"
#include "Armor.h"

Armor::Armor(string name, int type, int weight, int value, 
	int armor_class, int armor_type, int def)
	: Item(name, type, weight, value), armor_class(armor_class),
	armor_type(armor_type),def(def)
{
}
