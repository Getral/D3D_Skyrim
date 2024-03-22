#pragma once

class Terrain : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;
    const float MAX_HEIGHT = 100.0f;

    class RayBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Float3 pos;
            UINT triangleSize;

            Float3 dir;
            float padding;
        };

    public:
        RayBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

    struct InputDesc
    {
        Float3 v0, v1, v2;
    };

    struct OutputDesc
    {
        int picked;
        float distance;
    };

public:
    Terrain(Vector2 size = { 10, 10 });
    Terrain(wstring mapFile, wstring heightmap);
    ~Terrain();

    void Render();

    float GetHeight(const Vector3& pos, Vector3* normal = nullptr);

    Vector3 Picking();
    bool ComputePicking(Vector3& pos, Transform* transform);
    bool ComputePicking(Vector3& pos, Transform* transform, bool isJump);

    Vector2 GetSize() { return Vector2(width, height); } //가로 세로를 직접 받을 수 있게 추가

    void SetSize(Vector2 size) { this->width = size.x; this->height = size.y; }

private:
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();
    void MakeComputeData();

private:
    UINT width, height;
    UINT triangleSize;

    Mesh<VertexType>* mesh;

    vector<OutputDesc> outputs;
    vector<InputDesc> inputs;

    RayBuffer* rayBuffer;
    StructuredBuffer* structuredBuffer;

    ComputeShader* computeShader;

    Texture* heightMap;
    Texture* alphaMap;
    Texture* secondMap;
    Texture* thirdMap;

};