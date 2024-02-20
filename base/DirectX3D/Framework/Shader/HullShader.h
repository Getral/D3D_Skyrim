#pragma once

class HullShader : public Shader
{
    // �� ���̴� : ���� ���̴� �߿���, �ϵ���� ���� ������ ���� ��� ������ ����
    //            -> ���� �����ʹ� �̹� �ְ�, ��� ��� ������ �غ�Ǿ� �ִٰ� ĥ ��,
    //               �߰� ���� ���������� ��ȭ�� �ְ� ������ ������ �� �ִ�

private:
    friend class Shader; // ���̴� Ŭ�������� ���� private ���� ���� �����ϰ�

    HullShader(wstring file); //Ž���⿡�� (���̴�) ������ �ޱ� ����
    ~HullShader();

public:
    virtual void Set() override;

private:
    ID3D11HullShader* shader; // ���� �ڷ����� ��¥. Ŭ������ ���Ӹ��� ���� ����

};

