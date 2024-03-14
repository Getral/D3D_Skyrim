#include "Framework.h"

Misc::Misc(string name, int type, int weight, int value, int count)
	: Item(name, type, weight, value), count(count)
{
}
