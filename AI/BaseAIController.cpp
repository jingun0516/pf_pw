// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "AI/BaseAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense.h"
#include "Perception/AISenseConfig_Sight.h" // 예: 시각 감지 설정
#include "Perception/AISenseConfig_Hearing.h" // 예: 청각 감지 설정
#include "Characters/Hero.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Helper.h"


ABaseAIController::ABaseAIController()
{
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if(BTAsset)
		RunBehaviorTree(BTAsset);
	if(BTComp)
		BTComp->StartTree(*BTAsset);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AICharacter = Cast<ABaseAI>(InPawn);
}
