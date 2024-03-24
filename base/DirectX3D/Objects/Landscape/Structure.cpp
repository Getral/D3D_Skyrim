#include "Framework.h"
#include "Structure.h"

Structure::Structure(string modelName, float scale, Vector3 colliderSize, string tag, bool isAlpha)
	:modelName(modelName),scale(scale),colliderSize(colliderSize),tag(tag),isAlpha(isAlpha)
{
	if (modelName == "chest_armor_iron" ||
		modelName == "chest_armor_dragon" ||
		modelName == "chest_weapon_iron" ||
		modelName == "chest_weapon_ebony" ||
		modelName == "chest_potion")
	{
		model = new Model("chest");
	}
	else
		model = new Model(modelName);


	model->SetTag(tag);
	model->SetName(modelName);
	model->Scale() *= scale;

	if(isAlpha)
		model->SetShader(L"Basic/Texture.hlsl");

	if (tag == "Structure" || tag == "ItemBox" || tag == "Sign")
	{
		model->Rot().x += XM_PI / 2;
	}
	
	collider = new BoxCollider(colliderSize);
	collider->SetParent(model);

	FOR(2) blendState[i] = new BlendState();
	blendState[1]->AlphaToCoverage(true);

	if(modelName != "coin")
		collider->Pos().z -= colliderSize.z * 0.5f;
}

Structure::~Structure()
{
}

void Structure::Update()
{
	if (tag == "Item")
		model->Rot().y += 10 * DELTA;

	model->UpdateWorld();
	
	collider->UpdateWorld();
}

void Structure::Render()
{
	if (isAlpha)
	{
		blendState[1]->SetState();
		model->Render();
		blendState[0]->SetState();
	}
	else
		model->Render();

	if (isColRender)
		collider->Render();
}

void Structure::GUIRender()
{
	collider->GUIRender();
	model->GUIRender();
}
