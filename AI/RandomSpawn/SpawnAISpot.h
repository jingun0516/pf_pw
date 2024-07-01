#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnAISpot.generated.h"

class UInfosDataAsset;
class ABaseAI;
class UMonsterStatusDataAsset;
class ABaseCharacter;
class UBoxComponent;

UCLASS()
class PF_PW_API ASpawnAISpot : public AActor
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
	FVector makeRandomSpot();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* SpotCollision;

private:
	UInfosDataAsset* Infos;
	TArray<TSubclassOf<ABaseAI>> MonsterArray;
	ABaseCharacter* PlayerC;


	int CurTime = 0;
};
