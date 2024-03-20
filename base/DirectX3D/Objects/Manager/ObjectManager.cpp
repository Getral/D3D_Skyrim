#include "Framework.h"

ObjectManager::ObjectManager()
{
	structures.push_back(new Structure("farmhouse", { 0,0,0 }, { 1350,650,1250 }, "Structure"));
	structures.push_back(new Structure("farmhouse2", { 0,0,0 }, { 1350,650,1250 }, "Structure"));

	structures.push_back(new Structure("ebonydagger", { 0,0,0 }, { 10,10,10 }, "Item"));
}

ObjectManager::~ObjectManager()
{
	for (Structure* structure : structures)
		delete structure;
	for (Structure* item : items)
		delete item;

	for (Structure* structure : world_structures)
		delete structure;
	for (Structure* item : world_items)
		delete item;

	vector<BoxCollider*> structures_col;
	vector<BoxCollider*> items_col;
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

	FOR(world_structures.size())
	{
		if (world_structures[i]->GetCollider()->IsCollision(player->GetCollier()))
		{
			Vector3 collisionBlock = world_structures[i]->GetModel()->Pos();

			Vector3 dir = player->GetCollier()->GlobalPos() - collisionBlock;

			int maxIndex = 0;
			float maxValue = 0.0f;

			for (int i = 0; i < 3; i++)
			{
				if (abs(dir[i]) > maxValue)
				{
					maxIndex = i;
					maxValue = abs(dir[i]);
				}
			}

			switch (maxIndex)
			{
			case 0:
				dir.x = dir.x > 0 ? 1.0f : -1.0f;
				dir.y = 0;
				dir.z = 0;
				break;
			case 1:
				dir.y = dir.y > 0 ? 1.0f : -1.0f;
				dir.x = 0;
				dir.z = 0;
				break;
			case 2:
				dir.z = dir.z > 0 ? 1.0f : -1.0f;
				dir.y = 0;
				dir.x = 0;
				break;
			}

			if (NearlyEqual(dir.y, 1.0f)) continue;

			player->GetCollier()->GetParent()->Pos() += dir * 50.0f * DELTA;
		}
	}

	FOR(world_items.size())
	{
		if (player->GetCollier()->IsCollision(world_items[i]->GetCollider()))
		{
			UIManager::Get()->GetInvenUI()->AddItem(world_items[i]->GetModel()->GetName());
			world_items.erase(world_items.begin() + i);
		}
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
	if(world_structures.size() > 1)
		world_structures[0]->GUIRender();
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