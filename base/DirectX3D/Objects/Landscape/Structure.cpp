#include "Framework.h"
#include "Structure.h"

Structure::Structure(string modelName, float scale, Vector3 colliderSize, string tag, bool isAlpha)
	:modelName(modelName),scale(scale),colliderSize(colliderSize),tag(tag)
{
	model = new Model(modelName);
	model->SetTag(tag);
	model->SetName(modelName);
	model->Scale() *= scale;

	if (tag == "Structure")
	{
		model->Rot().x += XM_PI / 2;
	}
	
	else if (tag == "Item")
	{
	}

	FOR(2) blendState[i] = new BlendState();
	blendState[1]->AlphaToCoverage(true);
	
	
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
	blendState[1]->SetState();
	model->Render();
	blendState[0]->SetState();
	collider->Render();
}

void Structure::GUIRender()
{
	collider->GUIRender();
	model->GUIRender();
}
