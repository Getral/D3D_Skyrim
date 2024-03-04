#include "Framework.h"

Human::Human() : ModelAnimator("Human")
{
    ReadClip("Idle", 1);
    ReadClip("Run", 1);
    ReadClip("Jump", 1);

    action = (ACTION)frameBuffer->Get().cur.clip;

    crowbar = new Crowbar();
    crowbar->Load();

    mainHand = new Transform();
    crowbar->SetParent(mainHand);

    Scale() *= 0.1f;

    //궤적 사용하기
    startEdge = new Transform(); //준비만 하기
    endEdge = new Transform();
    trail = new Trail(L"Textures/Etc/sun.jpg", startEdge, endEdge, 100, 100);
    //trail = new Trail(L"Textures/Effect/Trail.png", startEdge, endEdge, 100, 100);
                // 궤적 생성 (이미지 파일, 시작점, 종점, 자를 그림 가로 크기, 재생-진행속도)

    trail->SetActive(trailToggle);
}

Human::~Human()
{
    delete crowbar;
    delete mainHand;

    delete trail;
}

void Human::Update()
{
    ClipSync();
    Control();
    Jump();

    mainHand->SetWorld(GetTransformByNode(51));
    crowbar->Update();

    // -----------------------------------------------

    // 모델 업데이트 전에 (모든 것이 반영되기 전에) 궤적 준비 진행

    //startEdge->Pos() = crowbar->GlobalPos() + crowbar->Up() * 200.0f; // 200.0f : 모델 크기
    //endEdge->Pos() = crowbar->GlobalPos() - crowbar->Up() * 200.0f; // Down만큼 더해도 가능

    startEdge->Pos() = crowbar->GlobalPos() + crowbar->Up() * 20.0f; // 20.0f : 10% 크기 반영
    endEdge->Pos() = crowbar->GlobalPos() - crowbar->Up() * 20.0f;

    // 찾아낸 꼭지점 위치를 업데이트
    startEdge->UpdateWorld();
    endEdge->UpdateWorld(); // 이러면 트랜스폼에 위치가 담긴다

    // -----------------------------------------------

    ModelAnimator::Update();

    trail->Update(); // 위에서 준비한 궤적 + 궤적을 진행하는 모델까지 업데이트 후, 본체 업데이트
                     // 궤적 시작, 끝 위치를 여기서 업데이트하면, 어차피 포인터라서 궤적이 업데이트할 때도
                     // 해당 위치가 모두 반영이 될 터이므로
}

void Human::Render()
{
    crowbar->Render();
    ModelAnimator::Render();

    trail->Render(); // 궤적 렌더
}

void Human::GUIRender()
{
    crowbar->GUIRender();
    ModelAnimator::GUIRender();
}

void Human::ClipSync()
{
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        PlayClip((int)action);
    }
}

void Human::Control()
{
    if (!isJump)
    {
        if (KEY_PRESS('W'))
        {
            action = ACTION::RUN;
        }

        if (KEY_UP('W'))
        {
            action = ACTION::IDLE;
        }

        if (KEY_DOWN(VK_SPACE))
        {
            action = ACTION::JUMP;
            jumpVelocity = jumpForce;
            isJump = true;
        }

        if (KEY_DOWN('T'))
        {
            trailToggle = !trailToggle; // 값 뒤집기
            trail->SetActive(trailToggle);
        }
    }
}

void Human::Jump()
{
    jumpVelocity -= 9.8f * gravityMult * DELTA;
    Pos().y += jumpVelocity;

    if (Pos().y > 0)
    {
        if (action != ACTION::JUMP) action = ACTION::JUMP;
        isJump = true;
    }

    if (Pos().y < 0)
    {
        Pos().y = 0;
        jumpVelocity = 0;
        if (action == ACTION::JUMP) action = ACTION::IDLE;
        isJump = false;
    }
}
