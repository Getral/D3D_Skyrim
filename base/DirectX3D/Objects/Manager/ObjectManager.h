#pragma once
class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	~ObjectManager();

	void Update();
	void Render();
	void GUIRender();

	Model* GetModel(string inname);
	void Create(Vector3 pos, string inname);

private:
	vector<Model*> structures;
	vector<Model*> items;

	vector<Model*> world_structures;
	vector<Model*> world_items;
};

