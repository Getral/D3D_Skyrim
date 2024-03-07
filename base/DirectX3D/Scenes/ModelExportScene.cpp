#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    string name = "Bear";
    string file = "Models/FBX/" + name + ".fbx";
    ModelExporter* exporter;
    string clipName;

    exporter = new ModelExporter(name, file);
    exporter->ExportMaterial();
    exporter->ExportMesh();
    delete exporter;

    clipName = "bear_attack2";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;

    clipName = "bear_attack3";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;
}

ModelExportScene::~ModelExportScene()
{
}

void ModelExportScene::Update()
{
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
}

void ModelExportScene::PostRender()
{
}

void ModelExportScene::GUIRender()
{
}
