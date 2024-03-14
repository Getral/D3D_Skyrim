#include "Framework.h"
#include "Arrow.h"

Arrow::Arrow(string name, int type, int weight, int value, int arrow_type, int atk)
	:Item(name,type,weight,value),arrow_type(arrow_type),atk(atk)
{
}
