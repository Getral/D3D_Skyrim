#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	player = new Player();

	aldu = new alduin();
	aldu->SetTarget(player);
	aldu->Pos() = { 244,0,150 };
	aldu->GetTransform()->Pos() = {244, 0, 150};
	

	//CAM->SetTarget(player); 
	//CAM->TargetOptionLoad("Skyrim2");
	//CAM->LookAtTarget(); 

	rock = new Model("farmhouse");
	rock->Scale() *= 0.01f;
	rock->Rot().x += XM_PI / 2;
	rock->Pos() = { 234,0,300 };
	//rock->Scale().x *= 0.5f;
	//rock->Scale().y *= 0.5f;

	rock2 = new Model("rock_large4");
	rock2->Scale() *= 0.05f;
	rock2->Rot().x += XM_PI / 2;
	rock2->Pos() = { 286,0,270 };
	//rock2->Scale().x *= 0.5f;
	//rock2->Scale().y *= 0.5f;
}

PlayerScene::~PlayerScene()
{
	//delete aldu;
	delete player;
}

void PlayerScene::Update()
{
	player->Update();
	aldu->Update();
	UIManager::Get()->Update(player, SpawnManager::Get()->GetMonsterSpawnManager(),aldu);
	ObjectManager::Get()->Update(player);
	rock->UpdateWorld();
	rock2->UpdateWorld();
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	player->Render();
	aldu->Render();
	ObjectManager::Get()->Render();
	//rock->Render();
	//rock2->Render();
}

void PlayerScene::PostRender()
{
	UIManager::Get()->PostRender();

}

void PlayerScene::GUIRender()
{
	//player->GUIRender();
	//aldu->GUIRender();
	//UIManager::Get()->GUIRender();
	//FOR(test.size())
	rock->GUIRender();
	//rock2->GUIRender();
}
