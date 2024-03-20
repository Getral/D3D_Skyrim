#pragma once
class Structure
{
public:
	Structure(string modelName, Vector3 pos, float scale, Vector3 colliderSize, string tag);
	~Structure();

	void Update();
	void Render();
	void GUIRender();

	BoxCollider* GetCollider() { return collider; }
	Model*& GetModel() { return model; }
private:
	Model* model;
	BoxCollider* collider;
};

