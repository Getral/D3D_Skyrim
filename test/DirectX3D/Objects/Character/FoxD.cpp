#include "Framework.h"

FoxD::FoxD() : ModelAnimator("Fox")
{
    ReadClip("Idle");
    ReadClip("Run", 0, "FoxTransform"); // �� ���Ͽ� �־��� ���븦 �������� ����

    PlayClip(curState); // ������ �ֱ���� ���
    Pos() = { 5, 0, 5 };
    Scale() *= 0.5f;
}

FoxD::~FoxD()
{
    //��ü�� �ۿ��� ���� �Ŷ� ���� ���⼭ ���� �ʿ䰡?
}

void FoxD::Update()
{
    Control();
    Move();
    Rotate();

    ModelAnimator::Update();

    //�ͷ���, ���ͽ�Ʈ�� : �ۿ��� ���� �Ŷ� ���� ���⼭ ������Ʈ�� �ʿ䰡?
}

void FoxD::Render()
{
    ModelAnimator::Render();
}

void FoxD::Control()
{
    // �Է��� �޾Ƽ� ���� �����̱�

    if (KEY_DOWN('Q')) //Q�� ������
    {
        //dijkstra->CallCreateNode(terrain->Picking()); //���콺 Ŀ���� �ִ� ���� �� ��� ��ġ
        Vector3 pickPos;
        if (terrain->ComputePicking(pickPos))
            dijkstra->CallCreateNode(pickPos);
    }

    if (KEY_DOWN('E')) //E�� ������
    {
        dijkstra->CallSelectNode(); //���콺 Ŀ���� �ִ� ���� ��带 ���� ����
    }

    if (KEY_UP('E')) //E���� ���� ����
    {
        dijkstra->CallLinkNode(); //���õ� ��尡 �־��� ���� ���콺 Ŀ���� ���� ��忡 ��Ҵٸ�,
                                  // �� ��带 �̾ ���� ��ó�� �ν�
    }

    if (KEY_DOWN(VK_SPACE)) // �����̽��ٸ� ������
    {
        SetPath(); // ��θ� ����
    }

}

void FoxD::Move()
{
    if (path.empty()) //��� ���Ͱ� ��� �ִ� ���
    {
        SetState(IDLE); //������ �ֱ�
        return; // �������� �ʱ�
    }

    // �� �������� �Դ� = ��ο� ���� �� ���� ���� �ִ�

    SetState(RUN); //�����̱� + �޸��� ���� ����

    //���ͷ� ���� ��θ� �ϳ��� ã�ư��鼭 �����̱�

    Vector3 dest = path.back(); // ������ �̸��� ����� ������
                                // = �������� ���� ���� ���� ������ ������
                                // ��ΰ� �� �Ųٷγ�? -> ��ã�� �˰��򿡼�
                                // ��θ� ���� ������ �ۼ��� ó������,
                                // �˻�� ��� �߰��� �ڿ������� �߱� ����

    Vector3 direction = dest - GlobalPos(); //�� ��ġ���� �������� ���� = ����

    direction.y = 0; // ���� ������ ���ͽ�Ʈ�� �˰��� Ư¡�� ����ؼ� ���̸� 0����
                     // ���� ���̸� �ݿ��� ���, �������� GetHeight ���� �������� ���� �޾ƿ��� ��õ

    if (direction.Length() < 0.5f) //���� �� ������ (������Ʈ ȣ�� �������� ��� ����)
    {
        path.pop_back(); //�� �� �������� ���Ϳ��� ����
    }

    //�������� ���� ���� ���� �̵�
    velocity = direction.GetNormalized(); //�ӷ±��� (������ ����ȭ)
    Pos() += velocity * moveSpeed * DELTA; //�ӷ±��� * ���� �ӷ� * �ð����...�� ����

}

void FoxD::Rotate()
{
    if (curState == IDLE) return; // �޸��� �ִ� ���� �ƴϸ� ȸ���� �ʿ� ����

    Vector3 forward = Forward(); //�� �������� �� ������
    Vector3 cross = Cross(forward, velocity); //�������̿��� ���� ����

    if (cross.y < 0) // ������ ���̴� = ���� ���� ���⺸�� �������� ���� ���̴�
    {
        Rot().y += rotSpeed * DELTA;
    }
    else if (cross.y > 0) //�ݴ��� ���
    {
        Rot().y -= rotSpeed * DELTA;
    }
}

void FoxD::SetState(State state)
{
    if (state == curState) return;
    curState = state;
    PlayClip(state);
}

void FoxD::SetPath()
{
    int start = dijkstra->FindCloseNode(GlobalPos()); // ���쿡�� ���� ����� ��带 ���������
    int end = dijkstra->FindCloseNode(terrain->Picking()); // ���콺 Ŀ�� ��ó�� ��������

    //������ ���� ������� ������ �մ� ��θ� ��ã�� �˰��򿡼� ����
    path = dijkstra->GetPath(start, end); // ��θ� ���� �������� Move �Լ��� �˾Ƽ� �������� ��
}
