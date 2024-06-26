// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/Wild/SetSpeedNode.h"
#include "AI/EnemyAI/EnemyAIController.h"
#include "AI/BaseAI.h"
#include "GameFramework/CharacterMovementComponent.h"

USetSpeedNode::USetSpeedNode()
{
	NodeName = TEXT("WildSetSpeedNode");
}

EBTNodeResult::Type USetSpeedNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
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
