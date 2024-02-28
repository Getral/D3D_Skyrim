#pragma once
class Rain : public Particle
{
public:
    Rain();
    ~Rain();

    void Update();
    void Render();
    void GUIRender();

private:
    void Create();

private:
    //FloatValueBuffer* buffer;   // 빗방울 표현
    //VertexBuffer* vertexBuffer; // 빗방울 위치
    // -> 비나 날씨의 경우 복잡하려면 더 복잡해질 수 있고
    //    단순하게 만들려면 오히려 더 단순하게도 만들 수 있다

    WeatherBuffer* buffer; // 정점+소수 버퍼, 날씨 효과 연출용
                           // * 날씨 버퍼는 비 말고도 다른 날씨에 쓸 수 있어서 범용으로 작성됨

    vector<VertexUV> vertices;
};

