// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BaseAINode.generated.h"

class ABaseAIController;
class ABaseAI;
/**
 * 
 */
UCLASS()
class PF_PW_API UBaseAINode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	ABaseAIController* Controller;
	ABaseAI* AICharacter;
	class UBlackboardComponent* blackboard;
};
