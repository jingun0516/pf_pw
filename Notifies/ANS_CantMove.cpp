// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/ANS_CantMove.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

FString UANS_CantMove::GetNotifyName_Implementation() const
{
	return FString(L"CantMove");
}

void UANS_CantMove::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!Owner) return;
	OriginSpeed = Owner->GetCharacterMovement()->MaxWalkSpeed;
	Owner->GetCharacterMovement()->MaxWalkSpeed = 0.f;
}

void UANS_CantMove::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!Owner) return;
	Owner->GetCharacterMovement()->MaxWalkSpeed = OriginSpeed;
}
