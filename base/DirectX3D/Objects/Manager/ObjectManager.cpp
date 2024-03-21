#include "Framework.h"

ObjectManager::ObjectManager()
{
	structures.push_back(new Structure("farmhouse", 0.01f, { 1350,650,1250 }, "Structure"));
	structures.push_back(new Structure("farmhouse2", 0.07f, { 1350,650,1250 }, "Structure"));
	structures.push_back(new Structure("rock_large1", 0.05f, { 250, 400, 250 }, "Structure"));
	structures.push_back(new Structure("rock_large2", 0.05f, { 600, 490, 200 }, "Structure"));
	structures.push_back(new Structure("rock_large3", 0.05f, { 400, 400, 150 }, "Structure"));
	structures.push_back(new Structure("rock_large4", 0.05f, { 200, 250, 370 }, "Structure"));
	structures.push_back(new Structure("rock_large5", 0.05f, { 250, 300, 190 }, "Structure"));
	structures.push_back(new Structure("rock_medium1", 0.05f, { 250, 160, 110 }, "Structure"));
	structures.push_back(new Structure("rock_medium2", 0.05f, { 130, 130, 100 }, "Structure"));
	structures.push_back(new Structure("rock_medium3", 0.05f, { 250, 230, 135 }, "Structure"));
	structures.push_back(new Structure("rock_medium4", 0.05f, { 150, 140, 100 }, "Structure"));

	structures.push_back(new Structure("tree", 0.025f, { 10,10,10 }, "Structure", true));


	items.push_back(new Structure("ebonydagger", 0.1f, { 10,10,10 }, "Item"));

	
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
	{
		structure->Render();
	}

	for (Structure* item : world_items)
		item->Render();
}

void ObjectManager::GUIRender()
{

}

void ObjectManager::Create(Vector3 pos, float Rot_y, string inname)
{
	if (GetStructure(inname)->GetModel()->GetTag() == "Structure")
	{
		Structure* temp = new Structure(GetStructure(inname)->GetmodelName(), GetStructure(inname)->GetScale(), GetStructure(inname)->GetColliderSize(), GetStructure(inname)->GetTag(),GetStructure(inname)->GetIsAlpha());
		world_structures.push_back(temp);
		world_structures.back()->GetModel()->Pos() = pos;
		world_structures.back()->GetModel()->Rot().y = Rot_y;
	}
		
	if (GetStructure(inname)->GetModel()->GetTag() == "Item")
	{
		Structure* temp = new Structure(GetStructure(inname)->GetmodelName(), GetStructure(inname)->GetScale(), GetStructure(inname)->GetColliderSize(), GetStructure(inname)->GetTag());
		world_items.push_back(temp);
		world_items.back()->GetModel()->Pos() = pos;
		world_items.back()->GetModel()->Rot().y = Rot_y;
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