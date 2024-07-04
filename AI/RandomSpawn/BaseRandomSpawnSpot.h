#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRandomSpawnSpot.generated.h"

class UBoxComponent;
class UInfosDataAsset;
class ABaseCharacter;

UCLASS()
class PF_PW_API ABaseRandomSpawnSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseRandomSpawnSpot();

protected:
	virtual void BeginPlay() override;
	FVector makeRandomSpot();

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* SpotCollision;

	UInfosDataAsset* Infos;
	ABaseCharacter* PlayerC;

	int CurTime = 0;
};
