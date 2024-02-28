#include "Framework.h"

Naruto::Naruto()
    : ModelAnimator("Naruto")
{
    // ������ �ڵ鷯�� ������(�� ������ ũ��)�� �� ��° �Ű������� ����
    if (isRot)
    {
        ClientToScreen(hWnd, &clientCenterPos);
        SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    }
    

    mainHand = new Transform();
    tmpCollider = new SphereCollider();
    tmpCollider->Scale() *= 0.1; // �ӽ÷� 10% ũ��
    tmpCollider->SetParent(mainHand); // �ӽ÷� ���� �浹ü�� "��" Ʈ�������� �ֱ�

    crosshair = new Quad(L"Textures/UI/cursor.png");
    crosshair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crosshair->UpdateWorld();

    compass = new Quad(L"Textures/UI/Compass.png");
    compass->Pos() = { CENTER_X, WIN_HEIGHT * 0.95, 0 };
    compass->Scale() *= 0.1f;
    compass->UpdateWorld();

    quest = new Quad(L"Textures/UI/Compass_N.png");
    quest->SetParent(compass);
    quest->Scale() *= 10;

    quest2 = new Quad(L"Textures/UI/Compass_S.png");
    quest2->SetParent(compass);
    quest2->Scale() *= 15;

    quest3 = new Quad(L"Textures/UI/Compass_W.png");
    quest3->SetParent(compass);
    quest3->Scale() *= 15;

    quest4 = new Quad(L"Textures/UI/Compass_E.png");
    quest4->SetParent(compass);
    quest4->Scale() *= 15;

    ReadClip("Idle");
    ReadClip("Run");
    ReadClip("RunBack");
    ReadClip("RunLeft");
    ReadClip("RunRight");
    ReadClip("Throw");
    ReadClip("Punching");

    //�� Ŭ�� �ȿ� �ִ� �̺�Ʈ ������ ȣ��

    //GetClip(THROW)->SetEvent(bind(&Naruto::Throw, this), 0.0f); //<-�� �ð��� ������ �����ߴٰ�
    //<-�� ���� �ð��� ������ ���� ���� ������ ���� ����
    //GetClip(THROW)->SetEvent(bind(&Naruto::Throw, this), 1.0f / 33.0f * ��ų���);
    GetClip(THROW)->SetEvent(bind(&Naruto::Throw, this), 0.7f);
    GetClip(THROW)->SetEvent(bind(&Naruto::EndThrow, this), 0.9f);
}

Naruto::~Naruto()
{
    delete mainHand;
    delete kunai;
}

void Naruto::Update()
{
    Control();
    SetAnimation();

    mainHand->SetWorld(GetTransformByNode(38));
    //SetWorld : Ʈ�������� ������ �ٸ� ������ ���Խ�Ű��
    //GetTransformByNode : ���� ��忡�� Ʈ������ ���� ���
    // 38 : ������ ���� ���� ��� Ʈ���� ��� ���� �������� �޽� ��Ͽ��� �����ϴ� ����
    //      -> �ٸ� ���̳� �ٸ� ��带 ������ ���� �ش� ����� �ε����� �˸� ����!

    ModelAnimator::Update(); //�� ������Ʈ

    tmpCollider->UpdateWorld(); //�������� ���󰡴� ���� �浹ü ������Ʈ
                                //�𵨺��� ������Ʈ�� �صθ� ���� �ޱ⿡ ����

    ///-----------------------------

    //TODO : ���̰� ���� �߿��� ������ ���ư���
    //       (���� ���� �ƴ� ���� �������)

    if (KEY_PRESS('R'))
        Rot().y += 10 * DELTA;
    if (KEY_PRESS('E'))
        Rot().y += -10 * DELTA;


    tmp = XMConvertToDegrees(Rot().y);

    tmp2 = tmp + 180;

    tmp3 = tmp + 90;

    tmp4 = tmp - 90;

    //if (XMConvertToDegrees(Rot().y) < -180)
    while (tmp < -180)
        tmp += 360;
    while (tmp > 180)
        tmp -= 360;

    while (tmp2 < -180)
        tmp2 += 360;
    while (tmp2 > 180)
        tmp2 -= 360;

    while (tmp3 < -180)
        tmp3 += 360;
    while (tmp3 > 180)
        tmp3 -= 360;

    while (tmp4 < -180)
        tmp4 += 360;
    while (tmp4 > 180)
        tmp4 -= 360;       
           
    quest->Pos().x = tmp * compass->GetSize().x / 140;
    quest2->Pos().x = tmp2 * compass->GetSize().x / 140;
    quest3->Pos().x = tmp3 * compass->GetSize().x / 140;
    quest4->Pos().x = tmp4 * compass->GetSize().x / 140;

    //quest->UpdateWorld();
    //quest2->UpdateWorld();
    //quest3->UpdateWorld();
    //quest4->UpdateWorld();   
}

    

void Naruto::Render()
{
    ModelAnimator::Render();
    tmpCollider->Render();
    //quest->Render();
    
}

void Naruto::PostRender()
{
    crosshair->Render();
    
   
    //compass->Render();
    //if(quest->Pos().x >= -60 * compass->GetSize().x / 140 && quest->Pos().x <= +60 * compass->GetSize().x/140)
    //    quest->Render();
    //if (quest2->Pos().x >= -60 * compass->GetSize().x / 140 && quest2->Pos().x <= +60 * compass->GetSize().x / 140)
    // quest2->Render();
    //if (quest3->Pos().x >= -60 * compass->GetSize().x / 140 && quest3->Pos().x <= +60 * compass->GetSize().x / 140)
    // quest3->Render();
    //if (quest4->Pos().x >= -60 * compass->GetSize().x / 140 && quest4->Pos().x <= +60 * compass->GetSize().x / 140)
    // quest4->Render();
}

void Naruto::GUIRender()
{
    Model::GUIRender(); // �𵨷μ� GUI ����
                        // (������ �ȿ��� �ִϸ����Ͱ�, �ִϸ����� �ȿ��� ���� �����ϱ�)

    //ImGui::Text("rotate : %f", Rot().y);
    //ImGui::Text("forward.x : %f",(Forward().x));
    //ImGui::Text("forward.y : %f",(Forward().y));
    //ImGui::Text("forward.z : %f",(Forward().z));
    ImGui::Text("degree : %f", XMConvertToDegrees(Rot().y));
    ImGui::Text("tmp : %f", tmp);

    
    //ImGui::Text("x : %f", quest->GlobalPos().x);
    //ImGui::Text("y : %f", quest->GlobalPos().y);
    //ImGui::Text("z : %f", quest->GlobalPos().z);
    //
    //ImGui::Text("z : %f", compass->GlobalScale().x);
    //ImGui::Text("z : %f", compass->Scale().y);
    //ImGui::Text("z : %f", compass->Scale().z);
    
}

void Naruto::Control()
{
    if(isRot)
        Rotate();
    Move();
    Attack();
}

void Naruto::Move()
{
    if (curState == THROW) return; //������ ���� �߿��� �������� �ʵ���

    bool isMoveZ = false; // ���� �̵� �� : �⺻�� "�ƴ�"
    bool isMoveX = false; // �¿� �̵� �� : �⺻�� "�ƴ�"

    if (KEY_PRESS('W'))
    {
        velocity.z += DELTA; //�ӷ� ���ؿ� �ð� �����ŭ ������ �ֱ�
        isMoveZ = true; //���� �̵� ����
    }

    if (KEY_PRESS('S'))
    {
        velocity.z -= DELTA;
        isMoveZ = true;
    }

    if (KEY_PRESS('A'))
    {
        velocity.x -= DELTA;
        isMoveX = true;
    }

    if (KEY_PRESS('D'))
    {
        velocity.x += DELTA;
        isMoveX = true;
    }

    // �ӷ� ���� ���� x,z (������ xy) ���� �Ǵ��ؼ� ������ ���Ѵ�
    if (velocity.Length() > 1) velocity.Normalize(); // ����ȭ�� Ǯ��? -> �ӷ��� �������� �ͻӸ� �ƴ϶�
                                                     // �밢�� �Է¿��� ū ������ �Ͼ�� �ȴ�

    if (!isMoveZ) //���� �̵� ���� �ƴ� ���� �ӷ� ������ �ٽ� ������
        velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //�������� ����

    if (!isMoveX)
        velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

    //Ʈ�������� ���⿡ ���� ȸ�������� �������� �ٲٱ�
    Matrix rotY = XMMatrixRotationY(Rot().y);
    //����(=�� �������� ���� ������)���� �� ȸ�� ������ �ӷ� ������ ���ļ� ���� ����
    //=���� ȸ�� ��Ȳ���� �ӷ� �������� ���ϱ� ���� ������ ����ϴ� ���� ����
    Vector3 direction = XMVector3TransformCoord(velocity, rotY);

    //���� ������� ����ȭ�� �ӷ� ����(=����)
    // + ������ ���� (���� �ӷ�)
    // + ������ ȸ�� ����
    //....�� ���ļ� �����ǿ� �ֵ��� �Ѵ�
    Pos() += direction * moveSpeed * DELTA * -1; // �̵� ����
                                                 // -1 : "�ڷ� ����" -> ���� ������ �����ϱ�.

    // -> ��Ÿ ��� ��� ������ �̿��ؼ� �̵� ����
}

void Naruto::Rotate()
{
    //�Ʒ� �ڵ� ������ �߰����� ������ Ŀ���� �ٽ� �����̸鼭 ��Ÿ ����
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    // ���콺�� ������ ������ ��ġ�� �߰����� ����
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    // -> Ȥ�� �� �� ���� ���� �ÿ� �� �� �ȴٸ� CENTER_XY�� clinetCenterPos ǥ�ø� �ٲ㺸�� ������

    //��Ÿ�� ���� ĳ���Ϳ� ī�޶� ������ ��� ȸ��
    Rot().y += delta.x * rotSpeed * DELTA; // ĳ���� �¿�ȸ�� (���� ���̶� ī�޶� ���� ��)
    CAM->Rot().x -= delta.y * rotSpeed * DELTA; // ī�޶� ����ȸ��
}

void Naruto::Attack()
{
    if (curState == THROW) return; // �̹� ������ ���̸� ���� (�޺��Ұ�)

    if (KEY_DOWN(VK_LBUTTON))
    {
        SetState(THROW);

        //���̰� ������
    }
}

void Naruto::SetAnimation()
{
    if (curState == THROW) return;

    if (velocity.z > 0.1f) // �ӷ� ������ ���� ������ +��
        SetState(RUN_F);
    else if (velocity.z < -0.1f) // �� ���� -��
        SetState(RUN_B);
    else if (velocity.x > 0.1f) // �¿� ���� +��
        SetState(RUN_R);
    else if (velocity.x < -0.1f) //�¿� ���� -��
        SetState(RUN_L);
    else SetState(IDLE); // ������ ������
}

void Naruto::SetState(State state)
{
    if (state == curState) return;

    curState = state;
    PlayClip((int)state);
}

void Naruto::Throw()
{
    //���̰� �������� ������ ���ư���
    KunaiManager::Get()->Throw(tmpCollider->GlobalPos(), Back()); // Back : �������� ������ �� �ݿ�
}

void Naruto::EndThrow()
{
    SetState(IDLE); //�� �������Ƿ� ���� ���� ���ư���
}


