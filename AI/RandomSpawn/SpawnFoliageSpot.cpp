#include "AI/RandomSpawn/SpawnFoliageSpot.h"
#include "SpawnFoliageSpot.h"
#include "Helper.h"
#include "InfosDataAsset.h"
#include "math.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/BaseCharacter.h"
#include "Resources/BaseResource.h"
#include "AI/RandomSpawn/BaseRandomSpawnSpot.h"

ASpawnFoliageSpot::ASpawnFoliageSpot()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnFoliageSpot::BeginPlay()
{
	Super::BeginPlay();

	ResourceArray = Infos->GetResourceArray();
}

void ASpawnFoliageSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurTime % 500 == 0)
		SpawnRandomFoliage();
}

void ASpawnFoliageSpot::SpawnRandomFoliage()
{
	int ArraySize = ResourceArray.Num();
	int32 RandomInt = FMath::RandRange(0, ArraySize - 1);

	FVector loc = makeRandomSpot();

	if (CanSpawnFoliage())
		GetWorld()->SpawnActor<ABaseResource>(ResourceArray[RandomInt], loc, FRotator());
}

bool ASpawnFoliageSpot::CanSpawnFoliage()
{
	TArray<AActor*> OverlappingActors;
	this->GetOverlappingActors(OverlappingActors);

	for (auto actors : OverlappingActors)
	{
		if (actors != this)
		{
			return false;
		}
	}

	return true;
}
