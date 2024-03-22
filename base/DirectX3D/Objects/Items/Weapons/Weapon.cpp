#include "Framework.h"
#include "Weapon.h"

Weapon::Weapon(string name, int type, int weight, int value, int weapon_class, int weapon_type, int atk)
	: Item(name, type, weight, value), weapon_class(weapon_class), weapon_type(weapon_type), atk(atk)
{
}
