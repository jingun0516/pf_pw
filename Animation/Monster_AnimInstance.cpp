#include "Animation/Monster_AnimInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"
#include "Characters/Basecharacter.h"
#include "Components/State/StateEnum.h"
#include "Components/State/StateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMonster_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (Owner != nullptr)
		Movement = Owner->GetCharacterMovement();
}

void UMonster_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
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

	if(Owner->GetStateComponent())
		state = Owner->GetStateComponent()->GetState();
}
