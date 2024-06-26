#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "Characters/BaseCharacter.h"

UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	SetState(E_StateType::E_Idle);

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	DOnHit.AddUFunction(this, "OnHitFunc");
	DOnDead.AddUFunction(this, "OnDeadFunc");
}


void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStateComponent::SetState(E_StateType state)
{
	CurState = state;

	if (CurState == E_StateType::E_Hit)
	{
		if (DOnHit.IsBound())
			DOnHit.Broadcast();
	}
	else if (CurState == E_StateType::E_Dead)
	{
		if (DOnDead.IsBound())
			DOnDead.Broadcast();
	}
}

void UStateComponent::OnHitFunc()
{
	if (OwnerCharacter)
		if(OwnerCharacter->GetHitMontage())
			OwnerCharacter->PlayAnimMontage(OwnerCharacter->GetHitMontage());
}

void UStateComponent::OnDeadFunc()
{
	if (OwnerCharacter)
	{
		if (OwnerCharacter->GetDeadMontage())
		{
			OwnerCharacter->PlayAnimMontage(OwnerCharacter->GetDeadMontage());
		}
	}
}

