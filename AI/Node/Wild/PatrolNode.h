// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolNode.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UPatrolNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPatrolNode();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
