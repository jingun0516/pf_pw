// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SetBehavior.generated.h"

enum class EBehaviorKeys : uint8;
/**
 * 
 */
UCLASS(Blueprintable)
class PF_PW_API UBTS_SetBehavior : public UBTService
{
	GENERATED_BODY()
	
private:
	UBTS_SetBehavior();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void SetBehavior(EBehaviorKeys behavior);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBoardKey", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector BehaviorKey;

	UBlackboardComponent* BlackBoardComp;

	float ActionDistance = 200.f;
};
