#pragma once
class Arrow : public Item
{
public:
	enum ArrowType
	{
		IRON,
		DRAGONBONE
	};
	Arrow(string name, int type, int weight, int value, int arrow_type, int atk);

	int GetAtk() { return atk; }
	int GetCount() { return count; }
private:
	int arrow_type;
	int atk;
	int count;
};

