#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	/*monsterInstancing = new ModelAnimatorInstancing("alduin");
	monsterInstancing->Scale() *= 0.001;
	monsterInstancing->ReadClip("alduin_fly");
	monsterInstancing->ReadClip("alduin_bite");*/

	alduin = new ModelAnimator("alduin");
	alduin->Scale() *= 0.001;
	alduin->ReadClip("alduin_fly",0);
	alduin->ReadClip("alduin_bite",1);

	alduin->PlayClip(1);

	//spawningPool = new SpawningPool(monsterInstancing, Vector3(0, 0, 0));
}

TestScene::~TestScene()
{
	delete terrain;
	delete monsterInstancing;
	delete spawningPool;
	delete alduin;
}

void TestScene::Update()
{
	//spawningPool->Update();
	//monsterInstancing->Update();
	alduin->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	terrain->Render();
	//spawningPool->Render();
	alduin->Render();

}

void TestScene::PostRender()
{
}

void TestScene::GUIRender()
{
	//spawningPool->GUIRender();
	//monsterInstancing->GUIRender();
	alduin->GUIRender();
}
