// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/Wild/PatrolNode.h"
#include "AI/EnemyAI/EnemyAIController.h"
#include "AI/BaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"


UPatrolNode::UPatrolNode()
{
	NodeName = TEXT("WildPatrol");
}

EBTNodeResult::Type UPatrolNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* Controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	ABaseAI* AICharacter = Controller->GetAICharacter();
	FVector TargetLocation = Controller->GetBBLoc();

	FVector ToLocation = Controller->GetTargetLoc();
	
	if (!AICharacter) {
		UE_LOG(LogTemp, Log, TEXT("PatrolNode : AICharacter is NULL"));
		return EBTNodeResult::Failed;
	}

	if (ToLocation == FVector(0, 0, 0))
	{
		Controller->SetTargetLoc(TargetLocation);
	}
	FVector AILocation = AICharacter->GetActorLocation();
	float dist = FVector::Distance(AILocation, ToLocation);

	if (dist <= 200.f)		// ToLocation과의 거리가 일정 수치 이하일 때 ToLocation 재설정
	{
		Controller->SetTargetLoc(TargetLocation);
	}
	Controller->MoveToLocation(ToLocation, 50.f);


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
