// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SetActionType.generated.h"

enum class EActionTypeKeys : uint8;
class ABaseResource;
class ABaseCharacter;
/**
 * 
 */
UCLASS(Blueprintable)
class PF_PW_API UBTS_SetActionType : public UBTService
{
	GENERATED_BODY()

private:
	UBTS_SetActionType();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBoardKey", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector ActionTypeKey;

	UBlackboardComponent* BlackBoardComp;

	void SetActionType(EActionTypeKeys Action);
};
