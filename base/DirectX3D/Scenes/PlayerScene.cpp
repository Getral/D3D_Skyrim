#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	player = new Player();

	//aldu = new alduin();
	//aldu->SetTarget(player);

	fox = new Model("Fox");
	fox->Pos() = { 100,0,100 };
	fox->Rot().x = XM_PI / 2;
	fox->Scale() *= 1.0f;
	fox->UpdateWorld();

	CAM->SetTarget(player); 
	CAM->TargetOptionLoad("Skyrim");
	CAM->LookAtTarget(); 
}

PlayerScene::~PlayerScene()
{
	//delete aldu;
	delete terrain;
	delete player;
	delete fox;
}

void PlayerScene::Update()
{
	player->Update();
	//aldu->Update();
	UIManager::Get()->Update(player, SpawnManager::Get()->GetMonsterSpawnManager());
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	player->Render();
	//aldu->Render();
	fox->Render();
}

void PlayerScene::PostRender()
{
	UIManager::Get()->PostRender();
}

void PlayerScene::GUIRender()
{
	player->GUIRender();
	//aldu->GUIRender();
	UIManager::Get()->GUIRender();
}
