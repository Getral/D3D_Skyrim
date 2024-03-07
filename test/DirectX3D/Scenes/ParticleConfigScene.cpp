#include "Framework.h"
#include "ParticleConfigScene.h"

ParticleConfigScene::ParticleConfigScene()
{
    // 구성할 파티클의 파일 이름 정하기 (여기서 값을 수정하고 파티클 만들기)
    wstring FILENAME = L"Textures/Effect/star.png";

    quad = new Quad(Vector2(1, 1));

    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");
    quad->GetMaterial()->SetDiffuseMap(FILENAME);
    
    instances.resize(particleCount);
    particleInfo.resize(particleCount);

    // 여기까지 파티클의 이미지와 기본 데이터 준비

    // 이어서 정점과 출력준비

    instanceBuffer = new VertexBuffer(instances.data(),
        sizeof(InstanceData), particleCount);

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    char path[128]; // C 문자열 준비 (128 = 윈도우가 절대 오류 없이 인지할 수 있는 최대 문자 길이 + 1)
    GetCurrentDirectoryA(sizeof(path), path); // 윈도우 함수로 경로명 불러오기
                        //GetCurrentDirectoryA : 경로명을 받아오는 기능
                        // 매개변수 : 1. 읽어올 분량, 2. 저장할 변수(의 이름)
    projectPath = path; //C++의 스트링 클래스는 문자열 복사를 통한 할당이 가능

    //경로명 준비를 이렇게 마친 후, 파티클을 시작
    Init();
}

ParticleConfigScene::~ParticleConfigScene()
{
    delete quad;
    delete instanceBuffer;
    FOR(2) delete blendState[i];
    FOR(2) delete depthState[i];
}

void ParticleConfigScene::Update()
{
    // 재생x 구성용 씬이라서 업데이트는 간단

    lifeSpan += DELTA; //주기 진행

    // 파티클을 업데이트
    UpdatePhysical();
    UpdateColor();
    quad->UpdateWorld();

    if (lifeSpan > data.duration)
    {
        Init(); //옵션에 상관없이 그냥 무조건 재시작 (확인, 구성용이라서)
    }
}

void ParticleConfigScene::PreRender()
{
}

void ParticleConfigScene::Render()
{
    instanceBuffer->Set(1);

    quad->SetRender();

    blendState[1]->SetState();
    depthState[1]->SetState();

    DC->DrawIndexedInstanced(6, drawCount, 0, 0, 0);

    // 다른 씬하고 같이 쓴다면 나중에 원상복구 추가할 것
    //blendState[0]->SetState();
    //depthState[0]->SetState();
}

void ParticleConfigScene::PostRender()
{
}

void ParticleConfigScene::GUIRender()
{
    // ImGUI의 디버그 패널을 이용해서 파티클 옵션을 제어

    ImGui::Text("Particle Editor"); //제목
    EditTexture(); //그림변경

    //옵션 제어
    ImGui::Checkbox("Loop", &data.isLoop);
    ImGui::Checkbox("Additice", &data.isAdditive);
    ImGui::Checkbox("Billboard", &data.isBillboard);
    ImGui::SliderInt("ParticleCount", (int*)&particleCount, 1, MAX_COUNT);
    ImGui::DragFloat("Duration", &data.duration, 0.1f, 10.0f);
    ImGui::ColorEdit4("StartColor", (float*)&data.startColor);
    ImGui::ColorEdit4("EndColor", (float*)&data.endColor);
    ImGui::SliderFloat3("MinVelocity", (float*)&data.minVelocity, -1, 1);
    ImGui::SliderFloat3("MaxVelocity", (float*)&data.maxVelocity, -1, 1);
    ImGui::SliderFloat3("MinAcceleration", (float*)&data.minAcceleration, -5, 5);
    ImGui::SliderFloat3("MaxAcceleration", (float*)&data.maxAcceleration, -5, 5);
    ImGui::SliderFloat3("MinStartScale", (float*)&data.minStartScale, 0, 5);
    ImGui::SliderFloat3("MaxStartScale", (float*)&data.maxStartScale, 0, 5);
    ImGui::SliderFloat3("MinEndScale", (float*)&data.minEndScale, 0, 5);
    ImGui::SliderFloat3("MaxEndScale", (float*)&data.maxEndScale, 0, 5);
    ImGui::SliderFloat("MinAngularVelocity", (float*)&data.minAngularVelocity, -10, 10);
    ImGui::SliderFloat("MaxAngularVelocity", (float*)&data.maxAngularVelocity, -10, 10);
    ImGui::SliderFloat("MinSpeed", (float*)&data.minSpeed, 0, data.maxSpeed); // 최소 속력이 최대 속력을 넘지는 못하게
    ImGui::SliderFloat("MaxSpeed", (float*)&data.maxSpeed, data.minSpeed, 100);
    ImGui::SliderFloat("MinStartTime", (float*)&data.minStartTime, 0, data.maxStartTime);
    ImGui::SliderFloat("MaxStartTime", (float*)&data.maxStartTime, data.minStartTime, data.duration); //아무리 지연돼도 파티클이 있어야 할 시간 내에는 나오게

    // 여기까지 수행되면 디버그 패널에 설정 옵션이 나오면서 설정에 의한 조작 가능

    SaveDialog(); //세이브
    ImGui::SameLine();
    LoadDialog(); //로드 (바로 옆에 출력)

    // SameLine : 바로 위 UI와 바로 아래 UI가 같은 줄에 나오게 하는 기능
}

void ParticleConfigScene::UpdatePhysical()
{
    drawCount = 0; 

    FOR(data.count)
    {
        if (lifeSpan < particleInfo[i].startTime) continue;

        particleInfo[i].velocity += particleInfo[i].acceleration * DELTA;
        particleInfo[i].transform.Pos() += particleInfo[i].velocity
            * particleInfo[i].speed * DELTA;

        particleInfo[i].transform.Rot().z += particleInfo[i].angularVelocity * DELTA;

        if (data.isBillboard)
        {
            particleInfo[i].transform.Rot().x = CAM->Rot().x;
            particleInfo[i].transform.Rot().y = CAM->Rot().y;
        }

        float t = (lifeSpan - particleInfo[i].startTime)
            / (data.duration - particleInfo[i].startTime);

        particleInfo[i].transform.Scale() =
            Lerp(particleInfo[i].startScale, particleInfo[i].endScale, t);

        particleInfo[i].transform.UpdateWorld(); 

        instances[drawCount++].transform =
            XMMatrixTranspose(particleInfo[i].transform.GetWorld());
    }

    instanceBuffer->Update(instances.data(), drawCount);
}

void ParticleConfigScene::UpdateColor()
{
    float t = lifeSpan / data.duration;

    Float4 color;
    color.x = Lerp(data.startColor.x, data.endColor.x, t); // R
    color.y = Lerp(data.startColor.y, data.endColor.y, t); // G
    color.z = Lerp(data.startColor.z, data.endColor.z, t); // B
    color.w = Lerp(data.startColor.w, data.endColor.w, t); // A

    quad->GetMaterial()->GetData().diffuse = color;
}

void ParticleConfigScene::Init()
{
    if (data.isAdditive) blendState[1]->Additive();
    else blendState[1]->Alpha(true);

    lifeSpan = 0;
    drawCount = 0;
    data.count = particleCount;

    instances.resize(data.count);
    particleInfo.resize(data.count);

    for (ParticleInfo& info : particleInfo)
    {
        info.transform.Pos() = {}; // 일단 대기

        //각 파티클의 실체 옵션 설정
        info.velocity = Random(data.minVelocity, data.maxVelocity);
        info.acceleration = Random(data.minAcceleration, data.maxAcceleration);
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.startScale = Random(data.minStartScale, data.maxStartScale);
        info.endScale = Random(data.minEndScale, data.maxEndScale);

        info.velocity.Normalize();
    }
}

void ParticleConfigScene::Save(string file)
{
    BinaryWriter* writer = new BinaryWriter(file);

    //파티클에 가장 필요한 것 : 어떤 그림의 파티클인가 (생성 때도 이미지를 썼으니까)
    writer->WString(quad->GetMaterial()->GetDiffuseMap()->GetFile());
    //파티클 데이터를 모조리 있는 그대로 파일에 집어넣기
    writer->Byte(&data, sizeof(ParticleData));

    delete writer;
}

void ParticleConfigScene::Load(string file)
{
    BinaryReader* reader = new BinaryReader(file);
    
    wstring textureFile = reader->WString(); // 저장된 파티클 파일 속에서 그림 파일 이름을 찾아
    quad->GetMaterial()->SetDiffuseMap(textureFile); // 그 그림 파일의 대상을 쿼드 디퓨즈맵에 할당

    ParticleData* particleData = new ParticleData(); // 파티클 데이터 만들기
    reader->Byte((void**)&particleData, sizeof(ParticleData)); // 바이트 데이터 그대로 덮어씌우기

    data = *particleData; //파티클 데이터의 값을 할당하기

    //혹시 파일 내에서 설정된 파티클 입자 개수가 달랐다면
    // 클래스에 설정을 반영하기 (+입자에는 클래스 상황을 반영하기)
    UINT temp = data.count;
    data.count = particleCount;
    particleCount = temp;

    //delete particleData; // 혹시 메모리에 여유가 없어지면 읽을 때 만든 파티클 데이터 할당 해제
    delete reader;
}

void ParticleConfigScene::EditTexture()
{
    // ImTextureID : 현재 처리되고 있는 텍스처의 데이터 (gui입장에서는 "이미지의 고유 데이터")
    ImTextureID textureID = quad->GetMaterial()->GetDiffuseMap()->GetSRV();
                            // = 이미지 데이터 처리후 셰이더에 넘기는 과정의 데이터

    if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
        // 받아온 이미지 데이터를 imgui 방식으로,
        // 50x50 크기로 보여주는 버튼을 그려주고, 이 버튼이 눌리면
    {
        DIALOG->OpenDialog("SelectTexture", "SelectTexture", ".png, .jpg, .tga", ".");
    }

    if (DIALOG->Display("SelectTexture"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName(); // 전체경로명
            file = file.substr(projectPath.size() + 1, file.size());
            
            //받아온 파일명을 2바이트 문자열로 바꾼 뒤, 디퓨즈맵 할당
            quad->GetMaterial()->SetDiffuseMap(ToWString(file));
        }
        DIALOG->Close();
    }

}

void ParticleConfigScene::SaveDialog()
{
    //디버그 패널에서 세이브 기능을 불러오고 작동

    if (ImGui::Button("Save")) // 버튼을 출력하고, 이 버튼을 만약 누르면 {} 수행
    {
        DIALOG->OpenDialog("Save", "Save", ".fx", ".");
        // Save라는 내부 키워드로 구분되고,
        // Save라는 제목으로 화면에 표기되는 파일 탐색 상자를 열어서
        // .fx라는 파일을, 프로젝트 위치로부터 찾는다 (폴더 이동은 가능)
    }

    if (DIALOG->Display("Save")) // 세이브 탐색 상자가 열린 동안
    {
        if (DIALOG->IsOk()) // 확인용 버튼을 출력시키고, 또 이 버튼이 눌리면
        {
            string file = DIALOG->GetFilePathName(); // 전체경로명
            file = file.substr(projectPath.size() + 1, file.size());
            // 폴더명이 끝나는 곳부터, 경로명이 끝나는 곳까지의 텍스트를 잘라낸다
            // = 파일명이 나온다

            Save(file); //나온 파일명을 이용해서 저장 함수 수행
        }

        DIALOG->Close(); //열린 동안에 용무가 끝나면 상자 닫기 (여기서 호출)
    }
}

void ParticleConfigScene::LoadDialog()
{
    //디버그 패널에서 세이브 기능을 불러오고 작동

    if (ImGui::Button("Load"))
    {
        DIALOG->OpenDialog("Load", "Load", ".fx", ".");
    }

    if (DIALOG->Display("Load"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName(); // 전체경로명
            file = file.substr(projectPath.size() + 1, file.size());

            Load(file);
        }
        DIALOG->Close();
    }
}
