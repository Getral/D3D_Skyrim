#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    // Export With Texture
     
    //vector<string> modelName =
    //{
    //    "rock_small1", "rock_small2"
    //};
    //
    //vector<wstring> textures =
    //{
    //    L"Landscape/rocksgrass01", L"Landscape/rocksgrass01"
    //};

    ////string name = "rock_large2";
    ////string file = "Models/FBX/" + name + ".fbx";
    ////string clipName;

    //FOR(modelName.size())
    //{
    //    string file = "Models/FBX/" + modelName[i] + ".fbx";
    //    wstring textureFile = L"Textures/" + textures[i] + L".png";
    //    ModelExporter* exporter;
    //    exporter = new ModelExporter(modelName[i], file);
    //    exporter->ExportMaterial(textureFile);
    //    exporter->ExportMesh();
    //    delete exporter;
    //}

    ///////////////////////////////////

    // Export Without Texture

    string name = "alduin";
    string file = "Models/FBX/" + name + ".fbx";
    ModelExporter* exporter;
    
    exporter = new ModelExporter(name, file);
    exporter->ExportMaterial();
    exporter->ExportMesh();
    delete exporter;


    //string name = "farmhouse2";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;

    //exporter = new ModelExporter(name, file);
    //exporter->ExportMaterial();
    //exporter->ExportMesh();
    //delete exporter;

    //string name = "dragonboneshield";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //string clipName;

    //exporter = new ModelExporter(name, file);
    //exporter->ExportMaterial();
    //exporter->ExportMesh();
    //delete exporter;

    //string name = "dragonbonegauntlets";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //string clipName;

    //exporter = new ModelExporter(name, file);
    //exporter->ExportMaterial();
    //exporter->ExportMesh();
    //delete exporter;

    //string name = "dragonbonecuirassplate";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //string clipName;

    //exporter = new ModelExporter(name, file);
    //exporter->ExportMaterial();
    //exporter->ExportMesh();
    //delete exporter;

    //string name = "male_dragonbone";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //string clipName;

    //exporter = new ModelExporter(name, file);
    //exporter->ExportMaterial();
    //exporter->ExportMesh();
    //delete exporter;

    //clipName = "male_1hm_equip";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;

    //clipName = "male_1hm_unequip";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;

    //clipName = "male_2hm_equip";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;

    //clipName = "male_2hm_unequip";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;

    //clipName = "male_bow_equip";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;

    //clipName = "male_bow_unequip";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;

   
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
