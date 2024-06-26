#include "AI/Node/Team/TeamSetSpeedNode.h"
#include "AI/MyTeam/MyTeamAIController.h"
#include "AI/BaseAI.h"
#include "GameFramework/CharacterMovementComponent.h"

UTeamSetSpeedNode::UTeamSetSpeedNode()
{
	NodeName = TEXT("TeamSetSpeedNode");
}

EBTNodeResult::Type UTeamSetSpeedNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AMyTeamAIController>(OwnerComp.GetAIOwner());
	if (!Controller) return EBTNodeResult::Failed;;
	ABaseAI* AICharacter = Controller->GetAICharacter();

	if (!AICharacter) {
		UE_LOG(LogTemp, Log, TEXT("SetSpeedNode : AICharacter is NULL"));
		return EBTNodeResult::Failed;
	}
	if (bWalking)
	{
		if (AICharacter)
			AICharacter->GetCharacterMovement()->MaxWalkSpeed = AICharacter->GetWalkSpeed();
	}
	else
	{
		if (AICharacter)
			AICharacter->GetCharacterMovement()->MaxWalkSpeed = AICharacter->GetMaxSpeed();
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
