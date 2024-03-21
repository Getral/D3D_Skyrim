#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    string name = "ironbow";
    string file = "Models/FBX/" + name + ".fbx";
    ModelExporter* exporter;
    string clipName;
    
    exporter = new ModelExporter(name, file);
    exporter->ExportMaterial();
    exporter->ExportMesh();
    delete exporter;

    clipName = "iron_bow_idle";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;

    clipName = "iron_bow_draw";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;
    
    clipName = "iron_bow_draw_idle";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;
    
    clipName = "iron_bow_draw_release";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;


    string name2 = "ironquiver";
    string file2 = "Models/FBX/" + name2 + ".fbx";
    ModelExporter* exporter2;
    string clipName2;

    exporter2 = new ModelExporter(name2, file2);
    exporter2->ExportMaterial();
    exporter2->ExportMesh();
    delete exporter2;
    

    string name1 = "ebonybow";
    string file1 = "Models/FBX/" + name1 + ".fbx";
    ModelExporter* exporter1;
    string clipName1;
    
    exporter1 = new ModelExporter(name1, file1);
    exporter1->ExportMaterial();
    exporter1->ExportMesh();
    delete exporter1;    

    clipName1 = "ebony_bow_idle";
    file1 = "Models/Animations/" + name1 + "/" + clipName1 + ".fbx";
    exporter1 = new ModelExporter(name1, file1);
    exporter1->ExportClip(clipName1);
    delete exporter1;

    clipName1 = "ebony_bow_draw";
    file1 = "Models/Animations/" + name1 + "/" + clipName1 + ".fbx";
    exporter1 = new ModelExporter(name1, file1);
    exporter1->ExportClip(clipName1);
    delete exporter1;
    
    clipName1 = "ebony_bow_draw_idle";
    file1 = "Models/Animations/" + name1 + "/" + clipName1 + ".fbx";
    exporter1 = new ModelExporter(name1, file1);
    exporter1->ExportClip(clipName1);
    delete exporter1;
    
    clipName1 = "ebony_bow_release";
    file1 = "Models/Animations/" + name1 + "/" + clipName1 + ".fbx";
    exporter1 = new ModelExporter(name1, file1);
    exporter1->ExportClip(clipName1);
    delete exporter1;



    //string name = "shield";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //string clipName;
    //
    //exporter = new ModelExporter(name, file);
    //exporter->ExportMaterial();
    //exporter->ExportMesh();
    //delete exporter;


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





//알두인

//string name = "alduin";
//string file = "Models/FBX/" + name + ".fbx";
//ModelExporter* exporter;
//string clipName;
//
//exporter = new ModelExporter(name, file);
//exporter->ExportMaterial();
//exporter->ExportMesh();
//delete exporter;
//
//
//clipName = "alduin_aproach";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_ascend";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_backward";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_bite";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_bite_left";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_bite_right";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_bleedidle";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_climb";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_descend";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_exhale_breath";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_exhale_fireball";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_flight_forward";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_flight_hit";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_fly";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_forward";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_hover";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_idle";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_inhale";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_injured";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_pain";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_pain2";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_rotate_left";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_rotate_right";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_tailwhip";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_takeoff";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_timetravel";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_wingswip_left";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//
//clipName = "alduin_wingswip_right";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;


//플레이어(드래곤본 통짜)

//string name = "male_dragonbone";
//string file = "Models/FBX/" + name + ".fbx";
//ModelExporter* exporter;
//string clipName;
//
//exporter = new ModelExporter(name, file);
//exporter->ExportMaterial();
//exporter->ExportMesh();
//delete exporter;
//
//
//clipName = "male_1hm_idle";
//file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//exporter = new ModelExporter(name, file);
//exporter->ExportClip(clipName);
//delete exporter;
//

   
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
