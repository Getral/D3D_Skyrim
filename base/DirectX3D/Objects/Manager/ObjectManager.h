#pragma once
class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	~ObjectManager();

	void Update(Player* player);
	void Render();
	void GUIRender();

	vector<Structure*>& GetsStructures() { return world_structures; }
	vector<BoxCollider*> GetItemsCol() { return items_col; }

	Structure* GetStructure(string inname);
	void Create(Vector3 pos, string inname);

private:
	vector<Structure*> structures;
	vector<Structure*> items;
	
	vector<Structure*> world_structures;
	vector<Structure*> world_items;

	vector<BoxCollider*> structures_col;
	vector<BoxCollider*> items_col;
};

