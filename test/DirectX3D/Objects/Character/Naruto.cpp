#include "Framework.h"

Naruto::Naruto()
    : ModelAnimator("Naruto")
{
    // 윈도우 핸들러의 정보값(중 윈도우 크기)을 두 번째 매개변수에 저장
    if (isRot)
    {
        ClientToScreen(hWnd, &clientCenterPos);
        SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    }
    

    mainHand = new Transform();
    tmpCollider = new SphereCollider();
    tmpCollider->Scale() *= 0.1; // 임시로 10% 크기
    tmpCollider->SetParent(mainHand); // 임시로 만든 충돌체를 "손" 트랜스폼에 주기

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

    //모델 클립 안에 있는 이벤트 세팅을 호출

    //GetClip(THROW)->SetEvent(bind(&Naruto::Throw, this), 0.0f); //<-이 시간에 무적을 설정했다가
    //<-이 정도 시간에 무적을 끄면 무적 프레임 설정 가능
    //GetClip(THROW)->SetEvent(bind(&Naruto::Throw, this), 1.0f / 33.0f * 스킬계수);
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
    //SetWorld : 트랜스폼의 공간을 다른 곳에서 대입시키기
    //GetTransformByNode : 모델의 노드에서 트랜스폼 정보 얻기
    // 38 : 나루토 모델을 뷰어로 열어서 트리를 모두 열면 오른손이 메쉬 목록에서 차지하는 순서
    //      -> 다른 모델이나 다른 노드를 대입할 때는 해당 노드의 인덱스를 알면 좋다!

    ModelAnimator::Update(); //모델 업데이트

    tmpCollider->UpdateWorld(); //오른손을 따라가는 중인 충돌체 업데이트
                                //모델부터 업데이트를 해두면 정보 받기에 유리

    ///-----------------------------

    //TODO : 쿠나이가 공격 중에는 앞으로 나아가게
    //       (공격 중이 아닐 때는 사라지게)

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
    Model::GUIRender(); // 모델로서 GUI 렌더
                        // (나루토 안에는 애니메이터가, 애니메이터 안에는 모델이 있으니까)

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
    if (curState == THROW) return; //던지기 동작 중에는 움직이지 않도록

    bool isMoveZ = false; // 전후 이동 중 : 기본값 "아님"
    bool isMoveX = false; // 좌우 이동 중 : 기본값 "아님"

    if (KEY_PRESS('W'))
    {
        velocity.z += DELTA; //속력 기준에 시간 경과만큼 누적값 주기
        isMoveZ = true; //전후 이동 중임
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

    // 속력 기준 값의 x,z (평면상의 xy) 값을 판단해서 방향을 구한다
    if (velocity.Length() > 1) velocity.Normalize(); // 정규화를 풀면? -> 속력이 빨라지는 것뿐만 아니라
                                                     // 대각선 입력에서 큰 가속이 일어나게 된다

    if (!isMoveZ) //전후 이동 중이 아닐 때는 속력 기준을 다시 내린다
        velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //보간으로 감속

    if (!isMoveX)
        velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

    //트랜스폼의 방향에 의한 회전정보를 면적으로 바꾸기
    Matrix rotY = XMMatrixRotationY(Rot().y);
    //면적(=그 면적에서 나온 수직선)으로 된 회전 정보와 속력 기준을 합쳐서 만든 방향
    //=현재 회전 상황에서 속력 기준으로 향하기 위한 방향을 계산하는 벡터 보간
    Vector3 direction = XMVector3TransformCoord(velocity, rotY);

    //위에 만들어진 정규화된 속력 기준(=방향)
    // + 보간된 벡터 (실제 속력)
    // + 보간된 회전 벡터
    //....를 합쳐서 포지션에 주도록 한다
    Pos() += direction * moveSpeed * DELTA * -1; // 이동 수행
                                                 // -1 : "뒤로 가기" -> 모델이 뒤집혀 있으니까.

    // -> 델타 계산 대신 보간을 이용해서 이동 가능
}

void Naruto::Rotate()
{
    //아래 코드 때문에 중간으로 고정된 커서가 다시 움직이면서 델타 생성
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    // 마우스가 움직일 때마다 위치를 중간으로 고정
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    // -> 혹시 위 두 줄이 조작 시에 잘 안 된다면 CENTER_XY와 clinetCenterPos 표시를 바꿔보면 될지도

    //델타에 의한 캐릭터와 카메라 양쪽을 모두 회전
    Rot().y += delta.x * rotSpeed * DELTA; // 캐릭터 좌우회전 (추적 중이라 카메라도 따라갈 것)
    CAM->Rot().x -= delta.y * rotSpeed * DELTA; // 카메라 상하회전
}

void Naruto::Attack()
{
    if (curState == THROW) return; // 이미 던지는 중이면 종료 (콤보불가)

    if (KEY_DOWN(VK_LBUTTON))
    {
        SetState(THROW);

        //쿠나이가 나가게
    }
}

void Naruto::SetAnimation()
{
    if (curState == THROW) return;

    if (velocity.z > 0.1f) // 속력 기준이 현재 앞으로 +면
        SetState(RUN_F);
    else if (velocity.z < -0.1f) // 앞 기준 -면
        SetState(RUN_B);
    else if (velocity.x > 0.1f) // 좌우 기준 +면
        SetState(RUN_R);
    else if (velocity.x < -0.1f) //좌우 기준 -면
        SetState(RUN_L);
    else SetState(IDLE); // 가만히 있으면
}

void Naruto::SetState(State state)
{
    if (state == curState) return;

    curState = state;
    PlayClip((int)state);
}

void Naruto::Throw()
{
    //쿠나이가 나루토의 앞으로 나아가게
    KunaiManager::Get()->Throw(tmpCollider->GlobalPos(), Back()); // Back : 나루토의 뒤집힌 모델 반영
}

void Naruto::EndThrow()
{
    SetState(IDLE); //다 던졌으므로 이전 동작 돌아가기
}


