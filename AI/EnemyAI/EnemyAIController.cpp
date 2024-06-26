// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAI/EnemyAIController.h"
#include "Characters/Hero.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Helper.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "AI/BaseAI.h"

AEnemyAIController::AEnemyAIController()
{
	SetActorTickEnabled(true);

	BTAsset = Helper::GetAsset<UBehaviorTree>(L"/Game/AI/MonsterAI/BT_Enemy");
	BTComp = Helper::CreateActorComponent<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));
	blackboard = Helper::CreateActorComponent<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	TargetLoc = FVector(0, 0, 0);
	//PerceptionÃÊ±âÈ­
	SetPerceptionSystem();

}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bFound)
	{
		bbLoc = get_blackboard()->GetValueAsVector(TEXT("TargetLocation"));
	}
}

void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	UE_LOG(LogTemp, Log, TEXT("Perception Updated"));

	bFound = false;
	for (auto actor : UpdatedActors)
	{
		UE_LOG(LogTemp, Log, TEXT("%s Perception Detected"), *actor->GetName());
		if (AHero* hero = Cast<AHero>(actor))
		{
			get_blackboard()->SetValueAsObject(TEXT("TargetActor"), hero);
			AHero* asdf = Cast<AHero>(get_blackboard()->GetValueAsObject(TEXT("TargetActor")));
			if(asdf)
				UE_LOG(LogTemp, Log, TEXT("Set PlayerKey Succeed : %s"), *asdf->GetName());
			bFound = true;
			break;
		}

		if (ABaseMonster* monster = Cast<ABaseMonster>(actor))
		{
			if (!(monster->GetIsWild()))
			{
				get_blackboard()->SetValueAsObject(TEXT("TargetActor"), monster);
				UE_LOG(LogTemp, Log, TEXT("Set TargetActor Succeed"));
				bFound = true;
				break;
			}
		}
	}
}

void AEnemyAIController::SetPerceptionSystem()
{
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}


float AEnemyAIController::GetDistance(FVector location1, FVector location2)
{
	FVector location = location1 - location2;

	return sqrt(location.X * location.X + location.Y * location.Y + location.Z * location.Z);
}