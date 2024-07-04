#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRandomSpawnSpot.h"
#include "SpawnFoliageSpot.generated.h"

class ABaseResource;
class UBoxComponent;
class ABaseCharacter;
class UInfosDataAsset;

UCLASS()
class PF_PW_API ASpawnFoliageSpot : public ABaseRandomSpawnSpot
{
	GENERATED_BODY()
	
public:	
	ASpawnFoliageSpot();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void SpawnRandomFoliage();
	bool CanSpawnFoliage();


private:
	TArray<TSubclassOf<ABaseResource>> ResourceArray;

};
