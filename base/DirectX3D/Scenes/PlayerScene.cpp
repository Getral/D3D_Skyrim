#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	player = new Player();

	CAM->SetTarget(player); 
	CAM->TargetOptionLoad("Skyrim");
	CAM->LookAtTarget(); 
}

PlayerScene::~PlayerScene()
{
	delete terrain;
	delete player;
}

void PlayerScene::Update()
{
	player->Update();
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	player->Render();
}

void PlayerScene::PostRender()
{
}

void PlayerScene::GUIRender()
{
	player->GUIRender();
}
