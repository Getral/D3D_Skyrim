#pragma once

class Item
{
public:
	struct Status
	{
		string name;
		float type;
		float weaght;	// 무게
		float gold;		// 화페
		float value;	// 개수
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

