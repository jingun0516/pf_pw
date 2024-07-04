#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UserStatusComponent.generated.h"

class AHero;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_PW_API UUserStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUserStatusComponent();

	FORCEINLINE int GetHPPoint() { return HPPoint; }
	FORCEINLINE int GetStaminaPoint() { return StaminaPoint; }
	FORCEINLINE int GetAttackPoint() { return AttackPoint; }
	FORCEINLINE int GetDefPoint() { return DefPoint; }
	FORCEINLINE int GetWorkTimePoint() { return WorkTimePoint; }
	FORCEINLINE int GetWeightPoint() { return WeightPoint; }
	
	void AddHPPoint(int point);
	FORCEINLINE void AddStaminaPoint(int point) { StaminaPoint += point; }
	FORCEINLINE void AddAttackPoint(int point) { AttackPoint += point; }
	FORCEINLINE void AddDefPoint(int point) { DefPoint += point; }
	FORCEINLINE void AddWorkTimePoint(int point) { WorkTimePoint += point; }
	FORCEINLINE void AddWeightPoint(int point) { WeightPoint += point; }

protected:
	virtual void BeginPlay() override;

private:
	AHero* OwnerHero;
	int StatusPoint;

	int HPPoint = 100;
	int StaminaPoint = 100;
	int AttackPoint = 100;
	int DefPoint = 100;
	int WorkTimePoint = 100;
	int WeightPoint = 100;

		
};
