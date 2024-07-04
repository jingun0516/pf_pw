#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRandomSpawnSpot.h"
#include "SpawnAISpot.generated.h"

class UInfosDataAsset;
class ABaseAI;
class UMonsterStatusDataAsset;
class ABaseCharacter;
class UBoxComponent;

UCLASS()
class PF_PW_API ASpawnAISpot : public ABaseRandomSpawnSpot
{
	GENERATED_BODY()
	
public:	
	ASpawnAISpot();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SpawnRandomMonster();
	bool CanSpawnMonster();


private:
	TArray<TSubclassOf<ABaseAI>> MonsterArray;
};
