// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TeamFindResourceNode.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UTeamFindResourceNode : public UBTTaskNode
{
	GENERATED_BODY()
	
	UTeamFindResourceNode();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
