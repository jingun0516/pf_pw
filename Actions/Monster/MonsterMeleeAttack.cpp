// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Monster/MonsterMeleeAttack.h"
#include "Characters/BaseCharacter.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AI/AIMonster/UndeadBear_AI.h"
#include "AI/AIMonster/WereWolf_AI.h"

void UMonsterMeleeAttack::DoAction()
{
	Super::DoAction();
	
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("MonsterMeleeAttack: Has No Owner!"));
		return;
	}

	OriginSpeed = OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed;

	if (OwnerCharacter->GetStateComponent()->GetState() == E_StateType::E_Idle)
	{
		if (Cast<AWereWolf_AI>(OwnerCharacter))
		{
			PlayAnimMontageToIndex(0, 1.5f);
		}
		else if (Cast<AUndeadBear_AI>(OwnerCharacter))
		{
			PlayAnimMontageToIndex(1, 1.5f);
		}
		OwnerCharacter->GetStateComponent()->SetState(E_StateType::E_Attacking);
	}
	
	
}

void UMonsterMeleeAttack::TickAction()
{
	Super::TickAction();
}

void UMonsterMeleeAttack::EndAction()
{
	Super::EndAction();
}

void UMonsterMeleeAttack::BeginActionNotify()
{
	Super::BeginActionNotify();

	//OwnerCharacter->GetStateComponent()->SetState(E_StateType::E_Attacking);
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 0.f;
}

void UMonsterMeleeAttack::EndActionNotify()
{
	Super::EndActionNotify();

	OwnerCharacter->GetStateComponent()->SetState(E_StateType::E_Idle);
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = OriginSpeed;
}
