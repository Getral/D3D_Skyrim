#include "Framework.h"
#include "alduinScene.h"

alduinScene::alduinScene()
{
	aldu = new alduin();
}

alduinScene::~alduinScene()
{

	delete aldu;
}

void alduinScene::Update()
{
	aldu->Update();
}

void alduinScene::PreRender()
{
}

void alduinScene::Render()
{

	aldu->Render();
}

void alduinScene::PostRender()
{
}

void alduinScene::GUIRender()
{
	aldu->GUIRender();
}
