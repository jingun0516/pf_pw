// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TeamActionNode.generated.h"

class AMyTeamAIController;
/**
 * 
 */
UCLASS()
class PF_PW_API UTeamActionNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UTeamActionNode();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
