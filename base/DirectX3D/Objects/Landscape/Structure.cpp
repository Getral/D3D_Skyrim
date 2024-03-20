#include "Framework.h"
#include "Structure.h"

Structure::Structure(string modelName, Vector3 pos, float scale, Vector3 colliderSize, string tag)
{
	model = new Model(modelName);
	model->Pos() = pos;
	model->SetTag(tag);
	model->SetName(modelName);
	model->Scale() *= scale;

	if (tag == "Structure")
	{
		//model->Rot().x += XM_PI / 2;
		//model->Scale() *= 0.07f;
	}
	
	else if (tag == "Item")
	{
		//model->Scale() *= 0.1f;
	}
	

	collider = new BoxCollider(colliderSize);
	collider->SetParent(model);
}

Structure::~Structure()
{
}

void Structure::Update()
{
	model->UpdateWorld();
	collider->UpdateWorld();
}

void Structure::Render()
{
	model->Render();
	collider->Render();
}

void Structure::GUIRender()
{
	collider->GUIRender();
}
