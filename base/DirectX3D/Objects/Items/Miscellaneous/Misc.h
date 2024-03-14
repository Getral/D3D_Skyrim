#pragma once

class Misc: public Item
{	
public:
	Misc(string name, int type, int weight, int value, int count);

	int& GetCount() { return count; }
private:
	int count;
};

