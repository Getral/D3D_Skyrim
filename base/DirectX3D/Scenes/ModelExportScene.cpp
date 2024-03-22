#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    // Export With Texture
    // 
    //vector<string> modelName =
    //{
    //    "rock_large1", "rock_large2", "rock_large3", "rock_large4", "rock_large5",
    //    "rock_medium1", "rock_medium2", "rock_medium3", "rock_medium4", "tree",
    //    
    //    //Armor
    //    "dragonboots", "dragoncuirass", "dragongauntlets", "dragonhelmet", "dragonshield",
    //    "ironboots", "ironcuirass", "irongauntlets", "ironhelmet", "ironshield",
    //
    //    //Weapon
    //    "ebonybattleaxe", "ebonybow", "ebonyclaymore", "ebonydagger", "ebonylongsword", "ebonymace", "ebonyquiver", "ebonywaraxe", "ebonywarhammer", "ebonyarrow",
    //    "ironbattleaxe", "ironbow", "ironclaymore", "irondagger", "ironlongsword", "ironmace", "ironquiver", "ironwaraxe", "ironwarhammer", "ironarrow"
    //};
    //
    //vector<wstring> textures =
    //{
    //    L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01",
    //    L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/rocksgrass01", L"Landscape/tree02",
    //    
    //    //Armor
    //    // Dragong
    //    L"Model/Armor/dragonboots", L"Model/Armor/dragoncuirass", L"Model/Armor/dragongauntlets", L"Model/Armor/dragonhelmet", L"Model/Armor/dragonshield",
    //    // Iron
    //    L"Model/Armor/ironboots", L"Model/Armor/ironcuirass", L"Model/Armor/irongauntlets", L"Model/Armor/ironhelmet", L"Model/Armor/ironshield",
    //
    //    //Weapon
    //    // Ebony
    //    L"Model/Weapon/ebonybattleaxe", L"Model/Weapon/ebonybow", L"Model/Weapon/ebonyclaymore", L"Model/Weapon/ebonydagger", L"Model/Weapon/ebonylongsword", 
    //    L"Model/Weapon/ebonymace", L"Model/Weapon/ebonyquiver", L"Model/Weapon/ebonywaraxe", L"Model/Weapon/ebonywarhammer",  L"Model/Weapon/ebonyarrow",
    //    // Iron
    //    L"Model/Weapon/ironarrow", L"Model/Weapon/ironbattleaxe", L"Model/Weapon/ironbow", L"Model/Weapon/ironclaymore", L"Model/Weapon/irondagger",
    //    L"Model/Weapon/ironlongsword", L"Model/Weapon/ironmace", L"Model/Weapon/ironquiver", L"Model/Weapon/ironwaraxe", L"Model/Weapon/ironwarhammer"
    //};
    //
    //
    //
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

    string name = "farmhouse2";
    string file = "Models/FBX/" + name + ".fbx";
    ModelExporter* exporter;
    
    exporter = new ModelExporter(name, file);
    exporter->ExportMaterial();
    exporter->ExportMesh();
    delete exporter;


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
