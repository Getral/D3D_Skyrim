#pragma once
class Structure
{
public:
	Structure(string modelName, Vector3 pos, float scale, Vector3 colliderSize, string tag);
	~Structure();

	string GetmodelName() { return modelName; }
	Vector3 GetPos() { return pos; }
	float GetScale() { return scale; }
	Vector3 GetColliderSize() { return colliderSize; }
	string GetTag() { return tag; }

	void Update();
	void Render();
	void GUIRender();

	BoxCollider* GetCollider() { return collider; }
	Model*& GetModel() { return model; }
private:
	Model* model;
	BoxCollider* collider;

	string modelName;
	Vector3 pos;
	float scale;
	Vector3 colliderSize;
	string tag;
};

