#pragma once

class TerrainLOD : public GameObject
{
    // LOD : Level of Detail, �Ÿ��� ���� ���ι��� �������� ���
    // �� Ŭ������ LOD�� ���� ���ҽ��� ��ü ���� �ǽð����� �����ϴ� ���� �������� �Ѵ�.

private:
    typedef VertexUV VertexType; // �ٸ� Ÿ���� �ִٸ� VertexUV���� ����

public:
    TerrainLOD(wstring heightFile); // ���� �� ������ �޾Ƽ� ���� ����
    ~TerrainLOD();

    void Render();
    void GUIRender();

private:
    void MakeMesh(); // ������ ��¥ ���� �� �ƴ϶� �ٸ� �Լ��� ���� �ʿ����� �ʴ�

private:
    // �Ҽ� ���۸� �뵵�� �°� 2����
    FloatValueBuffer* terrainBuffer;    // ���� ��� (��ü �����)
    FloatValueBuffer* heightBuffer;     // ���� ��� � �� �����

    //������ �޽�
    Mesh<VertexType>* mesh;

    //���� �����͸� ����� GPU�� ����/����� ���̴� �غ�
    HullShader* hullShader;     // ���� ���޿�
    DomainShader* domainShader; // ���޵� ���� ��¿�

    // ���̸�
    Texture* heightMap;

    //������ ������
    UINT width, height; // ������ ���ο� ����
    UINT patchWidth, patchHeight; // (Ư�� ���ؿ� ���� ����) ���� ������ ���ο� ����
                                  // * ���ؿ� ����, Ư�� ���·�, ������ �ɰ��鼭 ����Ѵ� �ǹ�

    // * patch : �ٸ� ���� Ŭ�������� ���ϴ� "���"�� ����� ����
    //           �ڵ� ������ ��ü�� �ִ� ���� ������ �ƴϰ�, ���� �߿� ���ǻ� �����ϴ� ����
    //           ��ġ�� ���´� �پ��� �� ������, ���� ���簢��(��Ʈ) ����� ���� �����Ѵ�

    // �׷��� � �������� ������ ������, ��� ����� ���ΰ�
    UINT cellsPerPatch = 32; // �ϳ��� ��ġ�� �Ǳ� ���� �ʿ��� ��(��������)�� ����
    float cellSpacing = 5.0f;   // �������� ���� ������ �� �������� ����
    Vector2 cellUV;          // ���������� ������ ����Ѵٰ� ġ��, �� �� ������ �ؽ�ó�� UV��ǥ

};

