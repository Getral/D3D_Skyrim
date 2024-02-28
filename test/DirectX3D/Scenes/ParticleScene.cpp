#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
    collider = new SphereCollider(30); // 테스트용 충돌체

    //particle = new Spark(L"Textures/Effect/star.png", true);
    //particle = new Rain(); //비 생성
    //particle = new Sprite(L"Textures/Effect/explosion.png", 10, 10, 5, 3);
    //particle = new Sprite(L"Textures/Effect/fire_8x2.png", 5, 25, 8, 2, false);

    // 파티클이 개별이고, 조건이 아닌 수동 재생이 필요할 때
    //particle->Play(Vector3()); //원점에서 날씨 이펙트 실행

    //---------------------------------------

    // 범용 파티클 사용
    //particle = new ParticleSystem(L"Textures/Effect/explosion.png");
                                        // 그림으로 만들기
    particle = new ParticleSystem("TextData/Particles/Star.fx");
                                        // 사전에 설정된 파일을 읽어서 만들기
}

ParticleScene::~ParticleScene()
{
    delete particle;
    delete collider;
}

void ParticleScene::Update()
{
    if (KEY_DOWN(VK_LBUTTON)) //좌클릭
    {
        Ray ray = CAM->ScreenPointToRay(mousePos);
        Contact contact;

        if (collider->IsRayCollision(ray, &contact)) //마우스 커서가 구체에 닿으면
        {
            particle->Play(contact.hitPoint); //거기서 파티클 재생
        }
    }
    particle->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
    particle->Render();
    collider->Render();
}

void ParticleScene::PostRender()
{
}

void ParticleScene::GUIRender()
{
    particle->GUIRender();
}
