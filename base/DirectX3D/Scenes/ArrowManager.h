#pragma once
class ArrowManager : public Singleton<ArrowManager>
{
private:
	friend class Singleton;

	UINT SIZE = 5;

	enum ArrowClass
	{
		IRON,
		EBONY
	};

	vector<string> arrowclass = {
		"Iron", "Ebony"
	};

public:
	ArrowManager();
	~ArrowManager();

	void Update();
	void Render();

	void Shoot(Vector3 pos, Vector3 dir); 

	bool IsCollision(Collider* collider);

	//vector<ModelInstancing*> GetArrowInstancing() { return arrowInstancing; }
	ModelInstancing* GetArrowInstancing() { return arrowInstancing; }

private:
	//vector<ModelInstancing*> arrowInstancing;
	ModelInstancing* arrowInstancing;
	vector<EbonyArrow*> arrows;
};

