스카이림 리소스 추출 워크플로우


1. skeleton.nif (짐승형은 skeletonbeast.nif)파일을 블렌더에서 불러온다

주의할 점: Rename bones 체크 해제


2. 아마추어가 선택된 상태로 캐릭터 메쉬 불러오기(조각나있는 모델의 경우 머리 다리 몸통 등 다 한번에 불러와야 됨)

마찬가지로 rename bones 체크해제

3. 메쉬 불러온 거 확인 후 다시 아마추어 선택 후 애니메이션(.hkx) 불러오기
이때 오른편 설정에서 skeleton.hkx의 경로를 지정해주고 불러와야 한다.

4.성공적으로 애니메이션이 재생된다면 전체 드래그 한 후 fbx로 내보내기
이때 내보내기 옵션은 X forward Y Up으로 해주기
