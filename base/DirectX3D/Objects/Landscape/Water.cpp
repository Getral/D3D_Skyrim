#include "Framework.h"

Water::Water(wstring normalFile, float width, float height)
    : size(width, height)
{
    SetTag("Water");
    material->SetShader(L"Environment/Water.hlsl");

    // �Ϸ��Ӱ� �ݻ� �����
    reflection = new Reflection(this); // ���� ���� ��(=��) �ڽ��� ������ ���, �ݻ��� ��ü��
    refraction = new Refraction(normalFile);

    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Alpha(true);

    mesh = new Mesh<VertexUV>();
    MakeMesh();
    mesh->CreateMesh();
}

Water::~Water()
{
    FOR(2) delete blendState[i];

    delete reflection;
    delete refraction;

    delete mesh;
}

void Water::Update()
{
    refraction->Update();
    reflection->Update();

    UpdateWorld(); //�� �ڽŵ� ������Ʈ
}

void Water::Render()
{
    SetRender();

    reflection->SetRender();
    refraction->SetRender();

    //ȥ������ ���� ���� �� ���� ����
    blendState[1]->SetState();
    mesh->Draw();

    blendState[0]->SetState(); //���󺹱�
}

void Water::GUIRender()
{
    Transform::GUIRender();
    refraction->GUIRender(); // ���� �ɼ� ����ϰ� Ȱ��
}

void Water::SetRefraction()
{
    refraction->SetRefraction();
}

void Water::SetReflection()
{
    reflection->SetReflection();
}

void Water::MakeMesh()
{
    // �켱 ���� ȭ��ȿ���� ���� ����, �޽��� ����� �ܼ�ȭ�ؼ� ����

    float left = -size.x * 0.5f;
    float right = size.x * 0.5f;
    float top = size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    //���� ������
    vector<VertexUV>& vertices = mesh->GetVertices();

    vertices.emplace_back(left, 0, top, 0, 0); // x, y, z, u, v ������ �ప �ֱ�
    vertices.emplace_back(right, 0, top, 1, 0);
    vertices.emplace_back(left, 0, bottom, 0, 1);
    vertices.emplace_back(right, 0, bottom, 1, 1);

    //���� �ε���
    vector<UINT>& indices = mesh->GetIndices();
    indices = {
        0, 1, 2, 2, 1, 3 //=����
    };
}
