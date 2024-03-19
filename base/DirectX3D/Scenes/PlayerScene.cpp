#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	player = new Player();

	aldu = new alduin();
	aldu->SetTarget(player);

	//CAM->SetTarget(player); 
	//CAM->TargetOptionLoad("skyrim2");
	//CAM->LookAtTarget(); 


	
}

PlayerScene::~PlayerScene()
{
	delete aldu;
	delete terrain;
	delete player;
}

void PlayerScene::Update()
{
	player->Update();
	//aldu->Update();
	UIManager::Get()->Update(player, SpawnManager::Get()->GetMonsterSpawnManager(),aldu);
	ObjectManager::Get()->Update();

	if(KEY_DOWN('R'))
		ObjectManager::Get()->Create({ 0,0,0 }, "farmhouse");
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	//player->Render();
	//aldu->Render();
	ObjectManager::Get()->Render();
}

void PlayerScene::PostRender()
{
	UIManager::Get()->PostRender();

}

void PlayerScene::GUIRender()
{
	//player->GUIRender();
	//aldu->GUIRender();

	ObjectManager::Get()->GUIRender();
}
