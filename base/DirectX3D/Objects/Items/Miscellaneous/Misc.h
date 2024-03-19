#pragma once

class Misc: public Item
{	
public:
	Misc(string name, int type, int weight, int value);

	int& GetCount() { return count; }
private:
	int count = 1;
};

