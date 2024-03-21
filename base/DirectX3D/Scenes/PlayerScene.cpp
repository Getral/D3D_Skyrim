#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	player = new Player();

	aldu = new alduin();
	aldu->SetTarget(player);

	CAM->SetTarget(player); 
	CAM->TargetOptionLoad("Skyrim2");
	CAM->LookAtTarget(); 

	ObjectManager::Get()->Create({ 50,0,-50 }, "farmhouse");
	ObjectManager::Get()->Create({ 0,0,0 }, "farmhouse2");
	ObjectManager::Get()->Create({ -50,0,50 }, "ebonydagger");
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
	//aldu->GUIRender();

	//ObjectManager::Get()->GUIRender();
}
