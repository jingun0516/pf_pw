#include "AI/Node/Team/TeamFindResourceNode.h"
#include "AI/MyTeam/MyTeamAIController.h"
#include "AI/BaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UTeamFindResourceNode::UTeamFindResourceNode()
{
	NodeName = TEXT("TeamResourceFind");
}

EBTNodeResult::Type UTeamFindResourceNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (dist <= 200.f)		// ToLocation과의 거리가 일정 수치 이하일 때 ToLocation 재설정
	{
		Controller->SetTargetLoc(TargetLocation);
	}
	Controller->MoveToLocation(ToLocation, 50.f);


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
