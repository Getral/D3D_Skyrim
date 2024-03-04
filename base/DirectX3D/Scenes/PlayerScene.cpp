#include "Framework.h"
#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	player = new Player();

	fox = new Model("Fox");
	fox->Pos() = { -300,0,-300 };
	fox->Rot().x += XM_PI / 2;
	fox->Rot().y += -XM_PI / 4 * 3;

	fox->Scale() *= 10.0f;

}

PlayerScene::~PlayerScene()
{
	delete terrain;
	delete player;
}

void PlayerScene::Update()
{
	player->Update();

	UIManager::Get()->Update(player, fox);
	fox->UpdateWorld();
}

void PlayerScene::PreRender()
{
}

void PlayerScene::Render()
{
	player->Render();
	fox->Render();
}

void PlayerScene::PostRender()
{
	UIManager::Get()->PostRender();
	player->PostRender();
}

void PlayerScene::GUIRender()
{
	player->GUIRender();
}
