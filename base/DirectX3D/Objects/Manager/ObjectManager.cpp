#include "Framework.h"

ObjectManager::ObjectManager()
{
	structures.push_back(new Model("farmhouse"));
	structures.back()->SetName("farmhouse");
	structures.back()->Rot().x += XM_PI / 2;
	structures.back()->Scale() *= 0.01f;
	structures.back()->SetName("farmhouse");
	
	//structures.push_back(new Model("farmhouse2"));
	//structures.back()->SetName("farmhouse2");
	
	for (Model* structure : structures)
	{
		structure->Rot().x += XM_PI / 2;
		structure->Scale() *= 0.01f;
		structure->SetTag("Structure");
	}

	items.push_back(new Model("ebonydagger"));
	items.back()->SetName("ebonydagger");

	for (Model* item : items)
	{
		item->Scale() *= 0.1f;
		item->SetTag("Item");
	}
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update()
{
	for (Model* structure : world_structures)
		structure->UpdateWorld();
	for (Model* item : world_items)
		item->UpdateWorld();
}

void ObjectManager::Render()
{
	for (Model* structure : structures)
		structure->Render();
	//for (Model* item : world_items)
	//	item->Render();
}

void ObjectManager::GUIRender()
{
	//ImGui::Text(structures[0]->GetTag().c_str());
	//ImGui::Text(structures[1]->GetTag().c_str());
	//ImGui::Text(structures[0]->GetName().c_str());
	//ImGui::Text(structures[1]->GetName().c_str());
	
}

void ObjectManager::Create(Vector3 pos, string inname)
{
	//if (GetModel(inname)->GetTag() == "Structure")
	//	world_structures.push_back(GetModel(inname));
	//if (GetModel(inname)->GetTag() == "Item")
	//	world_items.push_back(GetModel(inname));
}


Model* ObjectManager::GetModel(string inname)
{
	for (Model* structure : structures)
	{
		if (structure->GetTag() == inname)
		{
			return structure;
		}
	}

	for (Model* item : items)
	{
		if (item->GetTag() == inname)
		{
			return item;
		}
	}
}

