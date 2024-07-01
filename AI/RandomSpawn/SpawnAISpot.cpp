#include "AI/RandomSpawn/SpawnAISpot.h"
#include "AI/BaseAI.h"
#include "Helper.h"
#include "InfosDataAsset.h"
#include "Characters/Monsters/MonsterStatusDataAsset.h"
#include "Characters/BaseCharacter.h"
#include "math.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

ASpawnAISpot::ASpawnAISpot()
{
	PrimaryActorTick.bCanEverTick = true; 

	CurTime = 0;
	Infos = Helper::GetAsset<UInfosDataAsset>(L"/Game/ETC/DA_Info");

	SpotCollision = Helper::CreateSceneComponent<UBoxComponent>(this, L"Box Comp");

}

void ASpawnAISpot::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);

	for (auto monsterArr : Infos->GetMonsterArray())
		MonsterArray.Add(monsterArr->MonsterClass);

	PlayerC = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}



void ASpawnAISpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurTime++;

	if (CurTime % 500 == 0)
		SpawnRandomMonster();
	
}

void ASpawnAISpot::SpawnRandomMonster()
{
	int ArraySize = MonsterArray.Num();
	int32 RandomInt = FMath::RandRange(0, ArraySize - 1);
	UE_LOG(LogTemp, Log, TEXT("%d"), RandomInt);
	FVector loc = makeRandomSpot();

	if (CanSpawnMonster())
		GetWorld()->SpawnActor<ABaseAI>(MonsterArray[RandomInt], loc, FRotator());

	//else
	//	this->Destroy();
}

bool ASpawnAISpot::CanSpawnMonster()
{
	TArray<AActor*> OverlappingActors;
	this->GetOverlappingActors(OverlappingActors);

	for (auto actors : OverlappingActors)
	{
		if (actors != this || actors != PlayerC || !Cast<ABaseAI>(actors))
		{
			return false;
		}
	}

	return true;
}

FVector ASpawnAISpot::makeRandomSpot()
{
	FVector Origin = SpotCollision->Bounds.Origin;
	FVector BoxExtent = SpotCollision->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
}

