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
	player->Update();
	player_dragon->Pos() = player->Pos();
	player_dragon->Update();

	player_iron->Pos() = player->Pos();
	player_iron->Update();
	aldu->Update();
	UIManager::Get()->Update(player, SpawnManager::Get()->GetMonsterSpawnManager(),aldu);
	ObjectManager::Get()->Update(player);
	if (KEY_DOWN('T'))
	{
		ObjectManager::Get()->GetIsColRender() = !ObjectManager::Get()->GetIsColRender();
		aldu->SetIsColliderRend() = !aldu->SetIsColliderRend();
		player->SetisCollRend() = !player->SetisCollRend();
		player_dragon->SetisCollRend() = !player_dragon->SetisCollRend();
		player_iron->SetisCollRend() = !player_iron->SetisCollRend();
	}
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	if(UIManager::Get()->GetInvenUI()->GetHelmetClass() == Armor::NONE)
		player->Render();
	else if (UIManager::Get()->GetInvenUI()->GetHelmetClass() == Armor::IRON)
		player_iron->Render();
	else if (UIManager::Get()->GetInvenUI()->GetHelmetClass() == Armor::DRAGONBONE)
		player_dragon->Render();


	aldu->Render();
	ObjectManager::Get()->Render();
}

void PlayerScene::PostRender()
{
	UIManager::Get()->PostRender();
	ObjectManager::Get()->PostRender(player);
}

void PlayerScene::GUIRender()
{
	//player->GUIRender();
	//aldu->GUIRender();
	//UIManager::Get()->GUIRender();	

	ImGui::Text("bool : %d", ObjectManager::Get()->GetIsColRender());
}
