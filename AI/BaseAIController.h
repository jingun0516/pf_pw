// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class ABaseAI;
class UAISense;
/**
 * 
 */
UCLASS()
class PF_PW_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseAIController();
	FORCEINLINE ABaseAI* GetAICharacter() { return AICharacter; }

	FORCEINLINE class UBlackboardComponent* get_blackboard() {	return blackboard;	}
protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ABaseAI* AICharacter;

	class UBlackboardComponent* blackboard;
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BTComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;

	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
