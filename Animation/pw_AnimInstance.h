// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "pw_AnimInstance.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;
enum class E_StateType : UINT8;

/**
 *
 */
UCLASS()
class PF_PW_API Upw_AnimInstance : public UAnimInstance
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

	UPROPERTY(BlueprintReadOnly, Category = Aimoffset, meta = (AllowPrivateAccess = "true"))
	float Yaw;

	UPROPERTY(BlueprintReadOnly, Category = Aimoffset, meta = (AllowPrivateAccess = "true"))
	float Pitch;

	UPROPERTY(BlueprintReadOnly, Category = DamagedDirection, meta = (AllowPrivateAccess = "true"))
	int DamagedDirection;

private:
	ABaseCharacter* Owner;

	UCharacterMovementComponent* Movement;
	FRotator Rotation;
};
