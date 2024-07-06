#include "AI/RandomSpawn/SpawnAISpot.h"
#include "AI/BaseAI.h"
#include "Helper.h"
#include "InfosDataAsset.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Characters/Monsters/MonsterStatusDataAsset.h"
#include "Characters/BaseCharacter.h"
#include "math.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI/RandomSpawn/BaseRandomSpawnSpot.h"

ASpawnAISpot::ASpawnAISpot()
{
	PrimaryActorTick.bCanEverTick = true; 
}

void ASpawnAISpot::BeginPlay()
{
	Super::BeginPlay();

	for (auto monsterArr : Infos->GetMonsterArray())
		MonsterArray.Add(monsterArr->MonsterClass);
}



void ASpawnAISpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if(CurTime % 200 == 0)
		//SpawnRandomMonster();
	if (CurTime >= 5000 && CurTime % 500 == 0)
		SpawnRandomMonster();
	
	if (CurTime >= 7000) Destroy();
	
}

void ASpawnAISpot::SpawnRandomMonster()
{
	int ArraySize = MonsterArray.Num();
	int32 RandomInt = FMath::RandRange(0, ArraySize - 1);

	FVector loc = makeRandomSpot();

	if (CanSpawnMonster())
		GetWorld()->SpawnActor<ABaseAI>(MonsterArray[RandomInt], loc, FRotator(0.f, 0.f, 0.f));
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
