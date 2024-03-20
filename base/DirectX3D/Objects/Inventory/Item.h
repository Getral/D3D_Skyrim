#pragma once

class Item : public Model
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

protected:
	Status status;	
};