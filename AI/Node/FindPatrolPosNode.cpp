// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/FindPatrolPosNode.h"
#include "AI/BaseAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

// 현재 위치를 기준으로 임의의 location 값을 지정, 반환

UFindPatrolPosNode::UFindPatrolPosNode()
{
	NodeName = TEXT("FindPatrolPosNode");
}

EBTNodeResult::Type UFindPatrolPosNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	auto Enemy = Controller->GetPawn();

	if (nullptr == Enemy) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy Initialize failed!"));
		return EBTNodeResult::Failed;
	}
	
	//현재 에디터에 설정된 navi mesh로 초기화
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (nullptr == NavSystem) {
		//navi mesh가 없다면 실패를 반환
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Enemy in Navi"));
		return EBTNodeResult::Failed;
	}
	
	FVector const Origin = Enemy->GetActorLocation();
	FNavLocation NextPatrol;

	//NextPatrol변수에 임의의 location 데이터를 넣고 다시 TargetLocation키의 value에 값을 넣어준다.
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, search_radius, NextPatrol, nullptr))
	{
		Controller->get_blackboard()->SetValueAsVector(L"TargetLocation", NextPatrol.Location);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextPosSuccess!"));
	}

	//그 다음 이동할 곳을 확인하기 위한 디버그메시지
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("TargetLocation: %s"), *NextPatrol.Location.ToString()));

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
}
