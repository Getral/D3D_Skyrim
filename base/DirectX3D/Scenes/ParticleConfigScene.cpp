#include "Framework.h"
#include "ParticleConfigScene.h"

ParticleConfigScene::ParticleConfigScene()
{
    // ������ ��ƼŬ�� ���� �̸� ���ϱ� (���⼭ ���� �����ϰ� ��ƼŬ �����)
    wstring FILENAME = L"Textures/Effect/star.png";

    quad = new Quad(Vector2(1, 1));

    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");
    quad->GetMaterial()->SetDiffuseMap(FILENAME);
    
    instances.resize(particleCount);
    particleInfo.resize(particleCount);

    // ������� ��ƼŬ�� �̹����� �⺻ ������ �غ�

    // �̾ ������ ����غ�

    instanceBuffer = new VertexBuffer(instances.data(),
        sizeof(InstanceData), particleCount);

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    char path[128]; // C ���ڿ� �غ� (128 = �����찡 ���� ���� ���� ������ �� �ִ� �ִ� ���� ���� + 1)
    GetCurrentDirectoryA(sizeof(path), path); // ������ �Լ��� ��θ� �ҷ�����
                        //GetCurrentDirectoryA : ��θ��� �޾ƿ��� ���
                        // �Ű����� : 1. �о�� �з�, 2. ������ ����(�� �̸�)
    projectPath = path; //C++�� ��Ʈ�� Ŭ������ ���ڿ� ���縦 ���� �Ҵ��� ����

    //��θ� �غ� �̷��� ��ģ ��, ��ƼŬ�� ����
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
    // ���x ������ ���̶� ������Ʈ�� ����

    lifeSpan += DELTA; //�ֱ� ����

    // ��ƼŬ�� ������Ʈ
    UpdatePhysical();
    UpdateColor();
    quad->UpdateWorld();

    if (lifeSpan > data.duration)
    {
        Init(); //�ɼǿ� ������� �׳� ������ ����� (Ȯ��, �������̶�)
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

    // �ٸ� ���ϰ� ���� ���ٸ� ���߿� ���󺹱� �߰��� ��
    //blendState[0]->SetState();
    //depthState[0]->SetState();
}

void ParticleConfigScene::PostRender()
{
}

void ParticleConfigScene::GUIRender()
{
    // ImGUI�� ����� �г��� �̿��ؼ� ��ƼŬ �ɼ��� ����

    ImGui::Text("Particle Editor"); //����
    EditTexture(); //�׸�����

    //�ɼ� ����
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
    ImGui::SliderFloat("MinSpeed", (float*)&data.minSpeed, 0, data.maxSpeed); // �ּ� �ӷ��� �ִ� �ӷ��� ������ ���ϰ�
    ImGui::SliderFloat("MaxSpeed", (float*)&data.maxSpeed, data.minSpeed, 100);
    ImGui::SliderFloat("MinStartTime", (float*)&data.minStartTime, 0, data.maxStartTime);
    ImGui::SliderFloat("MaxStartTime", (float*)&data.maxStartTime, data.minStartTime, data.duration); //�ƹ��� �����ŵ� ��ƼŬ�� �־�� �� �ð� ������ ������

    // ������� ����Ǹ� ����� �гο� ���� �ɼ��� �����鼭 ������ ���� ���� ����

    SaveDialog(); //���̺�
    ImGui::SameLine();
    LoadDialog(); //�ε� (�ٷ� ���� ���)

    // SameLine : �ٷ� �� UI�� �ٷ� �Ʒ� UI�� ���� �ٿ� ������ �ϴ� ���
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
        info.transform.Pos() = {}; // �ϴ� ���

        //�� ��ƼŬ�� ��ü �ɼ� ����
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

    //��ƼŬ�� ���� �ʿ��� �� : � �׸��� ��ƼŬ�ΰ� (���� ���� �̹����� �����ϱ�)
    writer->WString(quad->GetMaterial()->GetDiffuseMap()->GetFile());
    //��ƼŬ �����͸� ������ �ִ� �״�� ���Ͽ� ����ֱ�
    writer->Byte(&data, sizeof(ParticleData));

    delete writer;
}

void ParticleConfigScene::Load(string file)
{
    BinaryReader* reader = new BinaryReader(file);
    
    wstring textureFile = reader->WString(); // ����� ��ƼŬ ���� �ӿ��� �׸� ���� �̸��� ã��
    quad->GetMaterial()->SetDiffuseMap(textureFile); // �� �׸� ������ ����� ���� ��ǻ��ʿ� �Ҵ�

    ParticleData* particleData = new ParticleData(); // ��ƼŬ ������ �����
    reader->Byte((void**)&particleData, sizeof(ParticleData)); // ����Ʈ ������ �״�� ������

    data = *particleData; //��ƼŬ �������� ���� �Ҵ��ϱ�

    //Ȥ�� ���� ������ ������ ��ƼŬ ���� ������ �޶��ٸ�
    // Ŭ������ ������ �ݿ��ϱ� (+���ڿ��� Ŭ���� ��Ȳ�� �ݿ��ϱ�)
    UINT temp = data.count;
    data.count = particleCount;
    particleCount = temp;

    //delete particleData; // Ȥ�� �޸𸮿� ������ �������� ���� �� ���� ��ƼŬ ������ �Ҵ� ����
    delete reader;
}

void ParticleConfigScene::EditTexture()
{
    // ImTextureID : ���� ó���ǰ� �ִ� �ؽ�ó�� ������ (gui���忡���� "�̹����� ���� ������")
    ImTextureID textureID = quad->GetMaterial()->GetDiffuseMap()->GetSRV();
                            // = �̹��� ������ ó���� ���̴��� �ѱ�� ������ ������

    if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
        // �޾ƿ� �̹��� �����͸� imgui �������,
        // 50x50 ũ��� �����ִ� ��ư�� �׷��ְ�, �� ��ư�� ������
    {
        DIALOG->OpenDialog("SelectTexture", "SelectTexture", ".png, .jpg, .tga", ".");
    }

    if (DIALOG->Display("SelectTexture"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName(); // ��ü��θ�
            file = file.substr(projectPath.size() + 1, file.size());
            
            //�޾ƿ� ���ϸ��� 2����Ʈ ���ڿ��� �ٲ� ��, ��ǻ��� �Ҵ�
            quad->GetMaterial()->SetDiffuseMap(ToWString(file));
        }
        DIALOG->Close();
    }

}

void ParticleConfigScene::SaveDialog()
{
    //����� �гο��� ���̺� ����� �ҷ����� �۵�

    if (ImGui::Button("Save")) // ��ư�� ����ϰ�, �� ��ư�� ���� ������ {} ����
    {
        DIALOG->OpenDialog("Save", "Save", ".fx", ".");
        // Save��� ���� Ű����� ���еǰ�,
        // Save��� �������� ȭ�鿡 ǥ��Ǵ� ���� Ž�� ���ڸ� ���
        // .fx��� ������, ������Ʈ ��ġ�κ��� ã�´� (���� �̵��� ����)
    }

    if (DIALOG->Display("Save")) // ���̺� Ž�� ���ڰ� ���� ����
    {
        if (DIALOG->IsOk()) // Ȯ�ο� ��ư�� ��½�Ű��, �� �� ��ư�� ������
        {
            string file = DIALOG->GetFilePathName(); // ��ü��θ�
            file = file.substr(projectPath.size() + 1, file.size());
            // �������� ������ ������, ��θ��� ������ �������� �ؽ�Ʈ�� �߶󳽴�
            // = ���ϸ��� ���´�

            Save(file); //���� ���ϸ��� �̿��ؼ� ���� �Լ� ����
        }

        DIALOG->Close(); //���� ���ȿ� �빫�� ������ ���� �ݱ� (���⼭ ȣ��)
    }
}

void ParticleConfigScene::LoadDialog()
{
    //����� �гο��� ���̺� ����� �ҷ����� �۵�

    if (ImGui::Button("Load"))
    {
        DIALOG->OpenDialog("Load", "Load", ".fx", ".");
    }

    if (DIALOG->Display("Load"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName(); // ��ü��θ�
            file = file.substr(projectPath.size() + 1, file.size());

            Load(file);
        }
        DIALOG->Close();
    }
}
