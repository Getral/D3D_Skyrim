#pragma once

class Trail : public GameObject
{
    // ���� ��ƼŬ : ��ƼŬ�� ����, �����δ� �ٸ� ��ƼŬ�� ���� ���α׷� ���ֿ� ���� �ʴ´�
    //              �ٸ� ��ƼŬ�� �׸��� ������ �����Ϳ� ���ؼ� ���� ����ϴ� �Ͱ� �ٸ���
    //              ������ ������ ������(�̹���)�� ������ ��Ģ�� ���� �κ� ���� ����� �ϱ� ����

public:
    Trail(wstring imageFile, Transform* start, Transform* end, UINT width, float speed);
    ~Trail();

    void Update();
    void Render();

private:
    void CreateMesh(); // ������� �̹����� ���� �޽��� �ʿ��ؼ�

private:
    Mesh<VertexUV>* mesh; // ������ (�⺻) ����)

    Transform* start; //������ ���۵Ǵ� ��
    Transform* end;   //������ ������ ��
    //Transform* offset, * origin; // ������ �߰� ���� �������� �� �� ������ ���⼭�� ����

    UINT width; //������ ���� ���� ��ƼŬ�� �׸� �� �̹��� ���� ũ��
    float speed; //������ ����, ��� �ӵ�

    // �̹��� ����� ���� ���� ����
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];

};

