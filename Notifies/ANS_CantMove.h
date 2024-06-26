// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/ANS_HeroBase.h"
#include "ANS_CantMove.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UANS_CantMove : public UANS_HeroBase
{
	GENERATED_BODY()

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	float OriginSpeed = 0.f;
};
