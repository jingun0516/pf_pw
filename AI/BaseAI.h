// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Monsters/BaseMonster.h"
#include "BaseAI.generated.h"

class UBehaviorTree;
class UBlackboardComponent;
class ABaseAIController;
class ABaseTool;
/**
 * 
 */
UCLASS()
class PF_PW_API ABaseAI : public ABaseMonster
{
	GENERATED_BODY()
	
public:
	ABaseAI();

	virtual void BeginPlay() override;

	void SetupEnemyAIController();
	void SetupTeamAIController();

	void ActivateAIController(bool bActivate);
	FORCEINLINE void SetCanAttack(bool can) { bCanAttack = can; }
	FORCEINLINE bool GetCanAttack() { return bCanAttack; }

protected:
	ABaseTool* MonsterTool;
	TSubclassOf<ABaseTool> MonsterToolClass;
	ABaseAIController* controller;

	virtual void SetCharacterMovement() override;
	void SetMonsterTool();
	bool bCanAttack = true;
};
