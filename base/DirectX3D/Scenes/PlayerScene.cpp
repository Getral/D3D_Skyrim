#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	//player = new Player();
	//
	//aldu = new alduin();
	//aldu->SetTarget(player);
	//
	//fox = new Model("Fox");
	//fox->UpdateWorld();
	//
	//CAM->SetTarget(player); 
	//CAM->TargetOptionLoad("Skyrim");
	//CAM->LookAtTarget(); 

	test3 = new Model("test3");


	CAM->SetTarget(player);
	CAM->TargetOptionLoad("Skyrim");
	CAM->LookAtTarget();
}

PlayerScene::~PlayerScene()
{
	//delete aldu;
	delete terrain;
	delete player;
	delete test3;
}

void PlayerScene::Update()
{
	//player->Update();
	//aldu->Update();
	test3->UpdateWorld();
	//UIManager::Get()->Update(player, fox);
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	//player->Render();
	//aldu->Render();
	test3->Render();
}

void PlayerScene::PostRender()
{
	UIManager::Get()->PostRender();
}

void PlayerScene::GUIRender()
{
	//player->GUIRender();
	//aldu->GUIRender();
	test3->GUIRender();
}
