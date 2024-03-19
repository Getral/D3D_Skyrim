#include "Framework.h"
#include "Structure.h"

Structure::Structure(string modelName, Vector3 pos, Vector3 size, string tag)
{
	model = new Model(modelName);
	model->Pos() = pos;
	if (tag == "Structure")
	{
		model->Rot().x += XM_PI / 2;
		model->Scale() *= 0.01f;
	}
	
	else if (tag == "Item")
	{
		model->Scale() *= 0.1f;
	}
	model->SetTag(tag);
	model->SetName(modelName);

	collider = new BoxCollider(size);
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
