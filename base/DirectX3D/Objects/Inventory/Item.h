#pragma once

class Item
{
public:
	struct Status
	{
		string name;
		int type;
		int weight;	
		int value;	
	};
	enum Type
	{
		ARMOR,
		WEAPON,
		ARROW,
		POTION,
		MISC
	};

public:
	Item(string name, int type,	int weight, int value);
	
	Status& GetStatus() { return status; }
private:
	Status status;	
};