#pragma once

class DomainShader : public Shader
{
    // 도메인 셰이더 : 정점 데이터가 있고, 전달 과정이 있다고 칠 때,
    //                받아온 정점 데이터들을 (지오메트리처럼) 하드웨어에서 빠르게 연산하는 셰이더
    //                거칠게 비유하면 GPU용 정점 셰이더라고 표현할 수도 있다

private:
    friend class Shader;

    DomainShader(wstring file);
    ~DomainShader();

public:
    virtual void Set() override;

private:
    ID3D11DomainShader* shader;

};

