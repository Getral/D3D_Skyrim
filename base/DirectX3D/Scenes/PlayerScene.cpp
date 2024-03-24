#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	player = new Player();
	player_dragon = new Player_Dragon();
	player_iron = new Player_Iron();

	aldu = new alduin();
	aldu->SetTarget(player);
	aldu->Pos() = { 244,0,150 };
	aldu->GetTransform()->Pos() = {244, 0, 150};
	
	CAM->SetTarget(player); 
	CAM->TargetOptionLoad("Skyrim2");
	CAM->LookAtTarget(); 

	player->Render();
	player_iron->Render();
	player_dragon->Render();
}

PlayerScene::~PlayerScene()
{
	delete aldu;
	delete player;
}

void PlayerScene::Update()
{
	if (!UIManager::Get()->IsIntro())
	{
		player->Update();

		player_dragon->Pos() = player->Pos();
		player_dragon->Getis1hm() = player->Getis1hm();
		player_dragon->Getis2hm() = player->Getis2hm();
		player_dragon->Getisbow() = player->Getisbow();
		player_dragon->Update();

		player_iron->Pos() = player->Pos();
		player_iron->Getis1hm() = player->Getis1hm();
		player_iron->Getis2hm() = player->Getis2hm();
		player_iron->Getisbow() = player->Getisbow();
		player_iron->Update();

		aldu->Update();

		ObjectManager::Get()->Update(player);
		if (KEY_DOWN('T'))
		{
			ObjectManager::Get()->GetIsColRender() = !ObjectManager::Get()->GetIsColRender();
			aldu->SetIsColliderRend() = !aldu->SetIsColliderRend();
			player->SetisCollRend() = !player->SetisCollRend();
			player_dragon->SetisCollRend() = !player_dragon->SetisCollRend();
			player_iron->SetisCollRend() = !player_iron->SetisCollRend();
		}
		if (KEY_DOWN('Q'))
		{
			if (!UIManager::Get()->IsQuestStarted())
				UIManager::Get()->StartQuest();
			else
				UIManager::Get()->EndQuest();
		}
	}
	UIManager::Get()->Update(player, SpawnManager::Get()->GetMonsterSpawnManager(),aldu);
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	if (!UIManager::Get()->IsIntro())
	{
		if (UIManager::Get()->GetInvenUI()->GetHelmetClass() == Armor::NONE)
			player->Render();
		else if (UIManager::Get()->GetInvenUI()->GetHelmetClass() == Armor::IRON)
			player_iron->Render();
		else if (UIManager::Get()->GetInvenUI()->GetHelmetClass() == Armor::DRAGONBONE)
			player_dragon->Render();


		aldu->Render();
		ObjectManager::Get()->Render();
	}
}

void PlayerScene::PostRender()
{
	UIManager::Get()->PostRender();
	ObjectManager::Get()->PostRender(player);
}

void PlayerScene::GUIRender()
{
	//player->GUIRender();
	//player_dragon->GUIRender();
	player_iron->GUIRender();
	//aldu->GUIRender();
	UIManager::Get()->GUIRender();	

	//ImGui::Text("bool : %d", ObjectManager::Get()->GetIsColRender());

	// test->GUIRender();
}
