// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_HeroBase.generated.h"

class UToolComponent;
class UStatusComponent;
class UStateComponent;
class ABaseCharacter;
/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(NotifyLog, Log, All);

UCLASS()
class PF_PW_API UAN_HeroBase : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY()
	ABaseCharacter* Owner;

	UPROPERTY()
	UToolComponent* ToolComponent;

	UPROPERTY()
	UStatusComponent* StatusComponent;

	UPROPERTY()
	UStateComponent* StateComponent;
};
