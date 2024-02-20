#pragma once

class Water : public GameObject
{
public:
    Water(wstring normalFile, float width = 100, float height = 100);
    ~Water();

    void Update();
    void Render();
    void GUIRender();

    // �Ϸ���, �ݻ� ������
    void SetRefraction();
    void SetReflection();

private:
    void MakeMesh();

private:
    Vector2 size;

    Mesh<VertexUV>* mesh;

    Reflection* reflection;
    Refraction* refraction;

    //��»���(����, ȥ��)
    BlendState* blendState[2];
};

