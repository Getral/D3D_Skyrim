#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
    //A, B, C ������� ������ ����
    //trees.reserve(COUNT);
    //
    //FOR(COUNT)
    //{
    //    //���� ũ�� ����2�� �����
    //    Vector2 size;
    //    size.x = Random(2.0f, 10.0f);
    //    size.y = Random(2.0f, 10.0f);
    //
    //    Quad* tree = new Quad(size); // ����� ũ��� �� �簢������ �����
    //    tree->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Tree.png"); //��ǻ��� ������
    //    
    //    //��ġ �������� �ٲٱ�
    //    tree->Pos().x = Random(0.0f, 50.0f);
    //    tree->Pos().z = Random(0.0f, 50.0f);
    //    tree->Pos().y = 0;
    //
    //    trees.push_back(tree);
    //
    //    //ĵ���̿� Ʈ�������� ���� �غ�
    //    Transform* transform = new Transform();
    //    transform->Pos() = tree->Pos();
    //    origins.push_back(transform);
    //}
    //FOR(2) blendState[i] = new BlendState();
    //blendState[1]->AlphaToCoverage(true);

    // D : ������Ʈ�� ���̴��� Ȱ���� ������ ������ ������

    //�׸� �����͸� ó������ �����Ѵ�
    //material = new Material(L"Basic/Texture.hlsl"); // �ؽ�ó ��ü�� ����� �ǵ��� �⺻ ���̴�
    material = new Material(L"Geometry/Billboard.hlsl"); //���� ������ �������� �ʰ� ���� ������ ����ϴ� ���� ���̴�
    material->SetDiffuseMap(L"Textures/Landscape/Tree.png"); //����

    //�� ���� ������Ʈ�� ���̴� ����
    geometryShader = Shader::AddGS(L"Geometry/Billboard.hlsl"); // ������� ���� ���̴� �غ�

    //* ���� �簢��(����) ������ ����

    //�簢�� ��� ������ ���� ��Ƽ���� �����͸� �״�� ���� ���� ���� ��ġ�� ���Ѵ�
    //�� ��ġ�� �������� ��� (������ ��ǻ�� ���忡���� �̸��̾� ��·�� �Ȱ��� ����+UV)

    vertices.resize(COUNT);
    FOR(COUNT)
    {
        //���⼭�� ������
        vertices[i].pos.x = Random(0.0f, 30.0f);
        vertices[i].pos.z = Random(0.0f, 30.0f);
        vertices[i].pos.y = 0;

        //���⼭�� �׸��� ũ��
        vertices[i].uv.x = Random(1.0f, 10.0f);
        vertices[i].uv.y = Random(1.0f, 10.0f);
    }
    //������ ���� ���� ���͸� �������� �� ����
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), COUNT);

    //��»��� ����
    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    
    // ȥ�� ������Ʈ�� ����� �ɼ�
    //blendState[1]->Alpha(true); //�̹��� ���� ������ ������� ������ ���� ����
    blendState[1]->AlphaToCoverage(true); //����� ���� + ���� ó���� ������ ���� ����

    // ���� ������Ʈ�� ����ũ �ɼ�
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);  // �� ������
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // �� ������
}

BillboardScene::~BillboardScene()
{
    for (Quad* tree : trees)
        delete tree;

    for (Transform* origin : origins)
        delete origin;

    FOR(2) delete blendState[i];
    FOR(2) delete depthState[i];

    delete material;
    delete vertexBuffer;
}

void BillboardScene::Update()
{
    //�̹����� ������� �����ϴ� ���

    //....�߿���, ���� ���� ���

    //���͸� �̿��� �ؽ�ó ���� ����
    //for (Quad* tree : trees)
    //{
    //    //�ƹ�ư �ؽ�ó�� ī�޶� ���� �׸�
    //    Vector3 dir = tree->Pos() - CAM->Pos(); //ī�޶� ������ ���� �����
    //    tree->Rot().y = atan2(dir.x, dir.z); //������ ��ź��Ʈ ����. ������ xy = DX������ xz
    //    tree->UpdateWorld(); //������ �ٲ� ������ �簢�� ���� ������Ʈ
    //}

    ////�ؽ�ó�� ī�޶� ���� ����ȭ
    //for (Quad* tree : trees)
    //{
    //    tree->Rot().x = CAM->Rot().x;
    //    tree->Rot().y = CAM->Rot().y;
    //    tree->UpdateWorld();
    //}

    //ĵ����
    //for (Quad* tree : trees)
    //{
    //    //������ ������ ��ġ�ϴ� Ʈ������(����) ã��
    //    int index = find(trees.begin(), trees.end(), tree) - trees.begin();
    //    //find : ���� ���� �Լ�. �Ű������� ã�� ������ ����� �ָ� ��� ��ġ�� ���� �ݺ��� ��ȯ
    //    //�ݺ��� ��� Ư¡ : �ݺ��ڳ����� ����ó�� ��� ����. �ݺ��� �ڽ��� ���� ���� (iter++)
    //    // -> find�� ����� ������ begin()�� ���� ��ġ �������� 0�� �� ��ó�� ���� ���� ����
    //    Transform* point = origins.at(index); //������ ���� ��ġ�� ��ϵ� Ʈ������
    //
    //    Vector3 pos = point->Pos();
    //    tree->Pos() = CAM->WorldToScreen(pos);
    //    float scale = 100 / (tree->Pos() - CAM->Pos()).Length();
    //    scale = Clamp(10.0f, 10.0f, scale);
    //    tree->Scale() = { scale, scale, scale };
    //    tree->UpdateWorld();
    //}
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
    //for (Quad* tree : trees)
    //    tree->Render();

    // (��� ��¿� �����ߴ� ��ó��) �̹����� ����󿡼� ���� ���

    // ���� + ����� + ����ũ �ɼ� ���� ���� ����
    blendState[1]->SetState();
    depthState[1]->SetState();

    //vertexBuffer->Set(); // �⺻ ��´�� �Լ�
    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
    // D3D_PRIMITIVE_TOPOLOGY_POINTLIST : DX���� �ִ� ���� ����� ���� �ɼ� �� �ϳ�
    //                                    TRIANGULARLIST = �� 3���� ��� �ﰢ�� ���� ���
    //                                    LINELIST = �� 2���� ��� ���� ���
    //                                    POINTLIST = �� �ϳ��� ������ �ð� �����͸� ���� ���
    //                                    -> ���귮 ����, �����ͷ� ����

    //�� ���ۿ�, ������ �������, �׷��� �� �ð� ������=��Ƽ������ �غ�
    material->Set();

    //�غ�� �ð� �����͸� ����� (�����Ϳ� ������) ���̴��� �غ�
    geometryShader->Set();

    //������� �غ�� ����+��Ƽ����+���̴��� �״�� �׷��� ����(�׸���)
    DC->Draw(COUNT, 0); // �Ű������� "�󸶳�, (���� ������) ������"

    //���̴� ���� ���� ��±���
    DC->GSSetShader(nullptr, nullptr, 0); //�Ű������� �ǹ�
                                          // ù nullptr : ��������(�߰�) ��� ����ų �ȼ�, ����.
                                          // ���� nullptr : �߰��� �����ؼ� ����� �ٸ� ��ü ����.
                                          // 0 : ����� Ŭ������ �ν��Ͻ� ����
                                          // == "���� ȣ��δ� �ٸ� ������ �� �� ����,
                                          // �� ȣ�� ���� �����ص� �ɼǴ�� �Ȱ��� ����϶�"

    // ������Ʈ ���󺹱�
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void BillboardScene::PostRender()
{
    //blendState[1]->SetState();
    //for (Quad* tree : trees)
    //    tree->Render();
    //blendState[0]->SetState();
}

void BillboardScene::GUIRender()
{
}
