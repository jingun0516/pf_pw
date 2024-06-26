// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "FindPatrolPosNode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)		// 에디터상에서 Blueprint로 뽑아내기 위함
class PF_PW_API UFindPatrolPosNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindPatrolPosNode();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float search_radius = 1500.f;
};
