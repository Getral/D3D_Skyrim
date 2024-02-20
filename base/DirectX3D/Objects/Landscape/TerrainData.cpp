#include "Framework.h"

TerrainData::TerrainData(wstring heightFile)
{
    heightMap = Texture::Add(heightFile); //높이 맵을 텍스처에서 받아서 적용

    //메쉬 만들기 + 정점 정리하기
    MakeMesh();
    MakeNormal();
    AlignVertexData();
}

TerrainData::~TerrainData()
{
    // 텍스처(=텍스처 클래스가 Release()함) 말고는 포인터 인스턴스 없음
    // 이후 추가되면 여기서 삭제
}

void TerrainData::MakeMesh()
{
    width = (UINT)heightMap->GetSize().x;
    height = (UINT)heightMap->GetSize().y;

    //높이맵 적용에 활용했던 픽셀읽기 다시 진행
    vector<Float4> pixels;
    heightMap->ReadPixels(pixels); // 결과는 벡터에 저장

    // 높이 맵에서 찾아낸 만큼 정점 준비
    vertices.reserve(width * height); // 지금은 형태 정점
    for (int z = 0; z < height; ++z)
    {
        for (int x = 0; x < width; ++x)
        {
            VertexType vertex; //정점준비
            vertex.pos = { (float)x, 0, (float)(height - z - 1) }; // 높이맵 픽셀에 맞추어서 위치 지정
            vertex.uv.x = x / (float)(width - 1); // 높이맵 픽셀 좌표를 UV에 대입
            vertex.uv.y = z / (float)(height - 1); 

            UINT index = width * z + x; //0부터 픽셀 끝까지 순번 부여
            vertex.pos.y = pixels[index].x * MAX_HEIGHT; //픽셀 위치에서 가져온 R값

            //정점 벡터에 넣기
            vertices.push_back(vertex);
        }
    }

    //정점 데이터를 인덱스로

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

    // 여기까지 오면 지형의 기본 형태, 메쉬가 만들어진다
    // 일단 이 함수는 여기서 끝
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

    // 이로써 지형의 법선 정보도 도출
}

void TerrainData::AlignVertexData()
{
    // 위에서 만든 메쉬의 정보와 순번의 목록과 법선 자료를 모두 사용해서
    // 각 정점을 인접 관계에 따라 다른 목록으로 한번 더 만들기

    alignedVertices.reserve(indices.size()); // 렌더용 목록을 만드는 과정에서
                                             // 연관 정점을 쓴다는 공통점이 있어서
                                             // 순번 목록의 크기 = 정리된 정점의 벡터 크기로 이해해도 된다

    for (UINT z = 0; z < height - 1; ++z) //위치에 따른 정점과 인접 정보 얻기
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            //찾아야 할 인접지의 인덱스
            UINT index0 = width * (z + 0) + (x + 0); // 자기자신
            UINT index1 = width * (z + 0) + (x + 1); // 가로 기준 옆자리
            UINT index2 = width * (z + 1) + (x + 0); // 세로 기준 옆자리
            UINT index3 = width * (z + 1) + (x + 1); // 대각선

            //이 인덱스에 해당하는 정점의 실제 위치, UV, 법선 등을 벡터에 따로 담는다
            alignedVertices.push_back(vertices[index0]);
            alignedVertices.push_back(vertices[index1]);
            alignedVertices.push_back(vertices[index2]);

            alignedVertices.push_back(vertices[index2]);
            alignedVertices.push_back(vertices[index1]);
            alignedVertices.push_back(vertices[index3]);

            // 이 과정이 반복되면서 렌더될 정점의 인덱스만이 아니라,
            // 실제로 인접된(그래서 렌더될) 정점의 실제 정보까지 앱이 인지할 수 있다
        }
    }
}
