#include "Framework.h"

ProgressBar::ProgressBar(wstring frontImageFile, wstring backImageFile)
    : Quad(frontImageFile)
{
    // ���� ���� ����
    material->SetShader(L"UI/ProgressBar.hlsl"); // 2D�� ����ϴ� ���̴�

    // �ĸ� �̹��� ����
    backImage = Texture::Add(backImageFile);

    valueBuffer = new FloatValueBuffer(); // �Ҽ� ����� ���� �����
    valueBuffer->Get()[0] = fillAmount; // valueBuffer->Get() : �� �����ӿ�ũ�� ���� ȣ�� �������̽�
                                        // [0] : ������ ù ��° ��
                                        // fillAmount : ���ۿ� ������ ������
}

ProgressBar::~ProgressBar()
{
    delete valueBuffer;
}

void ProgressBar::Render()
{
    valueBuffer->SetPS(10); // GPU�� �����ϵ��� ���� + ����(��¿켱����) 10
    backImage->PSSet(10);   // �ĸ� �̹��� �����͵� �ȼ� ���̴��� �غ�

    Quad::Render(); //���� ����
}

void ProgressBar::SetAmount(float value)
{
    valueBuffer->Get()[0] = value; //���ۿ� �Ű������� ���� ���� �״�� ����
}
