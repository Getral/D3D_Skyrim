#include "Framework.h"

Spark::Spark(wstring imageFile, bool isAdditive)
{
    //material->SetShader(L"Basic/Texture.hlsl"); //�ؽ�ó�� �ֿ켱�� ��
    //material->SetShader(L"Effect/Particle.hlsl"); // ���� ���̴�
    material->SetShader(L"Geometry/Spark.hlsl"); //������Ʈ�� ���̴� ���� ����ũ ���̴�

    material->SetDiffuseMap(imageFile);

    geometryShader = Shader::AddGS(L"Geometry/Spark.hlsl"); //������Ʈ�� ���̴� ����

    buffer = new FloatValueBuffer();
    startColorBuffer = new ColorBuffer();
    endColorBuffer = new ColorBuffer();

    if (isAdditive) blendState[1]->Additive(); // ȥ�� ���� ������ ��� ��»��¿� �ݿ�

    Create(); // ���� �� �ؽ�ó ���� �����
}

Spark::~Spark()
{
    delete buffer;
    delete startColorBuffer;
    delete endColorBuffer;
}

void Spark::Update()
{
    if (!isActive) return;

    buffer->Get()[0] += DELTA; // �Ҽ� ���ۿ� ����� ������ 0���� ��������ð� ���ϱ�

    if (buffer->Get()[0] > buffer->Get()[1]) Stop();
                            //�Ҽ����� 0���� 1���� ���ؼ� 0���� �� ũ�� ����Ʈ ����
                            // = 0���� ����ð�, 1���� ���ؽð�
}

void Spark::Render()
{
    //���� �Ҽ����۷� ������ �����ʹ� �Լ�ó�� �Ἥ ����

    buffer->SetVS(10); // ���� ������ �Ű������� �༭ ���ǹ��� ���̴� �ȿ��� �޼�
    buffer->SetPS(10); // * �� ���� 10�ΰ�? : ������ ������ ����, �׳� �� ���ڰ� �����ϴ�
                       // ���� 0~2 ������ ȭ�� ��¿��� ���ϱ�, 10 ������ ������ ħ������ �ʴ´�

    startColorBuffer->SetPS(11);
    endColorBuffer->SetPS(12);
                        // �� ���� �� 11�̰� 12�ΰ�? -> 10���� ������ �� ���̴��� ����� �����
                        //                             ���� ���� �;

    Particle::Render(); //�θ� �Լ� ���� (=����)
}

void Spark::GUIRender()
{
    ImGui::Text("Spark Option");
    ImGui::SliderInt("ParticleCount", (int*)&particleCount, 1, MAX_COUNT);

    ImGui::SliderFloat("Duration", &buffer->Get()[1], 0.0f, 10.0f); //���ӽð�
    ImGui::SliderFloat("MinRadius", &minRadius, 1.0f, maxRadius);   //�ּ� �ݰ�
    ImGui::SliderFloat("MaxRadius", &maxRadius, minRadius, 50.0f);  //�ִ� �ݰ�
    ImGui::SliderFloat("MinSize", &minSize, 0.1f, maxSize);         //�ּ� ũ�� (����)
    ImGui::SliderFloat("MaxSize", &maxSize, minSize, 10.0f);        //�ִ� ũ�� (����)

    ImGui::ColorEdit4("StartColor", (float*)&startColorBuffer->Get());  // ���۽� ����
    ImGui::ColorEdit4("EndColor", (float*)&endColorBuffer->Get());    // ����� ����
}

void Spark::Play(Vector3 pos)
{
    buffer->Get()[0] = 0; //����� �ð� ����
    Particle::Play(pos); //�Ű������� �����ؼ� �θ� �Լ� ����

    UpdateParticle();      //��ƼŬ (����) ������Ʈ ��
    vertexBuffer->Update(vertices.data(), particleCount); //������Ʈ�� ���ۿ��� �ݿ�
}

void Spark::Create()
{
    vertices.resize(MAX_COUNT); // �޸𸮰� ���ϰ� �������� �ʵ��� �ִ� ����
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexParticle), MAX_COUNT);

    //particleCount = MAX_COUNT; //���� ��ƼŬ ���� ����
    particleCount = 500; //�������� ���� �ٲ��ָ� ���� ���� ���� ����

    //���� �ð� ����
    buffer->Get()[1] = 1.0f; //�ٸ� ������ �޾ƿ��ų�, ���� �Է��ϰų�
}

void Spark::UpdateParticle()
{
    //��� ���ڸ� �ݺ������� ����
    FOR(particleCount)
    {
        vertices[i].position = position;

        float size = Random(minSize, maxSize);
        vertices[i].size = { size, size };

        float radius = Random(minRadius, maxRadius); //�ݰ���

        Float3 rot; //������
        rot.x = Random(0.0f, XM_2PI); // XM_2PI : ȣ���� ����, "�ݰ�x������"�� 2�� = 360��
        rot.y = Random(0.0f, XM_2PI);
        rot.z = Random(0.0f, XM_2PI);
        // -> 3���� 360�� ��������

        //�ӷ� ���� �����
        Vector3 velocity = Vector3(0, 0, radius); //�ݰ游�� �ӷ��� "��"����

        //������ ���� �ݰ�-����-�ӷ±������� "�ӵ�"�� ����� (=����� ���� ��� ���� ����)
        Matrix matRot = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z); // ����� ũ�⸦ ���� �������� �����
                        // XMMatrix~~ : ���͸� ũ�⸦ ���� �������� ����� DX ���� �Լ�
                        // ~~~RollPitchYaw : Z��, X��, Y�� ȸ���� �ݿ��ϴ� ��� ȸ��
        XMStoreFloat3(&vertices[i].velocity, XMVector3TransformCoord(velocity, matRot));
                    // XMStoreFloat3 : ��İ� ���� ������ ���ο� ���� ������ �ٲ㼭 ����ִ� �Լ�
                    // XMVector3TransformCoord : ���Ϳ�(�ӷ±���) �������(����� ũ�Ⱑ �ִ� ����)�� ���ļ� �� ���ͷ� �������ִ� �Լ�
                    // -> XMVector3TransformCoord ������ ����� &vertices[i].velocity �����Ϳ� ����ش�
        
        // �� �������� �� ������ ���� ������ (Ȥ�� ���� ƽ��) ���� �� ���� ����
    }
}
