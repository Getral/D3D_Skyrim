#pragma once

class TerrainLOD : public GameObject
{
    // LOD : Level of Detail, 거리에 의한 세부묘사 수준차별 기법
    // 이 클래스는 LOD를 복수 리소스의 교체 없이 실시간으로 연산하는 것을 목적으로 한다.

private:
    typedef VertexUV VertexType; // 다른 타입이 있다면 VertexUV에서 수정

public:
    TerrainLOD(wstring heightFile); // 높이 맵 파일을 받아서 지형 생성
    ~TerrainLOD();

    void Render();
    void GUIRender();

private:
    void MakeMesh(); // 영역을 진짜 나눌 게 아니라 다른 함수는 굳이 필요하진 않다

private:
    // 소수 버퍼를 용도에 맞게 2종류
    FloatValueBuffer* terrainBuffer;    // 지형 계산 (전체 연산용)
    FloatValueBuffer* heightBuffer;     // 지형 출력 등에 쓸 상수값

    //지형의 메쉬
    Mesh<VertexType>* mesh;

    //지형 데이터를 나누어서 GPU에 전달/출력할 셰이더 준비
    HullShader* hullShader;     // 정점 전달용
    DomainShader* domainShader; // 전달된 정점 출력용

    // 높이맵
    Texture* heightMap;

    //지형의 데이터
    UINT width, height; // 지도의 가로와 세로
    UINT patchWidth, patchHeight; // (특정 기준에 따라 나뉜) 개별 구역의 가로와 세로
                                  // * 기준에 따라, 특정 형태로, 지형을 쪼개면서 계산한단 의미

    // * patch : 다른 지형 클래스에서 말하던 "노드"와 비슷한 개념
    //           코드 내에서 실체가 있는 구분 단위는 아니고, 연산 중에 편의상 지정하는 구간
    //           패치의 형태는 다양할 수 있지만, 흔히 직사각형(렉트) 모양을 자주 전제한다

    // 그래서 어떤 기준으로 지형을 나누고, 어떻게 계산할 것인가
    UINT cellsPerPatch = 32; // 하나의 패치가 되기 위해 필요한 셀(정점단위)의 개수
    float cellSpacing = 5.0f;   // 정점단위 간에 가지게 될 공간상의 여백
    Vector2 cellUV;          // 정점단위를 실제로 출력한다고 치고, 그 때 참고할 텍스처의 UV좌표

};

