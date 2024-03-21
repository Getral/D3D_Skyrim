#pragma once
class Structure
{
public:
	Structure(string modelName,float scale, Vector3 colliderSize, string tag);
	~Structure();

	string GetmodelName() { return modelName; }
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
	float scale;
	Vector3 colliderSize;
	string tag;
};

