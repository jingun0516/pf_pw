// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SetSpeedNode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PF_PW_API USetSpeedNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USetSpeedNode();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "true"))
	bool bWalking;
};
