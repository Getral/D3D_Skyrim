#pragma once
class BillboardScene : public Scene
{
    //������ : ����, Ư�� �Ÿ��� ũ�� �����δ� ����
    //        ���α׷��ֿ����� ������ 100% ��µǴ� �̹��� UI�� ��Ī (2D)
    //        Ȥ�� ī�޶��� ����, ��ġ�� ������� ������ Ȯ�� ������ �̹��� ����� ��Ī(3D)

private:
    UINT COUNT = 100;

public:
    BillboardScene();
    ~BillboardScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    vector<Quad*> trees; //���� �̹��� = ����

    // ������ ������ ���� ���
    // A : ���͸� �̿��� ���� ���� : �ܼ�, ��� ǥ�� �ܿ� ������ �����̳� �������� ���� �����
    // B : ī�޶�� ���� ����ȭ    : ���̴� �� ������, ī�޶� �����Ѵ�
    // C : ĵ����                 : ǥ���� ����� ������, ���� ����� ���� ��� ��ġ�� �� ���� �ʴ�
    //                          //����� ������ �� �ְų�.. ������ �ִ� ���� ���� �ű⿡ ��ü�� �ִٴ� ������ ����
    //                          //�����ϰ� ���̴� �͸��� ������ �� ���� ����
    // 
    // D : ������Ʈ��(����) ���̴��� Ȱ���� �ǽð� ������ : ������. ������. ������ C�� ���� (��ü�� ����)

    // C ����� ���� �߰� ����
    vector<Transform*> origins; //���� ��ġ�� ������ ����� ����
    BlendState* blendState[2];

    // D ����� ���� �߰� ����

    // ������Ʈ�� ���̴��� ������ �����ϱ�
    GeometryShader* geometryShader; // DX�� G���̴��� ���ϰ� ���� ���� ��ü
                                    // *DX ���� ��ɵ��� ����ũ�μ���Ʈ �н� ���������� �˻� ����

    Material* material; // ���̴��� ���߱� ���� ������ ��Ƽ����
    VertexBuffer* vertexBuffer; //���� ���۵� (�簢�� �������� ����)

    //�׸� �����͸� "�ٸ� ��"�� �����ϱ� ���� �غ�
    DepthStencilState* depthState[2]; //���� ������Ʈ 2��
    vector<VertexUV> vertices; //���� ���� (�ؽ�ó ���� ���� + ���ۿ� �ֱ� ���� �������� ����)

    // -> ��Ƽ������ ������Ʈ���� �غ� -> ���ۿ� ���̴��� ���� -> �״�� ���
};

