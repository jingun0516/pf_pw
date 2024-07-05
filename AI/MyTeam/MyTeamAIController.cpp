#include "AI/MyTeam/MyTeamAIController.h"
#include "Characters/Hero.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Characters/BaseCharacter.h"
#include "Helper.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "AI/BaseAI.h"
#include "Resources/BaseResource.h"

AMyTeamAIController::AMyTeamAIController()
{
	SetActorTickEnabled(true);

	BTAsset = Helper::GetAsset<UBehaviorTree>(L"/Game/AI/MonsterAI/BT_MyTeam");
	BTComp = Helper::CreateActorComponent<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));
	blackboard = Helper::CreateActorComponent<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	TargetLoc = FVector(0, 0, 0);
	//PerceptionÃÊ±âÈ­
	SetPerceptionSystem();

}

void AMyTeamAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyTeamAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMyTeamAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bFound)
	{
		bbLoc = get_blackboard()->GetValueAsVector(TEXT("TargetLocation"));
	}
}

void AMyTeamAIController::OnUpdated(TArray<AActor*> const& updated_actors)
{
}

void AMyTeamAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	bFound = false;

	for (auto actor : UpdatedActors)
	{
		UE_LOG(LogTemp, Log, TEXT("TeamAI Perception Updated : %s"), *actor->GetName());
		if (ABaseMonster* monster = Cast<ABaseMonster>(actor))
		{
			if (!(monster->GetIsWild())) continue;

			get_blackboard()->SetValueAsObject(TEXT("TargetActor"), monster);
			UE_LOG(LogTemp, Log, TEXT("Set Monster TargetActor Succeed"));
			bFound = true;
			break;
		}
		else if (ABaseResource* resource = Cast<ABaseResource>(actor))
		{
			if (get_blackboard()->GetValueAsObject(TEXT("TargetActor")) != nullptr) continue;

			get_blackboard()->SetValueAsObject(TEXT("TargetActor"), resource);
			UE_LOG(LogTemp, Log, TEXT("Set Resource TargetActor Succeed"));
			bFound = true;
			break;
		}
	}
}

void AMyTeamAIController::SetPerceptionSystem()
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
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMyTeamAIController::OnPerceptionUpdated);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}


float AMyTeamAIController::GetDistance(FVector location1, FVector location2)
{
	FVector location = location1 - location2;

	return sqrt(location.X * location.X + location.Y * location.Y + location.Z * location.Z);
}