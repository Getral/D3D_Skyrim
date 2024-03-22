#include "Framework.h"
#include "ArrowManager.h"

ArrowManager::ArrowManager()
{
    //arrowInstancing = ("Arrow");
    //arrows.reserve(SIZE);
    //
    //FOR(SIZE)
    //{
    //    Transform* transform = arrowInstancing
    //    transform->SetActive(false);
    //    Arrow* arrow = new Arrow(transform);
    //    arrows.push_back(arrow);
    //    
    //}

    arrowInstancing = new ModelInstancing("arrow");
    arrows.reserve(SIZE);

    FOR(SIZE)
    {
        Transform* transform = arrowInstancing->Add();
        transform->SetActive(false);
        EbonyArrow* arrow = new EbonyArrow(transform);
        arrows.push_back(arrow);
    }
}

ArrowManager::~ArrowManager()
{
    for (EbonyArrow* arrow : arrows)
        delete arrow;

    delete arrowInstancing;
}

void ArrowManager::Update()
{
    arrowInstancing->Update();
    for (EbonyArrow* arrow : arrows) arrow->Update();
}

void ArrowManager::Render()
{
    arrowInstancing->Render();
    for (EbonyArrow* arrow : arrows) arrow->Render();
}

void ArrowManager::Shoot(Vector3 pos, Vector3 dir)
{
    for (EbonyArrow* arrow : arrows)
    {
        if (!arrow->GetTransform()->Active())
        {
            arrow->Shoot(pos, dir);
            return;
        }
    }
}

bool ArrowManager::IsCollision(Collider* collider)
{
    for (EbonyArrow* arrow : arrows)
    {
        if (arrow->GetCollider()->IsCollision(collider))
        {
            arrow->GetTransform()->SetActive(false);
            return true;
        }
    }

	return false;
}
