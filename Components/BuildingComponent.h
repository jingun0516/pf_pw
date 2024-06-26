#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

class ABaseCharacter;
class AHero;
class ABaseBuilding;
class AWorkTimeActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_PW_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TSubclassOf<ABaseBuilding> GetBuildingToMake() { return BuildingToMake; }
	FORCEINLINE AWorkTimeActor* GetWorkTimeActor() { return WorkTimeActor; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseBuilding> BuildingToMake = nullptr;

	ABaseBuilding* GetTempBuilding() { return tempBuilding; }

	UFUNCTION()
	void BulidingInteraction(ABaseBuilding* building);

	bool CanSpawnBuilding();
	void SpawnBuilding(TSubclassOf<ABaseBuilding> ToBuild);
	void SpawnBuildingStart();
	void SpawnBuildingSuccess();
	void BuildingCancel();
private:
	AWorkTimeActor* WorkTimeActor;
	ABaseBuilding* tempBuilding;

	ABaseCharacter* OwnerCharacter;
	AHero* OwnerHero;
};
