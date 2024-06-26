// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_SetActionType.h"
#include "AI/EnemyAI/EnemyAIController.h"
#include "AI/BaseAI.h"
#include "Characters/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Enum/EBehaviorKeys.h"
#include "Components/State/StateEnum.h"
#include "Components/State/StateComponent.h"

UBTS_SetActionType::UBTS_SetActionType()
{
	NodeName = TEXT("SetActionTypeService");
}

void UBTS_SetActionType::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Controller = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	auto AICharacter = Cast<ABaseAI>(Controller->GetPawn());

	BlackBoardComp = OwnerComp.GetBlackboardComponent();
	ABaseCharacter* enemy = Cast<ABaseCharacter>(BlackBoardComp->GetValueAsObject(TEXT("TargetActor")));
	
	if (enemy)
	{
		if (enemy->GetDistanceTo(AICharacter) <= ActionDistance)
		{
			SetActionType(EActionTypeKeys::E_Main);
		}
		else
		{
			SetActionType(EActionTypeKeys::E_None);

		}
		UE_LOG(LogTemp, Log, TEXT("Distance :%f / ActionDistance :%f"), enemy->GetDistanceTo(AICharacter), ActionDistance);
	}
	
	if (BlackBoardComp->GetValueAsEnum(TEXT("ActionTypeKey")) == static_cast<uint8>(EActionTypeKeys::E_Main))
	{
		UE_LOG(LogTemp, Log, TEXT("ActionType: Main"));
	}
	else if (BlackBoardComp->GetValueAsEnum(TEXT("ActionTypeKey")) == static_cast<uint8>(EActionTypeKeys::E_None))
	{
		UE_LOG(LogTemp, Log, TEXT("ActionType: None"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ActionType: OtherEnum"));
	}
	
}


void UBTS_SetActionType::SetActionType(EActionTypeKeys Action)
{
	if (!BlackBoardComp) return;

	BlackBoardComp->SetValueAsEnum(ActionTypeKey.SelectedKeyName, static_cast<uint8>(Action)); 
	//
	//EActionTypeKeys ActionType = static_cast<EActionTypeKeys>(BlackBoardComp->GetValueAsEnum(ActionTypeKey.SelectedKeyName));
	//UE_LOG(LogTemp, Log, TEXT("ActionType from Blackboard: %d"), ActionType);

}
