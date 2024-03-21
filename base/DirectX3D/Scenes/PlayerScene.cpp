#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	player = new Player();

	aldu = new alduin();
	aldu->SetTarget(player);
	aldu->Pos() = { 280,0,200 };
	aldu->GetTransform()->Pos() = {280, 0, 123};
	

	CAM->SetTarget(player); 
	CAM->TargetOptionLoad("Skyrim2");
	CAM->LookAtTarget(); 

	
}

PlayerScene::~PlayerScene()
{
	delete aldu;
	delete player;
}

void PlayerScene::Update()
{
	player->Update();
	aldu->Update();
	UIManager::Get()->Update(player, SpawnManager::Get()->GetMonsterSpawnManager(),aldu);
	ObjectManager::Get()->Update(player);

}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	player->Render();
	aldu->Render();
	ObjectManager::Get()->Render();
	
}

void PlayerScene::PostRender()
{
	UIManager::Get()->PostRender();

}

void PlayerScene::GUIRender()
{
	player->GUIRender();
	aldu->GUIRender();
	UIManager::Get()->GUIRender()
}
