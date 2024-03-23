#include "Framework.h"

ObjectManager::ObjectManager()
{
	structures.push_back(new Structure("farmhouse", 0.01f, { 1350,650,1250 }, "Structure"));
	structures.push_back(new Structure("farmhouse2", 0.01f, { 1350,650,1250 }, "Structure"));
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

	itemboxes.push_back(new Structure("chest", 0.015f, { 10, 10, 10 }, "ItemBox"));
	itemboxes.push_back(new Structure("chest_armor_iron", 0.015f, { 140, 70, 70 }, "ItemBox"));
	itemboxes.push_back(new Structure("chest_armor_dragon", 0.015f, { 10, 10, 10 }, "ItemBox"));
	itemboxes.push_back(new Structure("chest_weapon_iron", 0.015f, { 10, 10, 10 }, "ItemBox"));
	itemboxes.push_back(new Structure("chest_weapon_ebony", 0.015f, { 10, 10, 10 }, "ItemBox"));
	itemboxes.push_back(new Structure("chest_potion", 0.015f, { 10, 10, 10 }, "ItemBox"));


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

}

void ObjectManager::Update(Player* player)
{
	for (Structure* structure : world_structures)
	{
		structures_col.push_back(structure->GetCollider());
		structure->Update();
	}

	for (Structure* box : world_itemboxes)
	{
		itemboxes_col.push_back(box->GetCollider());
		box->Update();
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

	FOR(world_itemboxes.size())
	{
		if (player->GetCollier()->IsCollision(world_itemboxes[i]->GetCollider()) && KEY_DOWN('E'))
		{
			if (world_itemboxes[i]->GetmodelName() == "chest_armor_iron")
			{
				UIManager::Get()->GetInvenUI()->AddItem("ironcuirass");
				UIManager::Get()->GetInvenUI()->AddItem("irongauntlets");
				UIManager::Get()->GetInvenUI()->AddItem("ironboots");
				UIManager::Get()->GetInvenUI()->AddItem("ironhelmet");
				UIManager::Get()->GetInvenUI()->AddItem("ironshield");
			}

			if (world_itemboxes[i]->GetmodelName() == "chest_armor_dragon")
			{
				UIManager::Get()->GetInvenUI()->AddItem("dragoncuirass");
				UIManager::Get()->GetInvenUI()->AddItem("dragongauntlets");
				UIManager::Get()->GetInvenUI()->AddItem("dragonboots");
				UIManager::Get()->GetInvenUI()->AddItem("dragonhelmet");
				UIManager::Get()->GetInvenUI()->AddItem("dragonshield");
			}

			if (world_itemboxes[i]->GetmodelName() == "chest_weapon_iron")
			{
				UIManager::Get()->GetInvenUI()->AddItem("irondagger");
				UIManager::Get()->GetInvenUI()->AddItem("ironclaymore");
				UIManager::Get()->GetInvenUI()->AddItem("ironwaraxe");
				UIManager::Get()->GetInvenUI()->AddItem("ironmace");
				UIManager::Get()->GetInvenUI()->AddItem("ironlongsword");
				UIManager::Get()->GetInvenUI()->AddItem("ironbattleaxe");
				UIManager::Get()->GetInvenUI()->AddItem("ironwarhammer");
				UIManager::Get()->GetInvenUI()->AddItem("ironbow");
				for(int j = 0; j < 10; j++)
					UIManager::Get()->GetInvenUI()->AddItem("ironarrow");
			}

			if (world_itemboxes[i]->GetmodelName() == "chest_weapon_ebony")
			{
				UIManager::Get()->GetInvenUI()->AddItem("ebonydagger");
				UIManager::Get()->GetInvenUI()->AddItem("ebonyclaymore");
				UIManager::Get()->GetInvenUI()->AddItem("ebonywaraxe");
				UIManager::Get()->GetInvenUI()->AddItem("ebonymace");
				UIManager::Get()->GetInvenUI()->AddItem("ebonylongsword");
				UIManager::Get()->GetInvenUI()->AddItem("ebonybattleaxe");
				UIManager::Get()->GetInvenUI()->AddItem("ebonywarhammer");
				UIManager::Get()->GetInvenUI()->AddItem("ebonybow");
				for (int j = 0; j < 10; j++)
					UIManager::Get()->GetInvenUI()->AddItem("ebonyarrow");
			}

			if (world_itemboxes[i]->GetmodelName() == "chest_potion")
			{
				for (int j = 0; j < 10; j++)
				{
					UIManager::Get()->GetInvenUI()->AddItem("hp_potion");
					UIManager::Get()->GetInvenUI()->AddItem("sp_potion");
				}
			}
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
	
	for (Structure* box : world_itemboxes)
		box->Render();

	for (Structure* item : world_items)
		item->Render();
}

void ObjectManager::PostRender(Player* player)
{
	FOR(world_itemboxes.size())
	{
		if (player->GetCollier()->IsCollision(world_itemboxes[i]->GetCollider()))
		{
			Font::Get()->RenderText(world_itemboxes[i]->GetmodelName().c_str(), { CENTER_X - 50,CENTER_Y - 250 });
		}
	}
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

	if (GetStructure(inname)->GetModel()->GetTag() == "ItemBox")
	{
		Structure* temp = new Structure(GetStructure(inname)->GetmodelName(), GetStructure(inname)->GetScale(), GetStructure(inname)->GetColliderSize(), GetStructure(inname)->GetTag());
		world_itemboxes.push_back(temp);
		world_itemboxes.back()->GetModel()->Pos() = pos;
		world_itemboxes.back()->GetModel()->Rot().y = Rot_y;
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

	for (Structure* box : itemboxes)
	{
		if (box->GetModel()->GetName() == inname)
		{
			return box;
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