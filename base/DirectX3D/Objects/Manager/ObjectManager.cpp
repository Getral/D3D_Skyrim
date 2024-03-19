#include "Framework.h"

ObjectManager::ObjectManager()
{
	structures.push_back(new Structure("farmhouse", { 0,0,0 }, { 1350,650,1250 }, "Structure"));
	structures.push_back(new Structure("farmhouse2", { 0,0,0 }, { 1350,650,1250 }, "Structure"));

	structures.push_back(new Structure("ebonydagger", { 0,0,0 }, { 10,10,10 }, "Item"));
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update(Player* player)
{
	for (Structure* structure : world_structures)
	{
		structures_col.push_back(structure->GetCollider());
		structure->Update();
	}
	for (Structure* item : world_items)
	{
		items_col.push_back(item->GetCollider());
		item->Update();
	}

	FOR(world_items.size())
	{
		if (player->GetCollier()->IsCollision(world_items[i]->GetCollider()))
			UIManager::Get()->GetInvenUI()->AddItem(world_items[i]->GetModel()->GetName());
	}
}

void ObjectManager::Render()
{
	for (Structure* structure : world_structures)
		structure->Render();
	for (Structure* item : world_items)
		item->Render();

}

void ObjectManager::GUIRender()
{
}

void ObjectManager::Create(Vector3 pos, string inname)
{
	if (GetStructure(inname)->GetModel()->GetTag() == "Structure")
	{
		GetStructure(inname)->GetModel()->Pos() = pos;
		world_structures.push_back(GetStructure(inname));
	}
		
	if (GetStructure(inname)->GetModel()->GetTag() == "Item")
	{
		GetStructure(inname)->GetModel()->Pos() = pos;
		world_items.push_back(GetStructure(inname));
	}
}


Structure* ObjectManager::GetStructure(string inname)
{
	for (Structure* structure : structures)
	{
		if (structure->GetModel()->GetName() == inname)
		{
			return structure;
		}
	}

	for (Structure* item : items)
	{
		if (item->GetModel()->GetName() == inname)
		{
			return item;
		}
	}
}

