#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    string name = "male_dragonbone";
    string file = "Models/FBX/" + name + ".fbx";
    ModelExporter* exporter;
    string clipName;

    exporter = new ModelExporter(name, file);
    exporter->ExportMaterial();
    exporter->ExportMesh();
    delete exporter;    

    clipName = "male_idle";
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
