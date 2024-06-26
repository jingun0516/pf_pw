// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/pw_AnimInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"
#include "Characters/BaseCharacter.h"
#include "Components/ToolComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/State/StateEnum.h"
#include "Components/State/StateComponent.h"

void Upw_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (Owner != nullptr)
		Movement = Owner->GetCharacterMovement();
}

void Upw_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Movement || !Owner) return;
	bIsFalling = Movement->IsFalling();

	Velocity = Owner->GetVelocity();
	Speed = Velocity.Size2D();

	Rotation = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Rotation);

	bShouldMove =
		UKismetMathLibrary::NotEqual_VectorVector
		(
			Movement->GetCurrentAcceleration(),
			FVector(0, 0, 0),
			0.0f
		) && Speed > 3.0f;

	if(Owner->GetToolComponent())
		bAttack = Owner->GetToolComponent()->bAttack;
	if (Owner->GetStateComponent())
		state = Owner->GetStateComponent()->GetState();
	DamagedDirection = Owner->GetDirection();
	const FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(Owner->GetControlRotation(), Owner->GetActorRotation());
	// A와 B를 비교해 차이값을 구함
	// 캐릭터와 카메라 비교
	Yaw = DeltaRotator.Yaw;
	Pitch = DeltaRotator.Pitch;
}
