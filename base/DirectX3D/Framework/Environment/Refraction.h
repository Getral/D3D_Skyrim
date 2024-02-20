#pragma once

class Refraction
{
    // 일렁임 클래스

public:
    Refraction(wstring normalFile); //일렁임 중 높낮이 차를 묘사하기 위한 노말맵 필요
    ~Refraction();

    void Update();
    void SetRefraction();

    void SetRender();
    void PostRender();

    void GUIRender();

private:
    WaterBuffer* waterBuffer;

    Texture* normalMap;

    //이미지 투사를 위한 데이터
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    //본체 이미지
    class Quad* quad; //렌더 클래스라서 이쪽이 먼저 읽혀야 하지만,
                      //쿼드도 필수라서 부득이 선행 선언

};

