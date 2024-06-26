// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TeamSetSpeedNode.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UTeamSetSpeedNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UTeamSetSpeedNode();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "true"))
	bool bWalking;
};
