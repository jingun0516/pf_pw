// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Monster_AnimInstance.generated.h"

enum class E_StateType : UINT8;
class ABaseCharacter;
class UCharacterMovementComponent;
/**
 *
 */
UCLASS()
class PF_PW_API UMonster_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = BlendSpace, meta = (AllowPrivateAccess = "true"))
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = BlendSpace, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = BlendSpace, meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = BlendSpace, meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, Category = BlendSpace, meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;

	UPROPERTY(BlueprintReadOnly, Category = ToolComponent, meta = (AllowPrivateAccess = "true"))
	bool bAttack;

	UPROPERTY(BlueprintReadOnly, Category = StateComponent, meta = (AllowPrivateAccess = "true"))
	E_StateType state;

private:
	ABaseCharacter* Owner;

	UCharacterMovementComponent* Movement;
	FRotator Rotation;
};
