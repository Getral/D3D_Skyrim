#include "Framework.h"

TerrainData::TerrainData(wstring heightFile)
{
    heightMap = Texture::Add(heightFile); //���� ���� �ؽ�ó���� �޾Ƽ� ����

    //�޽� ����� + ���� �����ϱ�
    MakeMesh();
    MakeNormal();
    AlignVertexData();
}

TerrainData::~TerrainData()
{
    // �ؽ�ó(=�ؽ�ó Ŭ������ Release()��) ����� ������ �ν��Ͻ� ����
    // ���� �߰��Ǹ� ���⼭ ����
}

void TerrainData::MakeMesh()
{
    width = (UINT)heightMap->GetSize().x;
    height = (UINT)heightMap->GetSize().y;

    //���̸� ���뿡 Ȱ���ߴ� �ȼ��б� �ٽ� ����
    vector<Float4> pixels;
    heightMap->ReadPixels(pixels); // ����� ���Ϳ� ����

    // ���� �ʿ��� ã�Ƴ� ��ŭ ���� �غ�
    vertices.reserve(width * height); // ������ ���� ����
    for (int z = 0; z < height; ++z)
    {
        for (int x = 0; x < width; ++x)
        {
            VertexType vertex; //�����غ�
            vertex.pos = { (float)x, 0, (float)(height - z - 1) }; // ���̸� �ȼ��� ���߾ ��ġ ����
            vertex.uv.x = x / (float)(width - 1); // ���̸� �ȼ� ��ǥ�� UV�� ����
            vertex.uv.y = z / (float)(height - 1); 

            UINT index = width * z + x; //0���� �ȼ� ������ ���� �ο�
            vertex.pos.y = pixels[index].x * MAX_HEIGHT; //�ȼ� ��ġ���� ������ R��

            //���� ���Ϳ� �ֱ�
            vertices.push_back(vertex);
        }
    }

    //���� �����͸� �ε�����

    indices.reserve((width - 1) * (height - 1) * 6);

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            indices.push_back(width * (z + 0) + (x + 0)); // 0
            indices.push_back(width * (z + 0) + (x + 1)); // 1
            indices.push_back(width * (z + 1) + (x + 0)); // 2

            indices.push_back(width * (z + 1) + (x + 0)); // 2
            indices.push_back(width * (z + 0) + (x + 1)); // 1
            indices.push_back(width * (z + 1) + (x + 1)); // 3
        }
    }

    // ������� ���� ������ �⺻ ����, �޽��� ���������
    // �ϴ� �� �Լ��� ���⼭ ��
}

void TerrainData::MakeNormal()
{
    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 v0 = vertices[index0].pos;
        Vector3 v1 = vertices[index1].pos;
        Vector3 v2 = vertices[index2].pos;

        Vector3 e0 = v1 - v0;
        Vector3 e1 = v2 - v0;

        Vector3 normal = Cross(e0, e1).GetNormalized();

        vertices[index0].normal = normal + vertices[index0].normal;
        vertices[index1].normal = normal + vertices[index1].normal;
        vertices[index2].normal = normal + vertices[index2].normal;
    }

    // �̷ν� ������ ���� ������ ����
}

void TerrainData::AlignVertexData()
{
    // ������ ���� �޽��� ������ ������ ��ϰ� ���� �ڷḦ ��� ����ؼ�
    // �� ������ ���� ���迡 ���� �ٸ� ������� �ѹ� �� �����

    alignedVertices.reserve(indices.size()); // ������ ����� ����� ��������
                                             // ���� ������ ���ٴ� �������� �־
                                             // ���� ����� ũ�� = ������ ������ ���� ũ��� �����ص� �ȴ�

    for (UINT z = 0; z < height - 1; ++z) //��ġ�� ���� ������ ���� ���� ���
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            //ã�ƾ� �� �������� �ε���
            UINT index0 = width * (z + 0) + (x + 0); // �ڱ��ڽ�
            UINT index1 = width * (z + 0) + (x + 1); // ���� ���� ���ڸ�
            UINT index2 = width * (z + 1) + (x + 0); // ���� ���� ���ڸ�
            UINT index3 = width * (z + 1) + (x + 1); // �밢��

            //�� �ε����� �ش��ϴ� ������ ���� ��ġ, UV, ���� ���� ���Ϳ� ���� ��´�
            alignedVertices.push_back(vertices[index0]);
            alignedVertices.push_back(vertices[index1]);
            alignedVertices.push_back(vertices[index2]);

            alignedVertices.push_back(vertices[index2]);
            alignedVertices.push_back(vertices[index1]);
            alignedVertices.push_back(vertices[index3]);

            // �� ������ �ݺ��Ǹ鼭 ������ ������ �ε������� �ƴ϶�,
            // ������ ������(�׷��� ������) ������ ���� �������� ���� ������ �� �ִ�
        }
    }
}
