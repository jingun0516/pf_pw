// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_SetBehavior.h"
#include "AI/BaseAIController.h"
#include "AI/BaseAI.h"
#include "Characters/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Enum/EBehaviorKeys.h"
#include "Components/State/StateEnum.h"
#include "Components/State/StateComponent.h"
#include "Resources/BaseResource.h"
#include "Kismet/KismetMathLibrary.h"



UBTS_SetBehavior::UBTS_SetBehavior()
{
	NodeName = TEXT("SetBehaviorService");
}

void UBTS_SetBehavior::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Controller = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	auto AICharacter = Cast<ABaseAI>(Controller->GetPawn());

	BlackBoardComp = OwnerComp.GetBlackboardComponent();

	ABaseCharacter* enemy = Cast<ABaseCharacter>(BlackBoardComp->GetValueAsObject(TEXT("TargetActor")));
	ABaseResource* resource = Cast<ABaseResource>(BlackBoardComp->GetValueAsObject(TEXT("TargetActor")));

	if (AICharacter->GetStateComponent()->GetState() == E_StateType::E_Hit)
	{
		SetBehavior(EBehaviorKeys::E_Hitted);
	}
	else if (enemy)
	{
		ActionDistance = 250.f;
		if (enemy->GetDistanceTo(AICharacter) <= ActionDistance)
		{
			if (AICharacter->GetCanAttack())
			{
				FVector enemyLoc = enemy->GetActorLocation();
				FRotator rotation = UKismetMathLibrary::FindLookAtRotation(AICharacter->GetActorLocation(), FVector(enemyLoc.X, enemyLoc.Y, AICharacter->GetActorLocation().Z));
				// 로테이션을 구해주는 함수

				AICharacter->SetActorRotation(rotation);
				SetBehavior(EBehaviorKeys::E_Action);
			}
			else
			{
				SetBehavior(EBehaviorKeys::E_Wait);
			}
		}
		else
		{
			if(AICharacter->GetStateComponent()->GetState() == E_StateType::E_Idle)
				SetBehavior(EBehaviorKeys::E_Track);
		}
	}
	else if (resource && !(AICharacter->GetIsWild()))
	{
		ActionDistance = 250.f;
		if (resource->GetDistanceTo(AICharacter) <= ActionDistance)
		{
			if (AICharacter->GetCanAttack())
			{
				FVector resLoc = resource->GetActorLocation();
				FRotator rotation = UKismetMathLibrary::FindLookAtRotation(AICharacter->GetActorLocation(), FVector(resLoc.X, resLoc.Y, AICharacter->GetActorLocation().Z));
				// 로테이션을 구해주는 함수
				
				AICharacter->SetActorRotation(rotation);
				SetBehavior(EBehaviorKeys::E_Action);
			}
			else
			{
				SetBehavior(EBehaviorKeys::E_Wait);
			}
		}
		else
		{
			if (AICharacter->GetStateComponent()->GetState() == E_StateType::E_Idle)
				SetBehavior(EBehaviorKeys::E_Track);
		}
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("No enemy Detected, Patrol"));
		SetBehavior(EBehaviorKeys::E_Patrol);
	}
	/*
	if (BlackBoardComp->GetValueAsEnum(TEXT("BehaviorKey")) == static_cast<uint8>(EBehaviorKeys::E_Action))
	{
		UE_LOG(LogTemp, Log, TEXT("BehaviorKey: E_Action"));
	}
	else if (BlackBoardComp->GetValueAsEnum(TEXT("BehaviorKey")) == static_cast<uint8>(EBehaviorKeys::E_Hitted))
	{
	 	UE_LOG(LogTemp, Log, TEXT("BehaviorKey: E_Hitted"))
	}
	else if (BlackBoardComp->GetValueAsEnum(TEXT("BehaviorKey")) == static_cast<uint8>(EBehaviorKeys::E_Track))
	{
	 	UE_LOG(LogTemp, Log, TEXT("BehaviorKey: E_Track"));
	}
	else if (BlackBoardComp->GetValueAsEnum(TEXT("BehaviorKey")) == static_cast<uint8>(EBehaviorKeys::E_Patrol))
	{
		UE_LOG(LogTemp, Log, TEXT("BehaviorKey: E_Patrol"));
	}
	else UE_LOG(LogTemp, Log, TEXT("BehaviorKey: Other Enum"));
	*/
}

void UBTS_SetBehavior::SetBehavior(EBehaviorKeys behavior)
{
	if (!BlackBoardComp) return;

	BlackBoardComp->SetValueAsEnum(BehaviorKey.SelectedKeyName, static_cast<uint8>(behavior));
}
