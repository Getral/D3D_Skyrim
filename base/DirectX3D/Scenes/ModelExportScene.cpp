#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    string name = "ebonybattleaxe";
    string file = "Models/FBX/" + name + ".fbx";
    ModelExporter* exporter;
    string clipName;
    
    exporter = new ModelExporter(name, file);
    exporter->ExportMaterial();
    exporter->ExportMesh();
    delete exporter;


    string name1 = "male_dragonbone";
    string file1 = "Models/FBX/" + name1 + ".fbx";
    ModelExporter* exporter1;
    string clipName1;

    exporter1 = new ModelExporter(name1, file1);
    exporter1->ExportMaterial();
    exporter1->ExportMesh();
    delete exporter1;


    string name2 = "male_dragonbone";
    string file2 = "Models/FBX/" + name2 + ".fbx";
    ModelExporter* exporter2;
    string clipName2;

    exporter2 = new ModelExporter(name2, file2);
    exporter2->ExportMaterial();
    exporter2->ExportMesh();
    delete exporter2;


    //string name = "farmhouse";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //string clipName;
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
