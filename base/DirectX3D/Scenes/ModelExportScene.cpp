#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    // Export With Texture
    // 
    vector<string> modelName =
    {
        "rock_large1", "rock_large2", "rock_large3", "rock_large4", "rock_large5",
        "rock_medium1", "rock_medium2", "rock_medium3", "rock_medium4", "tree", "chest",
        "hp_potion", "sp_potion", "coin"
    };
    
    vector<wstring> textures =
    {
        L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01",
        L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/tree02",
        L"Model/Chest/chest", L"Model/Potion/genericpotion", L"Model/Potion/genericpotion", L"Model/Misc/coin"
    };

    

    FOR(modelName.size())
    {
        string file = "Models/FBX/" + modelName[i] + ".fbx";
        wstring textureFile = L"Textures/" + textures[i] + L".png";
        ModelExporter* exporter;
        exporter = new ModelExporter(modelName[i], file);
        exporter->ExportMaterial(textureFile);
        exporter->ExportMesh();
        delete exporter;
    }

    ///////////////////////////////////

    // Export Without Texture

    //string name = "tree";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //
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
