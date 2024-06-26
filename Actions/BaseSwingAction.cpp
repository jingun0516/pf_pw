#include "Actions/BaseSwingAction.h"
#include "Logging/LogMacros.h"

#include "Characters/BaseCharacter.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"

void UBaseSwingAction::DoAction()
{
	Super::DoAction();

	if (!OwnerCharacter) return;

	if (OwnerCharacter->GetStateComponent()->GetState() == E_StateType::E_Idle)
	{
		OwnerCharacter->GetStateComponent()->SetState(E_StateType::E_Attacking);
		PlayAnimMontageToIndex(0);
	}
}

void UBaseSwingAction::TickAction()
{
	Super::TickAction();
}

void UBaseSwingAction::EndAction()
{
	Super::EndAction();
}
