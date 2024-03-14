#pragma once
class Potion : public Item
{
public:
	enum PotionType
	{
		POTION_HP,
		POTION_SP
	};
	Potion(string name, int type, int weight, int value, int potion_type, int amount);

	int GetAmount() { return amount; }
	int& GetCount() { return count; }
private:
	int potion_type;
	int amount;
	int count;
};

