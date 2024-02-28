#pragma once

class Quad : public GameObject
{
private:
    typedef VertexUV VertexType;

public:
    Quad(Vector2 size);    
    Quad(wstring file);
    ~Quad();

    void Render();
    void SetRender();

    Vector2 GetSize() { return size; }
private:
    void MakeMesh();

private:
    Vector2 size;

    Mesh<VertexType>* mesh;    
};