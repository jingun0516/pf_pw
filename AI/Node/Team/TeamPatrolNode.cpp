#include "AI/Node/Team/TeamPatrolNode.h"
#include "TeamPatrolNode.h"
#include "AI/MyTeam/MyTeamAIController.h"
#include "AI/BaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UTeamPatrolNode::UTeamPatrolNode()
{
	NodeName = TEXT("TeamPatrol");
}

EBTNodeResult::Type UTeamPatrolNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyTeamAIController* Controller = Cast<AMyTeamAIController>(OwnerComp.GetAIOwner());

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

	if (dist <= 200.f || cnt >= 500)		// ToLocation과의 거리가 일정 수치 이하일 때 ToLocation 재설정
	{
		Controller->SetTargetLoc(TargetLocation);
		cnt = 0;
	}
	UE_LOG(LogTemp, Log, TEXT("cnt: %d"), cnt);
	Controller->MoveToLocation(ToLocation, 50.f);
	cnt++;

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
}
