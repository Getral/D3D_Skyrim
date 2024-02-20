#include "Framework.h"
#include "TerrainLOD.h"

TerrainLOD::TerrainLOD(wstring heightFile)
{
    //��Ƽ���� ����
    material->SetShader(L"TS/TerrainLOD.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    //���̴� �غ�
    hullShader = Shader::AddHS(L"TS/TerrainLOD.hlsl");
    domainShader = Shader::AddDS(L"TS/TerrainLOD.hlsl");

    //���� �� �غ�
    heightMap = Texture::Add(heightFile);

    //�����غ�
    terrainBuffer = new FloatValueBuffer();
    heightBuffer = new FloatValueBuffer();

    //���ۿ� �̸� �ǹ̸� ���� ��ġ�� �־��ֱ�
    // -> �������ۿ��� LOD ������ �� �Ÿ��� �ֱ�
    // -> + ���� ���ۿ� LOD�� ���� ���� ���� ���� �����ϱ� 
    // -> ���� (�籸��) ���ۿ��� ����� �ֱ�

    terrainBuffer->Get()[0] = 1.0f;        // �����Ÿ� �ּ� (���⼭ ���ι��� �ִ�)
    terrainBuffer->Get()[1] = 1000.0f;     // �����Ÿ� �ִ� (���⼭ ���ι��� �ּ�)

    terrainBuffer->Get()[2] = 1.0f;        // ���� ���� �ּ� (���⼭ ���� �� �ִ�)
    terrainBuffer->Get()[3] = 64.0f;       // ���� ���� �ִ� (���⼭ ���� �� �ּ�)

    heightBuffer->Get()[0] = 20.0f;        // ���

    // * �� ������ ���� �������� ������ ���� �ƴմϴ�. (�������� ���ظ� ���� ���� ������ ����)
    // -> �� ������θ� LOD ����� ��Ȯ�� ī�޶� �ٷ� �տ������� ���۵ȴ� (������ 99%�� ���� ���� ��ħ)
    //    �׸��� �Ÿ��� 1000�� �Ǿ ���� ������ �ּ� ����
    // -> ���ι��簡 �ּ� 1/64���� : ����� ���ٱ⿡�� �ָ�, ���ٱ⿡�� �ָ�
    //    = ������ ���°� �޶����� ���� �ð�ȭ�ؼ� ���� �߿� ���� ���� �˾ƺ��� ���� ����

    // �޽� �����
    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

TerrainLOD::~TerrainLOD()
{
    delete terrainBuffer;
    delete heightBuffer;

    delete mesh;
    
}

void TerrainLOD::Render()
{
    //���ӿ�����Ʈ�� ���� ���� ���� (������Ʈ����)
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    //������ ���� ���̴��� �ְ� ����� �غ��ϱ�
    terrainBuffer->SetHS(10); // �� ���̴����� ���� �Ϻ� ���� �д��ؼ� ����
    heightBuffer->SetDS(10); // ������ ���̴��� ���� ��� �ÿ� ���� ��� �д�

    heightMap->DSSet(); // �ؽ�ó�� �ؽ�ó�� �д��ؾ� �� ���ǹ� ���� ���� ����

    //���� �غ�
    material->Set();
    hullShader->Set();
    domainShader->Set();

    //�׸��� (���� ����)
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
            //��� �ɼ� : ��Ģ�� ����, �ڵ�� ������ 4���� ������ ���� ������ ����� ����

    //����Ϳ� ���̴��� �����ϸ鼭 ���
    DC->HSSetShader(nullptr, nullptr, 0); // ����
    DC->DSSetShader(nullptr, nullptr, 0); // ���
}

void TerrainLOD::GUIRender()
{
    //�� �� �ɼ�
    ImGui::Text("Terrain LOD Option");
    ImGui::DragFloat("MinDistance", &terrainBuffer->Get()[0]);
    ImGui::DragFloat("MaxDistance", &terrainBuffer->Get()[1]);
    ImGui::DragFloat("MinQuality", &terrainBuffer->Get()[2]);
    ImGui::DragFloat("MaxQuality", &terrainBuffer->Get()[3]);
    ImGui::DragFloat("Height", &heightBuffer->Get()[0]);

    GameObject::GUIRender();
    ImGui::Text("width : %d", width);
    ImGui::Text("height : %d", height);
}

void TerrainLOD::MakeMesh()
{
    // �⺻ �޽� (��ü ũ��� ���� ����)

    // ��ü ������ ũ��
    width = heightMap->GetSize().x;
    height = heightMap->GetSize().y;

    // ��ü ũ�⿡�� ȣ��Ǵ� �� UV ����
    // + �� �������� ���� ���µ� �����̳� ���� ����

    cellUV = { 1.0f / width, 1.0f / height };
            // ���� �ܼ��� ���������� UV : �ؽ�ó�� ���� ���η� �ɰ� ����ŭ
            // -> �� �Ŀ��� ���� ������ ���� ���� : ��Ʈ

    // �� ������ ������ �� ����, ���ε� ���
    // -> ����� �� = ���簢���̹Ƿ�, ������ ���簢������
    patchWidth = ((width - 1) / cellsPerPatch) + 1;
    patchHeight = ((height - 1) / cellsPerPatch) + 1;
                // �� �� ���� �ǹ� : �� ������ cellsPerPatch��ŭ �߸� ���簢���̰�
                // ���� �� ���� �ȿ��� cell ��ŭ�� �ؽ�ó �ȼ��� �� ��

    // �̷��� ���� ���� ����....�� ���� �޽��� �����

    //���� ������
    vector<VertexType>& vertices = mesh->GetVertices();
    vertices.resize(patchWidth * patchHeight); // ���� ���� ���� ���� �ʱ�ȭ

    //���� Ž�� ����� ���� �����
    float halfWidth = width * cellSpacing * 0.5f; //���ο� ������ ���ϰ� ������ ���� ��
    float halfHeight = height * cellSpacing * 0.5f;

    // �ӽ� ����, ���� �����
    float tempWidth = width * cellSpacing / patchWidth; // ��üũ�� �� ������ �����ϴ� ���ذ�
    float tempHeight = height * cellSpacing / patchHeight;

    // �� ���� ������ �����ؾ� �� �ؽ�ó UV�� ������
    float du = 1.0f / patchWidth; // float���� Ȯ���� �ϱ� ���ؼ� 1.0f�� �� �����ָ� ����
    float dv = 1.0f / patchHeight;

    //������ ������ ���ư��鼭 ���� ���� ����
    for (UINT z = 0; z < patchHeight; ++z)
    {
        float tempZ = halfHeight - z * tempHeight; // ���� ���� �� z ��ǥ ����
        for (UINT x = 0; x < patchWidth; ++x)
        {
            float tempX = -halfHeight + x * tempWidth; // ���� ���� �� x ��ǥ ����

            //���� ���� �� ������ �ε����� ����
            UINT index = patchWidth * z + x; //�׳� �ؽ�ó/������ ���� x, z ��ǥ

            //�� �Ŀ��� �����, index�� ���̴� x,z�� tempX, tempZ��
            // �ݺ��� ���� �ø��� �������� �ʰ� �ٲ�� ���� �̿��ؼ�

            // ������ �ε���(������ �ö󰡴� ������)��, ������ �ִ� temp��ǥ�� ����
            vertices[index].pos = { tempX, 0, tempZ }; // �ε����� �ݺ��� ���� �ø��� ������ +1
            vertices[index].uv = { x * du, z * dv };   // �׷��� temp�� �ٸ� ���� �ִ�...
        }

    }

    // ������� ���� ���� ������ ������
    // -> ��¿� ���� �ε��� �ʿ�

    vector<UINT>& indices = mesh->GetIndices();
    indices.reserve((patchWidth - 1)* (patchHeight - 1) * 4); // 

    for (UINT z = 0; z < patchHeight - 1; ++z)
    {
        for (UINT x = 0; x < patchWidth - 1; ++x)
        {
            // ���簢���� ������ �� �ִ� ���� 4�� 1��Ʈ

            indices.push_back(patchWidth * (z + 0) + (x + 0)); // 0
            indices.push_back(patchWidth * (z + 0) + (x + 1)); // 1
            indices.push_back(patchWidth * (z + 1) + (x + 0)); // 2
            indices.push_back(patchWidth * (z + 1) + (x + 1)); // 3
        }
    }

}
