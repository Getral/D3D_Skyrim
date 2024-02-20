#pragma once

class Water : public GameObject
{
public:
    Water(wstring normalFile, float width = 100, float height = 100);
    ~Water();

    void Update();
    void Render();
    void GUIRender();

    // 일렁임, 반사 설정용
    void SetRefraction();
    void SetReflection();

private:
    void MakeMesh();

private:
    Vector2 size;

    Mesh<VertexUV>* mesh;

    Reflection* reflection;
    Refraction* refraction;

    //출력상태(투명, 혼합)
    BlendState* blendState[2];
};

