#include "Actions/KickAction.h"
#include "Characters/BaseCharacter.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "GameFramework/CharacterMovementComponent.h"


void UKickAction::DoAction()
{
	Super::DoAction();

	if (OwnerCharacter->GetStateComponent()->GetState() == E_StateType::E_Idle)
	{
		OwnerCharacter->GetStateComponent()->SetState(E_StateType::E_Attacking);
		PlayAnimMontageToIndex(0, 2.0f);
	}
}

void UKickAction::TickAction()
{
	Super::TickAction();
}

void UKickAction::EndAction()
{
	Super::EndAction();
}

void UKickAction::BeginActionNotify()
{
	Super::BeginActionNotify();

	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 0.f;
}

void UKickAction::EndActionNotify()
{
	Super::EndActionNotify();

	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.f;
}
