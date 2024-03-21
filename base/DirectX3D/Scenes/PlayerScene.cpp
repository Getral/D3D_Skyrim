#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	//terrain = new Terrain();
	//terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	//terrain->UpdateWorld();

	player = new Player();
	player->Scale() *= 0.1f;

	//aldu = new alduin();
	//aldu->SetTarget(player);

	CAM->SetTarget(player); 
	CAM->TargetOptionLoad("test123");
	CAM->LookAtTarget(); 


}

PlayerScene::~PlayerScene()
{
	//delete aldu;
	//delete terrain;
	delete player;
}

void PlayerScene::Update()
{
	player->Update();
	//aldu->Update();
	//UIManager::Get()->Update(player, SpawnManager::Get()->GetMonsterSpawnManager(),aldu);
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	player->Render();
	//aldu->Render();
}

void PlayerScene::PostRender()
{
	//UIManager::Get()->PostRender();
}

void PlayerScene::GUIRender()
{
	player->GUIRender();
	//aldu->GUIRender();
}
