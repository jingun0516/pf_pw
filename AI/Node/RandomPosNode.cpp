// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/RandomPosNode.h"
#include "AI/BaseAIController.h"
#include "AI/BaseAI.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

URandomPosNode::URandomPosNode()
{
	NodeName = TEXT("FindRandomPos");
}

EBTNodeResult::Type URandomPosNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed) return EBTNodeResult::Failed;

	if (nullptr == AICharacter) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy Initialize failed!"));
		return EBTNodeResult::Failed;
	}

	//���� �����Ϳ� ������ navi mesh�� �ʱ�ȭ
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (nullptr == NavSystem) {
		//navi mesh�� ���ٸ� ���и� ��ȯ
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Enemy in Navi"));
		return EBTNodeResult::Failed;
	}

	FVector const Origin = AICharacter->GetActorLocation();
	FNavLocation NextPatrol;

	//NextPatrol������ ������ location �����͸� �ְ� �ٽ� TargetLocationŰ�� value�� ���� �־��ش�.
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, search_radius, NextPatrol, nullptr))
	{
		Controller->get_blackboard()->SetValueAsVector(L"TargetLocation", NextPatrol.Location);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextPosSuccess!"));
	}

	//�� ���� �̵��� ���� Ȯ���ϱ� ���� ����׸޽���
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("TargetLocation: %s"), *NextPatrol.Location.ToString()));

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
