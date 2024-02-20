#pragma once

class HullShader : public Shader
{
    // 헐 셰이더 : 정점 셰이더 중에서, 하드웨어 접근 과정을 따로 떼어서 구분한 과정
    //            -> 정점 데이터는 이미 있고, 결과 출력 과정도 준비되어 있다고 칠 때,
    //               중간 전달 과정에서만 변화를 주고 싶으면 선택할 수 있다

private:
    friend class Shader; // 셰이더 클래스에서 서로 private 자유 참조 가능하게

    HullShader(wstring file); //탐색기에서 (셰이더) 파일을 받기 위해
    ~HullShader();

public:
    virtual void Set() override;

private:
    ID3D11HullShader* shader; // 이쪽 자료형이 진짜. 클래스는 줄임말을 위한 수단

};

