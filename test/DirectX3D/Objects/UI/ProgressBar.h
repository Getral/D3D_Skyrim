#pragma once
class ProgressBar : public Quad
{
    // ���α׷��� �� (�����Ȳ ǥ�ñ�) : Ư�� ������ ����, �޼�ġ ���� �׸��� ������ ��Ÿ���� UI
    //                         ������� Ư���� (������ ä������ �����) ü�¹� ��� ���� ����

public:
    ProgressBar(wstring frontImageFile, wstring backImageFile);
    ~ProgressBar();

    void Render();

    void SetAmount(float value); //amount : (��ü �翡 ����) ���� ����ġ

private:
    Texture* backImage; // ��� �̹���.
                        // �� Ŭ������ �����̱� ������ ��������� �̹��� 2���� ���� ��

    float fillAmount = 1; // �⺻ ����ġ = 1 = "��ü, �� á��"

    // �� ������ �־ ��� ��������... ���� �ӵ��� ���̱� ���ؼ�
    // �����͸� ������ ����(Ȥ�� �ٸ� ����)���� �ű���� �Ѵ�

    FloatValueBuffer* valueBuffer; // �Ҽ� ����� ���� : �����̵��� ���۷� ���� �� �ִ�!
                                   // ���۰� �������� �ش� �����ʹ� ������ ��������,
                                   // ��ü ���� ��������, �޸� �δ��� Ŀ����.
};

