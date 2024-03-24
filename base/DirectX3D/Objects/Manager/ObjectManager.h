#pragma once
class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	~ObjectManager();

	void Update(Player* player);
	void Render();
	void PostRender(Player* player);
	void GUIRender();

	Structure* GetStructure(string inname);
	void Create(Vector3 pos, float Rot_y, string inname);

private:
	vector<Structure*> structures;
	vector<Structure*> itemboxes;
	vector<Structure*> items;
	
	vector<Structure*> world_structures;
	vector<Structure*> world_itemboxes;
	vector<Structure*> world_items;

	vector<BoxCollider*> structures_col;
	vector<BoxCollider*> itemboxes_col;
	vector<BoxCollider*> items_col;
};

