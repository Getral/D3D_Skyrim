#include "Framework.h"
#include "Armor.h"

Armor::Armor(string name, int type, int weight, int value, int armortype, int def)
	: Item(name, type, weight, value), armortype(armortype),def(def)
{
	name = "dsadsad";
	type = Item::AROMOR;
	weight = 10;
	value = 10;
	armortype = Armor::helmat;
	def = 10;
}
