#pragma once

class Item
{
public:
	struct Status
	{
		string name;
		int type;
		int weight;	
		int gold;	
		int count;
	};

	enum Type
	{
		AROMOR,
		WEAPON,
		CLOTHING,
		EXPENDABLES,
		MISC
	};

public:
	Item(string name, int type,	int weight, int value);
	
	Status& GetStatus() { return status; }
private:
	Status status;	
};